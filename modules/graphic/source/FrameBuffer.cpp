/*
 * Copyright (c) 2015 Alexandre Arsenault.
 *
 * This file is part of axLibrary.
 *
 * axLibrary is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axLibrary License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLibrary. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLibrary, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#include "Render.hpp"
#include "FrameBuffer.hpp"
#include "RenderMath.hpp"
#include "GC.hpp"

#include <fst/print.h>

// #ifdef ANDROID
// #include <EGL/egl.h> // requires ndk r5 or newer
// #include <EGL/eglext.h>
// #include <GLES/gl.h>
// #include <GLES/glext.h>
// #include <GLES2/gl2.h> 
// //#ifdef __linux__
// //#include <X11/Xlib.h>
// //#include <X11/Xutil.h>
// //#include <GL/glx.h>
// //#include <GL/gl.h>
// //#include <GL/glu.h>
// #elif WAYLAND
// #include "GL/gl.h"

// #elif axCoreX11
// #include "GL/gl.h"
// #include "GL/glext.h"

// #elif _MSC_VER
// #include <windows.h>
// #include "GL/glew.h"
// //#include <gl\gl.h>
// #include <gl\glu.h>

// #else //__APPLE__
// #include <OpenGL/OpenGL.h>
// #include <OpenGL/glu.h>
// #endif // __APPLE__

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi

namespace ax {
namespace GL {
	FrameBuffer::FrameBuffer(const ax::Size& size)
	{
		Init(size);
	}

	FrameBuffer::~FrameBuffer()
	{
#ifdef ANDROID 
#else
//		std::cout << "Delete framebuffer" << std::endl;
		//Delete resources
		//glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &_frameBufferTexture);
		//glFinish();
		//Bind 0, which means render to back buffer, as a result, fb is unbound
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &_frameBuffer);

#endif		
//		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);
//		if (status != GL_FRAMEBUFFER_COMPLETE_EXT) {
//			ax::Error("Generating frame buffer : ", status);
//		}
	}
	
	void FrameBuffer::Init(const ax::Size& size)
	{
#ifdef ANDROID
		glGenFramebuffersOES(1, &_frameBuffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, _frameBuffer);
#else
		glGenFramebuffers(1, &_frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
#endif

		// Create texture.
		glGenTextures(1, &_frameBufferTexture);
		glBindTexture(GL_TEXTURE_2D, _frameBufferTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//--------------------------------------------------------------------------------------------------------------------
//			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

#ifdef ANDROID
		// NULL means reserve texture memory, but texels are undefined.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, NULL);

		// Attach 2D texture to this FBO.
		glFramebufferTexture2DOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES,
			GL_TEXTURE_2D, _frameBufferTexture, 0);

		// Does the GPU support current FBO configuration.
		GLenum status = glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES);

		if (status != GL_FRAMEBUFFER_COMPLETE_OES) {
			ax::Error("Generating frame buffer : ", status);
		}

#else
		// NULL means reserve texture memory, but texels are undefined.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.w, size.h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, NULL);

		// Attach 2D texture to this FBO.
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, _frameBufferTexture, 0);

		// Does the GPU support current FBO configuration.
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);

		if (status != GL_FRAMEBUFFER_COMPLETE) {
			ax::console::Error("Generating frame buffer : ", status);
		}
#endif

#ifdef ANDROID
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, _frameBuffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, 0);
#else
		glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif


		GLenum err = GL_NO_ERROR;
		while((err = glGetError()) != GL_NO_ERROR)
		{
		  //ax::console::Error("GL :", err);
		  fst::errprint(ptrace, "GL :", err);
		}
	}

	void FrameBuffer::Resize(const ax::Size& size)
	{
		glBindTexture(GL_TEXTURE_2D, _frameBufferTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.w, size.h, 0, GL_RGBA,
					 GL_UNSIGNED_BYTE, NULL);
		
//		glDeleteTextures(1, &_frameBufferTexture);
//
//#ifdef ANDROID
//		glDeleteFramebuffersOES(1, &_frameBuffer);
//#else
//		glDeleteFramebuffers(1, &_frameBuffer);
//#endif
//		Init(size);
	}

	void FrameBuffer::DrawOnFrameBuffer(const std::function<void()>& fct,
		const ax::Size& size, const ax::Size& globalSize)
	{
		if(_custom_draw_on_fb_func) {
			return _custom_draw_on_fb_func(*this);
		}
	
		 bool need_to_reactive_clip_test = false;

		 if (glIsEnabled(GL_SCISSOR_TEST)) {
		 	glDisable(GL_SCISSOR_TEST);
		 	need_to_reactive_clip_test = true;
		 }


#ifdef ANDROID
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, _frameBuffer);
#else
		glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
		glPushAttrib(GL_DEPTH_BUFFER_BIT);
#endif

		glClearColor(0.0, 0.0, 0.0, 0.0);

#ifdef ANDROID
		glClearDepthf(1.0f);
#else
		glClearDepth(1.0f);
#endif

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		DrawingOnFrameBufferBlendFunction();

		glViewport(0, 0, size.w, size.h);

#ifdef ANDROID
		glOrthof(0.0f, size.x, 0.0f, size.y, 0.0f, 1.0f);
#else
//		glOrtho(0.0, size.x, 0.0, size.y, 0.0, 1.0);
#endif
		
		glMatrixMode(GL_MODELVIEW);
		ax::GL::Math::Matrix4 mv_matrix;
		mv_matrix.Identity().Load();
		
		// Projection matrix.
		glm::mat4 projMat = glm::ortho(0.0f, (float)size.w, 0.0f, (float)size.h);
		// glm::mat4 view(1.0f);
		// glm::mat4 model(1.0f);
		
		ax::GC::mvp_matrix = projMat;// * view * model;

		if (fct) {
			fct();
		}

#ifdef ANDROID
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, 0);
#else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
		
		// Reset old viewport.
		glViewport(0, 0, globalSize.w, globalSize.h);

#ifndef ANDROID // WHEN ANDROID IS NOT DEFINE.
		glPopAttrib();
#endif

		if (need_to_reactive_clip_test) {
			glEnable(GL_SCISSOR_TEST);
		}

	}

	void FrameBuffer::DrawFrameBuffer(const ax::Size& shownSize,
			ax::Point scroll, ax::Rect abs_rect, void* data)
	{
		if(_custom_draw_fb_func) {
			_custom_draw_fb_func(*this);
			return;
		}
		
		// ax::Print("DrawFB shownSize :", shownSize.x, shownSize.y);

		ax::GC::shader_fb.Activate();
		glEnable(GL_TEXTURE_2D);

		DrawingFrameBufferBlendFunction();

		ax::FPoint pos(0.0, 0.0);
		ax::FSize size(shownSize.w, shownSize.h);

		// Bind framebuffer texture.
		glBindTexture(GL_TEXTURE_2D, _frameBufferTexture);
		
		float vertices[8] = { pos.x, pos.y, pos.x, pos.y + size.h,
			pos.x + size.w, pos.y + size.h, pos.x + size.w, pos.y };

		float tex_coords[8] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
		
		GLuint prog_id = ax::GC::shader_fb.GetProgramId();
		GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");

		if(MatrixID == -1) {
			ax::console::Error("mvp_matrix doesn't exist in shader.");
		}

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)data);
		
		// Vertex coordinate.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);
		
		// Texture coordinate.
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
		glEnableVertexAttribArray(1);
		
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		
		glDisableVertexAttribArray(0);
//		 glDisableVertexAttribArray(5);
		glDisableVertexAttribArray(1);
		// glDisableVertexAttribArray(1);
		glDisable(GL_TEXTURE_2D);
	}

	void FrameBuffer::DrawingOnFrameBufferBlendFunction()
	{
#ifdef ANDROID
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            //glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
              //                     GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#else
		// All other blend function doesn't work except this one when
		// drawing multiple transparent frame buffer.
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		
//		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

#endif
	}

	void FrameBuffer::DrawingFrameBufferBlendFunction()
	{
#ifdef ANDROID
		glBlendFuncSeparate(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            //glBlendFuncSeparateOES(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
             //                      GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#else
		// This seem to be the only way to make the alpha and color
		// blend properly.
		glBlendFuncSeparate(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//		glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
//		glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
	}
	
	void FrameBuffer::AssignCustomFBDrawFunction(const std::function<void(FrameBuffer&)>& fct)
	{
		_custom_draw_fb_func = fct;
	}
	
	void FrameBuffer::AssignCustomFBDrawOnFunction(const std::function<void(FrameBuffer&)>& fct)
	{
		_custom_draw_on_fb_func = fct;
	}
	
	void FrameBuffer::ChangeTextureData(const ax::Size& size, void* data)
	{
		glBindTexture(GL_TEXTURE_2D, _frameBufferTexture);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.w, size.h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
}
}
