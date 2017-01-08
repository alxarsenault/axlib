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

#include "Util.hpp"
#include "Core.hpp"
#include <string>

namespace ax {
namespace core {

	class WindowManager;

	class Facade {
	public:
		Facade(const ax::Size& frame_size);

		Facade(const ax::Size& frame_size, Core* core);

		void Init(const ax::Size& frame_size);

		std::string GetAppDirectory();

		std::string GetAppPath();

		std::string OpenFileDialog();

		std::string SaveFileDialog();

		ax::Rect GetScreenRect();

		ax::Size GetScreenSize();

		ax::Size GetFrameSize() const;

		void SetFrameSize(const ax::Size& size);

		inline std::shared_ptr<ax::event::Manager> GetEventManager()
		{
			return _core->GetEventManager();
		}

		ax::core::WindowManager* GetWindowManager();

		ax::core::WindowManager* GetPopupManager();

		ax::core::WindowManager* GetRealPopWindowManager();

		void UpdateAll();

		void HideMouse();

		void ShowMouse();

		int Draw();

		virtual void MainLoop();

		void SetCursor(const Core::Cursor& cursor_id);

		void SetResizable(bool resizable);

		void SetTitleBar(bool titlebar);

		void SetFocusAndCenter();

		std::string GetPasteboardConent();
		
		inline void SetPasteboardContent(const std::string& str) {
			_core->SetPasteboardContent(str);
		}

		/// Add a GUI init main entry callback function.
		/// This function will be call when the ax::Core is done initializing.
		inline void AddMainEntry(std::function<void()> fct)
		{
			_core->AddMainEntry(fct);
		}

		/// Add a callback function to load after the GUI is loaded.
		inline void AddAfterGUILoadFunction(std::function<void()> fct)
		{
			_core->AddAfterGUILoadFunction(fct);
		}

		/// ax::App -> ax::core::Facade should be use instead of this.
		/// You better know what you are doing when you're using this function.
		Core* GetCore();

	protected:
		void PushEventOnSystemQueue();

	private:
		Core* _core;
	};
}
}
