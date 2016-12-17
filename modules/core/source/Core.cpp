/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axFrameworks.
 *
 * axFrameworks is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axFrameworks License.
 *
 * axFrameworks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axFrameworks. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axFrameworks, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#include "Core.hpp"
#include "GraphicInterface.hpp"
#include "Render.hpp"

namespace ax {
namespace core {
	Core::Core()
		: _needToDraw(true)
		, _popupNeedToDraw(true)
	{
		_windowManager = nullptr;
		_popupManager = nullptr;
		_editor_manager = nullptr;
	}

	void Core::InitManagers()
	{
		//	ax::Print("axCore::InitManagers");
		_windowManager = std::unique_ptr<ax::core::WindowManager>(new ax::core::WindowManager());
		_windowManager->_managerName = "WindowManager";

		_popupManager = std::unique_ptr<ax::core::WindowManager>(new ax::core::WindowManager());
		_popupManager->_managerName = "PopupManager";

		_realPopWindowManager = std::unique_ptr<ax::core::WindowManager>(new ax::core::WindowManager());
		_realPopWindowManager->_managerName = "RealPopWindowManager";

		_editor_manager = std::unique_ptr<ax::core::WindowManager>(new ax::core::WindowManager());
		_editor_manager->_managerName = "Editor";
	}

	int Core::InitGL()
	{
		GLenum err = glGetError();
		if (err != GL_NO_ERROR) {
			std::cout << "Error before ax::GL::Init : " << err << std::endl;
		}

		ax::GL::Init();

		err = glGetError();
		if (err != GL_NO_ERROR) {
			std::cout << "Error after ax::GL::Init : " << err << std::endl;
		}

		// Normal vertex shader.
		const std::string v_normal("uniform sampler2D texture1; 						\
		 uniform mat4 mvp_matrix;							\
		 attribute vec4 vPosition;							\
		 attribute vec4 vColor;								\
		 varying vec4 fragColor;							\
							   								\
		 void main()										\
		 {													\
			fragColor = vColor;								\
			gl_Position = mvp_matrix * vPosition;			\
		 }													");

		// Normal fragment shader.
		const std::string f_normal("varying vec4 fragColor;							\
		 uniform sampler2D texture1;						\
															\
		 void main()										\
		 {													\
			gl_FragColor = fragColor;						\
		 }													");

		// Framebuffer vertex shader.
		const std::string v_fb("attribute vec4 vPosition;		\
		 attribute vec2 vTexCoord;							\
		 attribute vec4 vColor;								\
		 uniform mat4 mvp_matrix;							\
		 varying vec2 v_texCoor;							\
						   									\
		 void main()										\
		 {													\
			v_texCoor = vTexCoord;							\
			gl_Position = mvp_matrix * vPosition;			\
		 }													");

		// Framebuffer fragment shader.
		const std::string f_fb("varying vec4 vColor;			\
	 	 uniform sampler2D texture1;						\
	  	 varying vec2 v_texCoor;							\
						   									\
		 void main()										\
		 {													\
			gl_FragColor = texture2D(texture1, v_texCoor);	\
		 }													");

		// Font vertex shader.
		const std::string v_font("uniform mat4 mvp_matrix;							\
		 attribute vec4 vPosition;							\
		 attribute vec2 vTexCoord;							\
		 attribute vec4 vColor;								\
		 varying vec4 fragColor;							\
		 varying vec2 v_texCoor;							\
							 								\
		 void main()										\
		 {													\
			v_texCoor = vTexCoord;							\
			fragColor = vColor;								\
			gl_Position = mvp_matrix * vPosition;			\
		 }													");

		// Font fragment shader.
		const std::string f_font("uniform sampler2D texture1;						\
		 varying vec4 fragColor;							\
		 varying vec2 v_texCoor;							\
															\
		 void main()										\
		 {													\
			vec4 txtColor = texture2D(texture1, v_texCoor); \
			gl_FragColor = fragColor * txtColor.a;			\
		 }													");

		// Image vertex shader.
		const std::string v_img("attribute vec4 vPosition;							\
		 attribute vec2 vTexCoord;							\
		 attribute vec4 vColor;								\
		 varying vec2 v_texCoor;							\
		 uniform mat4 mvp_matrix;							\
															\
		 void main()										\
		 {													\
			v_texCoor = vTexCoord;							\
			gl_Position = mvp_matrix * vPosition;			\
		 }													");

		// Image fragment shader.
		const std::string f_img("uniform sampler2D texture1;						\
		 varying vec2 v_texCoor;							\
															\
		 void main()										\
		 {													\
			gl_FragColor = texture2D(texture1, v_texCoor);	\
		 }													");

		// Trasnparent image vertex shader.
		const std::string v_img_alpha("attribute vec4 vPosition;							\
		 attribute vec2 vTexCoord;							\
		 attribute vec4 vColor;								\
		 varying vec4 fragColor;							\
		 varying vec2 v_texCoor;							\
		 uniform mat4 mvp_matrix;							\
															\
		 void main()										\
		 {													\
			v_texCoor = vTexCoord;							\
			fragColor = vColor;								\
			gl_Position = mvp_matrix * vPosition;			\
		 }													");

		// Transparent image fragment shader.
		const std::string f_img_alpha("varying vec2 v_texCoor;							\
		 varying vec4 fragColor;							\
		 uniform sampler2D texture1;						\
								  							\
		 void main()										\
		 {													\
		 	vec4 txtColor = texture2D(texture1, v_texCoor);	\
			gl_FragColor = fragColor.a * txtColor;			\
		 }													");

		// Color image vertex shader.
		const std::string v_img_color("attribute vec4 vPosition;							\
		 attribute vec2 vTexCoord;							\
	     attribute vec4 vColor;								\
	     varying vec4 fragColor;							\
	     varying vec2 v_texCoor;							\
	     uniform mat4 mvp_matrix;							\
	                                                        \
	     void main()										\
	     {													\
	     	v_texCoor = vTexCoord;							\
	     	fragColor = vColor;								\
	     	gl_Position = mvp_matrix * vPosition;			\
	     }													");

		// Color image fragment shader.
		const std::string f_img_color("varying vec2 v_texCoor;							\
		 varying vec4 fragColor;							\
		 uniform sampler2D texture1;						\
													        \
		 void main()										\
		 {													\
		 	vec4 txtColor = texture2D(texture1, v_texCoor);	\
		 	float cc = txtColor.a;							\
		 	gl_FragColor = vec4(fragColor.r, fragColor.g, fragColor.b, cc);			\
		 }													");

		ax::GC::shader_normal = ax::GL::Shader(true, v_normal, f_normal);
		ax::GC::shader_fb = ax::GL::Shader(true, v_fb, f_fb);
		ax::GC::shader_font = ax::GL::Shader(true, v_font, f_font);
		ax::GC::shader_image = ax::GL::Shader(true, v_img, f_img);
		ax::GC::shader_image_alpha = ax::GL::Shader(true, v_img_alpha, f_img_alpha);
		ax::GC::shader_image_color = ax::GL::Shader(true, v_img_color, f_img_color);

		ax::GC::shader_normal.CompileAndLink();
		ax::GC::shader_fb.CompileAndLink();
		ax::GC::shader_font.CompileAndLink();
		ax::GC::shader_image.CompileAndLink();
		ax::GC::shader_image_alpha.CompileAndLink();
		ax::GC::shader_image_color.CompileAndLink();
		ax::GC::shader_fb.Activate();

		return true;
	}

