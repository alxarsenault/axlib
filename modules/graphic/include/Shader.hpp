//
//  axGraphicInterface.h
//  axLib
//
//  Created by Alexandre Arsenault on 2015-02-17.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __AX_GL_SHADER_H__
#define __AX_GL_SHADER_H__

#include <string>
#include "Render.hpp"

namespace ax {
namespace GL {

	class Shader {
	public:
		Shader();

		Shader(const bool& content, const std::string& s_vextex_path,
			const std::string& s_fragments_path);
		
//		Shader(const std::pair<std::string, std::string>& content);
		
		void CompileAndLink();
		
		void Activate();
		
		GLint GetProgramId() const;
		
		GLuint GetUniformLocation(const char* path);

	private:
		GLuint _program_id;
		bool _is_content;
		
		std::string _s_vertex_path;
		std::string _s_fragments_path;
	};
}
}
#endif // __AX_GL_SHADER_H__
