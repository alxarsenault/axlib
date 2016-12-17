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

#ifndef __AX_FRAME_BUFFER__
#define __AX_FRAME_BUFFER__

/*
 * @file    axFrameBuffer.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @date    18/02/2015
 */

/// @defgroup Graphic
/// @{

#include "Util.hpp"
#include <stdint.h>
#include <functional>

namespace ax {
namespace GL {
	class FrameBuffer {
	public:
		FrameBuffer(const ax::Size& size);

		~FrameBuffer();

		void Init(const ax::Size& size);

		void Resize(const ax::Size& size);

		void DrawOnFrameBuffer(
			const std::function<void()>& fct, const ax::Size& size, const ax::Size& globalSize);

		void DrawFrameBuffer(const ax::Size& shownSize, ax::Point scroll = ax::Point(0, 0),
			ax::Rect abs_rect = ax::Rect(0, 0, 100, 100), void* data = nullptr);

		inline unsigned int GetFrameBufferTexture()
		{
			return _frameBufferTexture;
		}

		void AssignCustomFBDrawFunction(const std::function<void(FrameBuffer&)>& fct);
		void AssignCustomFBDrawOnFunction(const std::function<void(FrameBuffer&)>& fct);

		// Don't call this unless you realy know what you are doing.
		void DrawingOnFrameBufferBlendFunction();
		void DrawingFrameBufferBlendFunction();

		void ChangeTextureData(const ax::Size& size, void* data);

	private:
		std::function<void(FrameBuffer&)> _custom_draw_fb_func;
		std::function<void(FrameBuffer&)> _custom_draw_on_fb_func;

#ifdef ANDROID
		unsigned int _frameBuffer, _frameBufferTexture, _depthBuffer;
#else
		uint32_t _frameBuffer, _frameBufferTexture; // _depthBuffer;
#endif
	};
}
}

/// @}
#endif // __AX_FRAME_BUFFER__
