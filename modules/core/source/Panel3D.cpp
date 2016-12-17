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

#include "Panel3D.hpp"

namespace ax {
Window3D::Window3D(const ax::Rect& rect)
{
	win = ax::Window::Create(rect);
}

void Window3D::Render3D()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//	ax::Rect rect(win->dimension.GetDrawingRect());

	// Calculate the aspect ratio of the window.
	//	double asp_ratio = rect.size.x / (double)rect.size.y;

	//	ax::Print("NOT GLU PERSPECTIVE.");
	// gluPerspective(45.0, asp_ratio, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_CULL_FACE);

	OnPaint3D(ax::GC());

	glDisable(GL_CULL_FACE);
}

void Window3D::RenderWindow()
{
#if _axBackBufferWindow_ == 1

	if (property.HasProperty("BackBuffer")) {
		if (state[NeedUpdate]) {
			dimension.GetFrameBuffer()->DrawOnFrameBuffer(
				[this]() {
					event.OnPaint(ax::GC());
					Render3D();

				},
				dimension.GetRect().size, ax::App::GetInstance().GetFrameSize());

			state[NeedUpdate] = false;
		}

		dimension.GetFrameBuffer()->DrawFrameBuffer(dimension.GetShownRect().size);
	}
	else {
		event.OnPaint(ax::GC());
		Render3D();
	}

#else // No back buffer.
	//        OnPaint();
	win->event.OnPaint(ax::GC());
	Render3D();
#endif //_axBackBufferWindow_
}
}
