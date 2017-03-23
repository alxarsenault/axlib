/*
 * Copyright (c) 2013 Alexandre Arsenault.
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

#pragma once

//#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>

#include "Core.hpp"
#include "CocoaApplication.h"
#include "CocoaOpenGLView.h"

namespace ax {
namespace core {
	class CoreMac : public Core {
	public:
		CoreMac();

		virtual void MainLoop();

		virtual void Init(const ax::Size& frame_size);

		virtual std::string GetAppDirectory();

		virtual std::string GetAppPath();

		virtual ax::Rect GetScreenRect();

		virtual ax::Size GetScreenSize();

		virtual std::string OpenFileDialog();

		virtual std::string SaveFileDialog();

		virtual void PushEventOnSystemQueue();

		virtual void KillGLWindow();

		virtual bool CreateGLWindow(const char* title, int width, int height, int bits);

		virtual void UpdateAll();

		virtual void ResizeFrame(const ax::Size& size);

		virtual void HideMouse();

		virtual void ShowMouse();

		virtual void SetCoreCursor(const Cursor& cursor_id);

		virtual void SetResizable(bool resizable);

		virtual void SetTitleBar(bool titlebar);

		virtual void SetBorderLess();

		virtual void SetDefaultBorder();

		virtual void SetFocusAndCenter();

		virtual std::string GetPasteboardContent();

		virtual void SetPasteboardContent(const std::string& str);

		void CreateWindow();

	private:
		cocoa::Application _cocoa_app;
		std::shared_ptr<cocoa::OpenGLView> _cocoa_view;
	};
} // ax.
} // core.

//#endif // __APPLE__
