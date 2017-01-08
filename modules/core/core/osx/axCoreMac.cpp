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

#include "axCoreMac.hpp"
#include "CocoaInterface.h"
#include <unistd.h>
#include <fst/print.h>

namespace ax {
namespace core {
	CoreMac::CoreMac()
	{
	}

	void CoreMac::MainLoop()
	{
		fst::print(ptrace);
		_cocoa_app.run();
	}

	void CoreMac::Init(const ax::Size& frame_size)
	{
		InitManagers();

		// This will create CocoaAppDelegate.
		_cocoa_view = std::make_shared<cocoa::OpenGLView>(this, frame_size);
		_cocoa_app.setDelegate(_cocoa_view->GetDelegate());
		SetGlobalSize(frame_size);
	}

	ax::Size CoreMac::GetScreenSize()
	{
		return cocoa::GetScreenSize();
	}

	std::string CoreMac::GetAppDirectory()
	{
		return std::string(cocoa::GetAppDirectory() + std::string("/"));
	}

	std::string CoreMac::GetAppPath()
	{
		return std::string(cocoa::GetAppPath() + std::string("/"));
	}

	ax::Rect CoreMac::GetScreenRect()
	{
		return ax::Rect(0, 0, cocoa::GetScreenSize());
	}

	void CoreMac::KillGLWindow()
	{
	}

	bool CoreMac::CreateGLWindow(const char* title, int width, int height, int bits)
	{
		return true;
	}

	void CoreMac::UpdateAll()
	{
		Core::UpdateAll();
		_cocoa_view->RefreshView();
	}

	void CoreMac::ResizeFrame(const ax::Size& size)
	{
		fst::print(ptrace);
		_cocoa_view->SetFrameSize(size);
		ResizeGLScene(size);
	}

	std::string CoreMac::OpenFileDialog()
	{
		return cocoa::OpenFileDialog();
	}

	std::string CoreMac::SaveFileDialog()
	{
		return cocoa::SaveFileDialog();
	}

	void CoreMac::PushEventOnSystemQueue()
	{
		cocoa::AddEventToDispatchQueue();
	}

	void CoreMac::HideMouse()
	{
		cocoa::HideMouse();
	}

	void CoreMac::ShowMouse()
	{
		cocoa::ShowMouse();
	}

	void CoreMac::SetResizable(bool resizable)
	{
		_cocoa_view->SetResizable(resizable);
	}

	void CoreMac::SetTitleBar(bool titlebar)
	{
		_cocoa_view->SetTitleBar(titlebar);
	}

	void CoreMac::SetFocusAndCenter()
	{
		_cocoa_view->SetFocusAndCenter();
	}

	void CoreMac::SetCoreCursor(const Cursor& cursor_id)
	{
		_cocoa_view->SetCursor(cursor_id);
	}

	std::string CoreMac::GetPasteboardContent()
	{
		return cocoa::GetPasteboardContent();
	}
	
	void CoreMac::SetPasteboardContent(const std::string& str)
	{
		cocoa::SetPasteboardContent(str);
	}
}
}
