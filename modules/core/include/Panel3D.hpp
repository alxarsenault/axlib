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

#ifndef __AX_PANEL_3D_H__
#define __AX_PANEL_3D_H__

/// @defgroup Core
/// @{

#include "axlib.hpp"
#include "Render.hpp"
#include "RenderMath.hpp"

namespace ax {
class Window3D : public ax::Window::Backbone {
public:
	Window3D(const ax::Rect& rect);

	void Render3D();

	virtual void RenderWindow();

	ax::Window::Event::Function<ax::GC> OnPaint3D;

	//		virtual void OnPaint3D() {}
};
}

/// @}
#endif // __AX_PANEL_3D_H__
