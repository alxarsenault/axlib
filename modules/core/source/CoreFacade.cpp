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

#include "CoreFacade.hpp"

#ifdef ANDROID
#include "axCoreAndroid.h"
//#include "axCoreX11.h"
//#endif //__linux__

#elif WAYLAND
#include "axCoreWayland.h"

#elif axCoreX11
#include "axCoreX11.h"

#elif _MSC_VER
#if _axWxWidgetsCore_ == 1
#include "axCoreWxWidgets.h"

#else
#include "axCoreWin32.h"
#endif // _axWxWidgetsCore_.
//#endif //_MSC_VER

#else // __APPLE__
#ifdef AX_EOS_CORE
#include "axCoreEOS.h"
#else
#include "axCoreMac.hpp"
#endif // _AX_VST_APP_
#endif // __APPLE__

namespace ax {
namespace core {
	Facade::Facade(const ax::Size& frame_size)
	{
#ifdef ANDROID
		_core = new axCoreAndroid();
		_core->Init(frame_size);
		_core->SetGlobalSize(frame_size);
#elif defined(WAYLAND)
		_core = new ax::CoreWayland();
		_core->Init(frame_size);
		_core->SetGlobalSize(frame_size);
#elif defined(axCoreX11)
		_core = new ax::Core::X11();
		_core->Init(frame_size);
		_core->SetGlobalSize(frame_size);
#elif defined(_MSC_VER)
		_core = new axCoreWin32();
		axCORE = _core;
		_core->Init(frame_size);
#else // __APPLE__

#ifdef AX_EOS_CORE
		_core = new ax::CoreEOS();
		_core->Init(frame_size);
		_core->SetGlobalSize(frame_size);
#else
		//		ax::Print("Facade _core = new axCoreMac");
		_core = new CoreMac();
		_core->SetGlobalSize(frame_size);
//_core->Init(frame_size);
#endif // _AX_VST_APP_

#endif // __APPLE__
	}

	Facade::Facade(const ax::Size& frame_size, Core* core)
	{
		_core = core;
		//		_core->Init(frame_size);
		_core->SetGlobalSize(frame_size);
	}

	void Facade::Init(const ax::Size& frame_size)
	{
		_core->Init(frame_size);
	}

	std::string Facade::GetAppDirectory()
	{
		return _core->GetAppDirectory();
	}

	std::string Facade::GetAppPath()
	{
		return _core->GetAppPath();
	}

	std::string Facade::OpenFileDialog()
	{
		return _core->OpenFileDialog();
	}

	std::string Facade::SaveFileDialog()
	{
		return _core->SaveFileDialog();
	}

	ax::Rect Facade::GetScreenRect()
	{
		return _core->GetScreenRect();
	}

	ax::Size Facade::GetScreenSize()
	{
		return _core->GetScreenSize();
	}

	void Facade::SetCursor(const Core::Cursor& cursor_id)
	{
		_core->SetCursor(cursor_id);
	}

	ax::Size Facade::GetFrameSize() const
	{
		return _core->GetGlobalSize();
	}

	void Facade::SetFrameSize(const ax::Size& size)
	{
		_core->ResizeFrame(size);
	}

	void Facade::SetFocusAndCenter()
	{
		_core->SetFocusAndCenter();
	}

	ax::core::WindowManager* Facade::GetWindowManager()
	{
		return _core->GetWindowManager();
	}

	ax::core::WindowManager* Facade::GetPopupManager()
	{
		return _core->GetPopupManager();
	}

	ax::core::WindowManager* Facade::GetRealPopWindowManager()
	{
		return _core->GetRealPopWindowManager();
	}

	void Facade::UpdateAll()
	{
		_core->UpdateAll();
	}

	void Facade::HideMouse()
	{
		_core->HideMouse();
	}

	void Facade::ShowMouse()
	{
		_core->ShowMouse();
	}

	int Facade::Draw()
	{
		return _core->DrawGLScene();
	}

	void Facade::SetResizable(bool resizable)
	{
		_core->SetResizable(resizable);
	}

	void Facade::SetTitleBar(bool titlebar)
	{
		_core->SetTitleBar(titlebar);
	}

	std::string Facade::GetPasteboardConent()
	{
		return _core->GetPasteboardContent();
	}

	void Facade::MainLoop()
	{
		_core->MainLoop();
	}

	void Facade::PushEventOnSystemQueue()
	{
		_core->PushEventOnSystemQueue();
	}

	Core* Facade::GetCore()
	{
		return _core;
	}
}
}
