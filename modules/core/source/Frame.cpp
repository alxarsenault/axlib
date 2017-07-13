/*
 * Copyright (c) 2017 Alexandre Arsenault.
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

#include "Frame.hpp"
#include "Engine.hpp"

#ifdef ANDROID
#elif axCoreX11
#elif _MSC_VER
#else // __APPLE__
#include "CocoaWindow.h"
#endif // __APPLE__

namespace ax {
Frame::Frame(const ax::Rect& rect)
{
#ifdef ANDROID
#elif axCoreX11
#elif _MSC_VER
#else // __APPLE__
	_frame = std::make_shared<cocoa::Window>(rect);
#endif // __APPLE__

//	_context_id = ax::rndr::Engine::GetInstance().CreateContext();
}

void Frame::SetSize(const ax::Size& size)
{
//	ax::rndr::Context* context = ax::rndr::Engine::GetInstance().GetContext(_context_id);
//	if (context == nullptr) {
//		return;
//	}
//
//	context->Resize(size);
	_frame->SetSize(size);
}
    
//    void Frame::SetDrawFunction(std::function<void()> df)
//    {
//        _frame->SetDrawFunction(df);
//    }
}
