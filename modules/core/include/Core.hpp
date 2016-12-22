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

#pragma once

/// @defgroup Core
/// @{

#include "EventManager.hpp"
#include "WindowManager.hpp"
#include <memory>
#include <time.h>

namespace ax {
namespace core {

	class Core {
	public:
		Core();

		virtual void MainLoop() = 0;

		virtual void Init(const ax::Size& frame_size) = 0;

		virtual void ResizeGLScene(const ax::Size& size);

		virtual bool CreateGLWindow(const char* title, int width, int height, int bits) = 0;

		virtual std::string GetAppDirectory() = 0;

		virtual std::string GetAppPath()
		{
			return "";
		}

		virtual ax::Rect GetScreenRect() = 0;

		virtual ax::Size GetScreenSize() = 0;

		virtual std::string OpenFileDialog() = 0;

		virtual std::string SaveFileDialog()
		{
			return "";
		}

		virtual void PushEventOnSystemQueue() = 0;

		virtual void ResizeFrame(const ax::Size& size) = 0;

		virtual void KillGLWindow() = 0;

		int InitGL();

		enum Cursor {
			NORMAL,
			RESIZE_UP_DOWN,
			RESIZE_LEFT_RIGHT,
			RESIZE_TOP_LEFT_DOWN_RIGHT,
			RESIZE_BOTTOM_LEFT_TOP_RIGHT,
			MOVE
		};

		void SetCursor(const Cursor& cursor_id)
		{
			if (_cursor_id != cursor_id) {
				_cursor_id = cursor_id;
				SetCoreCursor(_cursor_id);
			}
		}

		inline std::shared_ptr<ax::event::Manager> GetEventManager()
		{
			return _evtManager;
		}

		virtual ax::core::WindowManager* GetWindowManager();

		virtual ax::core::WindowManager* GetPopupManager();

		virtual ax::core::WindowManager* GetRealPopWindowManager();

		virtual ax::core::WindowManager* GetEditorWindowManager()
		{
			return _editor_manager.get();
		}

		//		virtual ax::Size GetFrameSize() const = 0;

		//		virtual void SetFrameSize(const ax::Size& size) = 0;

		ax::Size GetFrameSize() const;

		void SetGlobalSize(const ax::Size& size);

		virtual void UpdateAll();

		virtual void HideMouse()
		{
		}

		virtual void ShowMouse()
		{
		}

		virtual void SetResizable(bool resizable)
		{
		}

		virtual void SetTitleBar(bool titlebar)
		{
		}

		virtual void SetFocusAndCenter()
		{
		}

		virtual std::string GetPasteboardContent()
		{
			return "";
		}

		virtual int DrawGLScene();

		/// Add a GUI init main entry callback function.
		/// This function will be call when the ax::Core is done initializing.
		inline void AddMainEntry(std::function<void()> fct)
		{
			_mainEntryFunction = fct;
		}

		/// Add a callback function to load after the GUI is loaded.
		inline void AddAfterGUILoadFunction(std::function<void()> fct)
		{
			_afterGuiLoadFunction = fct;
		}

		/// Call the main entry callback..
		/// This function should only be called by the ax::Core or any backend
		/// implementatiion.
		void CallMainEntryFunction();

		/// Call the after gui load callback when the gui is done loading.
		/// This function should only be called by the ax::Core or any backend
		/// implementatiion.
		void CallAfterGUILoadFunction();

	protected:
		std::shared_ptr<ax::event::Manager> _evtManager;

		std::unique_ptr<ax::core::WindowManager> _windowManager;
		std::unique_ptr<ax::core::WindowManager> _popupManager;
		std::unique_ptr<ax::core::WindowManager> _editor_manager;
		std::unique_ptr<ax::core::WindowManager> _realPopWindowManager;

		bool _needToDraw, _popupNeedToDraw;
		ax::Size _size, _popSize;
		Cursor _cursor_id = NORMAL;

		std::function<void()> _mainEntryFunction; /// Main GUI callback.
		std::function<void()> _afterGuiLoadFunction; /// After GUI callback.

		virtual void InitManagers();

		virtual void SetCoreCursor(const Cursor& cursor_id)
		{
		}
	};
}
}

/// @}
