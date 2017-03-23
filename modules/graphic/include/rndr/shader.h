#pragma once

#include "GL.hpp"
#include <vector>

namespace ax {
namespace rndr {

	class shader {
	public:
		static shader create_from_path(const char* vertex_path, const char* frag_path);

		static shader create_from_content(const char* vertex_content, const char* frag_content);

		shader();

		int compile(const char* vertex_content, const char* frag_content);
        
        int link(const std::vector<std::pair<GLuint, const char*>>& binded_values);
        
        void activate();
        
        GLint program_id() const {
            return _program_id;
        }
        
       GLuint get_uniform_location(const char* path);

	private:
		GLuint _program_id;
		GLuint _s_vertex;
		GLuint _s_fragment;
	};
} // rndr.
} // ax.
