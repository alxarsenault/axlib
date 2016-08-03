/*
 * Copyright (c) 2016 Alexandre Arsenault.
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

#include "Render.hpp"
#include "RenderMath.hpp"
#include "Shader.hpp"
#include "Util.hpp"

namespace ax {
namespace GL {
	Shader::Shader()
		: _program_id(0)
	{
	}

	Shader::Shader(const bool& content, const std::string& s_vextex_path, const std::string& s_fragments_path)
		: _program_id(0)
		, _is_content(content)
		, _s_vertex_path(s_vextex_path)
		, _s_fragments_path(s_fragments_path)
	{
	}

	void Shader::CompileAndLink()
	{
		GLuint s_vextex = 0;
		GLuint s_fragments = 0;

		// Create vertex shader.
		if (!_s_vertex_path.empty()) {

			// Create vertex shader.
			s_vextex = glCreateShader(GL_VERTEX_SHADER);

			if (_is_content) {
				const char* v_data = _s_vertex_path.c_str();
				glShaderSource(s_vextex, 1, &v_data, NULL);
			}
			else {
				// Read vertex shader file.
				std::ifstream vextex_shader_file(_s_vertex_path);
				std::vector<char> vertex_shader_buffer(
					(std::istreambuf_iterator<char>(vextex_shader_file)), std::istreambuf_iterator<char>());

				vertex_shader_buffer.push_back('\0');

				// Add source to shader.
				const char* v_data = vertex_shader_buffer.data();
				glShaderSource(s_vextex, 1, &v_data, NULL);
			}

			// Compile shader.
			glCompileShader(s_vextex);

			GLint isCompiled = 0;
			glGetShaderiv(s_vextex, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE) {
				int info_length = 0;
				glGetShaderiv(s_vextex, GL_INFO_LOG_LENGTH, &info_length);

				if (info_length > 1) {
					int n_char_written = 0;
					char* error_msg = new char[info_length];
					glGetShaderInfoLog(s_vextex, info_length, &n_char_written, error_msg);

					ax::console::Error("Vertex Shader :", error_msg);
					delete[] error_msg;
				}
			}
		}

		// Create fragments shader.
		if (!_s_fragments_path.empty()) {

			// Create fragmens shader.
			s_fragments = glCreateShader(GL_FRAGMENT_SHADER);

			if (_is_content) {
				const char* f_data = _s_fragments_path.c_str();
				glShaderSource(s_fragments, 1, &f_data, NULL);
			}
			else {
				// Read fragments shader file.
				std::ifstream vextex_fragments_file(_s_fragments_path);

				std::vector<char> vertex_fragments_buffer(
					(std::istreambuf_iterator<char>(vextex_fragments_file)),
					std::istreambuf_iterator<char>());

				vertex_fragments_buffer.push_back('\0');

				const char* f_data = vertex_fragments_buffer.data();

				// Add source to shader.
				glShaderSource(s_fragments, 1, &f_data, NULL);
			}

			// Compile shader.
			glCompileShader(s_fragments);

			GLint isCompiled = 0;
			glGetShaderiv(s_fragments, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE) {
				int info_length = 0;
				glGetShaderiv(s_fragments, GL_INFO_LOG_LENGTH, &info_length);

				if (info_length > 1) {
					int n_char_written = 0;
					char* error_msg = new char[info_length];
					glGetShaderInfoLog(s_fragments, info_length, &n_char_written, error_msg);

					ax::console::Error("Fragment Shader :", error_msg);
					delete[] error_msg;
				}
			}
		}

		// Create program and link.
		_program_id = glCreateProgram();
		glAttachShader(_program_id, s_vextex);
		glAttachShader(_program_id, s_fragments);

		// Bind vPosition to attribute 0
		glBindAttribLocation(_program_id, 0, "vPosition");
		glBindAttribLocation(_program_id, 1, "vTexCoord");
		glBindAttribLocation(_program_id, 2, "vColor");

		glLinkProgram(_program_id);

		// Check link status.
		int linked = 0;
		glGetProgramiv(_program_id, GL_LINK_STATUS, &linked);

		if (!linked) {
			int info_length = 0;
			glGetProgramiv(_program_id, GL_INFO_LOG_LENGTH, &info_length);

			if (info_length > 1) {
				char* error_msg = new char[info_length];
				glGetProgramInfoLog(_program_id, info_length, NULL, error_msg);
				ax::console::Error("Shader link :", error_msg);
				delete[] error_msg;
			}

			glDeleteProgram(_program_id);
		}
	}

	void Shader::Activate()
	{
		glUseProgram(_program_id);
	}

	GLint Shader::GetProgramId() const
	{
		return _program_id;
	}

	GLuint Shader::GetUniformLocation(const char* path)
	{
		return glGetUniformLocation(_program_id, path);
	}
}
}