	ax::core::WindowManager* Core::GetWindowManager()
	{
		return _windowManager.get();
	}

	ax::core::WindowManager* Core::GetPopupManager()
	{
		return _popupManager.get();
	}

	ax::core::WindowManager* Core::GetRealPopWindowManager()
	{
		return _realPopWindowManager.get();
	}

	void Core::ResizeGLScene(const ax::Size& size)
	{
		// Prevent a division by zero.
		_size = ax::Size(size.w, size.h == 0 ? 1 : size.h);

		ax::GL::Resize(_size);

		_needToDraw = true;
		_popupNeedToDraw = true;

		GetWindowManager()->OnSize(size);
		//	GetPopupManager()->OnSize(size);
		//	GetEditorWindowManager()->OnSize(size);
	}

	ax::Size Core::GetGlobalSize() const
	{
		return _size;
	}

	void Core::SetGlobalSize(const ax::Size& size)
	{
		_size = size;
	}

	void Core::UpdateAll()
	{
		_needToDraw = true;
		_popupNeedToDraw = true;
	}

	int Core::DrawGLScene()
	{
		if (_needToDraw) {
			ax::GL::Draw(_size);

			GetWindowManager()->OnPaint();
			GetPopupManager()->OnPaint();
			GetEditorWindowManager()->OnPaint();

			glFinish();
			_needToDraw = false;
			return true;
		}

		return false;
	}
}
}
