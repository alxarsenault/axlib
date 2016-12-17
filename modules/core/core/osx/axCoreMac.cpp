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

/// @todo Put in axLib core lib.
#include "axCocoaInterfaceMac.h"
#include <unistd.h>

namespace ax {
namespace core {
	CoreMac::CoreMac()
	{
	}

	void CoreMac::MainLoop()
	{
		//	std::cout << "MainLoop" << std::endl;
		axCallNSApplicationMain();
	}

	void CoreMac::Init(const ax::Size& frame_size)
	{
		//		std::cout << "Init axCoreMac." << std::endl;
		InitManagers();
		InitGL();
		ResizeFrame(frame_size);
		//    _size = frame_size;
	}

	ax::Size CoreMac::GetScreenSize()
	{
		return axCocoaGetScreenSize();
	}

	std::string CoreMac::GetAppDirectory()
	{
		return std::string(CocoaGetAppDirectory() + std::string("/"));
	}

	std::string CoreMac::GetAppPath()
	{
		return std::string(CocoaGetAppPath() + std::string("/"));
	}

	// bool axCoreMac::CreatePopupWindow(const char* title, int width, int height)
	//{
	//    return false;
	//}

	ax::Rect CoreMac::GetScreenRect()
	{
		return ax::Rect(0, 0, axCocoaGetScreenSize());
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
		TestFunctionInterface();
	}

	void CoreMac::ResizeFrame(const ax::Size& size)
	{
		axCocoaResizeFrame(size);
		ResizeGLScene(size);
	}

	std::string CoreMac::OpenFileDialog()
	{
		return axOpenFileDialog();
	}

	std::string CoreMac::SaveFileDialog()
	{
		return axSaveFileDialog();
	}

	void CoreMac::PushEventOnSystemQueue()
	{
		AddEventToDispatchQueue();
	}

	void CoreMac::HideMouse()
	{
		axCocoaHideMouse();
	}

	void CoreMac::ShowMouse()
	{
		axCocoaShowMouse();
	}

	void CoreMac::SetResizable(bool resizable)
	{
		axCocoaSetResizable(resizable);
	}

	void CoreMac::SetTitleBar(bool titlebar)
	{
		axCocoaSetTitleBar(titlebar);
	}

	void CoreMac::SetFocusAndCenter()
	{
		axCocoaSetFocusAndCenter();
	}

	void CoreMac::SetCoreCursor(const Cursor& cursor_id)
	{
		axCocoaChangeMouseCursor(cursor_id);
	}

	std::string CoreMac::GetPasteboardContent()
	{
		return axCocoaGetPasteboardContent();
	}
}
}
