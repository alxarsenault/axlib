/*
 * Copyright (c) 2017 Alexandre Arsenault.
 *
 * This file is part of OpenAX.
 *
 * OpenAX is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial OpenAX License.
 *
 * OpenAX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenAX. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses OpenAX, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#include "shader.h"
#include <fst/print.h>

namespace ax {
namespace rndr {
	shader shader::create_from_path(const char* vertex_path, const char* frag_path)
	{
		return shader();
	}

	shader shader::create_from_content(const char* vertex_content, const char* frag_content)
	{
		return shader();
	}

	shader::shader()
		: _program_id(0)
		, _s_vertex(0)
		, _s_fragment(0)
	{
	}

	int shader::compile(const char* vertex_content, const char* frag_content)
	{
		_s_vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(_s_vertex, 1, &vertex_content, nullptr);

		// Compile vertex shader.
		glCompileShader(_s_vertex);

		GLint isCompiled = 0;
		glGetShaderiv(_s_vertex, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE) {
			int info_length = 0;
			glGetShaderiv(_s_vertex, GL_INFO_LOG_LENGTH, &info_length);

			if (info_length > 1) {
				int n_char_written = 0;
				char* error_msg = new char[info_length];
				glGetShaderInfoLog(_s_vertex, info_length, &n_char_written, error_msg);

				fst::print("Vertex shader :", (const char*)error_msg);
				delete[] error_msg;
			}

			return 1;
		}

		_s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(_s_fragment, 1, &frag_content, nullptr);

		// Compile vertex shader.
		glCompileShader(_s_fragment);

		isCompiled = 0;
		glGetShaderiv(_s_fragment, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE) {
			int info_length = 0;
			glGetShaderiv(_s_fragment, GL_INFO_LOG_LENGTH, &info_length);

			if (info_length > 1) {
				int n_char_written = 0;
				char* error_msg = new char[info_length];
				glGetShaderInfoLog(_s_fragment, info_length, &n_char_written, error_msg);

				fst::print("Frament shader :", (const char*)error_msg);
				delete[] error_msg;
			}

			return 1;
		}

		return 0;
	}

	int shader::link(const std::vector<std::pair<GLuint, const char*>>& binded_values)
	{
		// Create program and link.
		_program_id = glCreateProgram();
		glAttachShader(_program_id, _s_vertex);
		glAttachShader(_program_id, _s_fragment);

		// Bind attributes.
		for (const auto& n : binded_values) {
			glBindAttribLocation(_program_id, n.first, n.second);
		}

		glLinkProgram(_program_id);

		// Check link status.
		int linked = 0;
		glGetProgramiv(_program_id, GL_LINK_STATUS, &linked);

		if (!linked) {
			int info_length = 0;
			glGetProgramiv(_program_id, GL_INFO_LOG_LENGTH, &info_length);

			if (info_length > 1) {
				char* error_msg = new char[info_length];
				glGetProgramInfoLog(_program_id, info_length, nullptr, error_msg);
				fst::print("Shader link :", (const char*)error_msg);
				delete[] error_msg;
			}

			glDeleteProgram(_program_id);
			return 1;
		}
		return 0;
	}

	void shader::activate()
	{
		glUseProgram(_program_id);
	}

	GLuint shader::get_uniform_location(const char* path)
	{
		return glGetUniformLocation(_program_id, path);
	}

} // rndr
}
