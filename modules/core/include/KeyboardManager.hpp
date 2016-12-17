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

/// @defgroup core
/// @{

#include "Util.hpp"
#include "Window.hpp"

namespace ax {
namespace core {
	class WindowTree;

	class KeyboardManager {
	public:
		KeyboardManager();

		void SetWindowTree(WindowTree* tree);

		void OnKeyDown(const char& key);
		void OnKeyUp(const char& key);
		void OnEnterDown();
		void OnKeyDeleteDown();
		void OnBackSpaceDown();
		void OnLeftArrowDown();
		void OnRightArrowDown();
		void OnUpArrowDown();
		void OnDownArrowDown();

		void OnCmdDown();

		void GrabKey(ax::Window* win);

		void UnGrabKey();

		void UnGrabKey(const ax::Window* win);

		bool IsKeyGrab(const ax::Window* win) const;

		bool IsCmdDown() const;

		void AddGlobalGrabedWindow(ax::Window* win);

		bool IsGlobalKeyGrabbed(const ax::Window* win);

		void UnGrabGlobalKey(const ax::Window* win);

		//	void SetPastKeyWindow(ax::Window* win);

		bool IsPastKeySelected(const ax::Window* win);

		void ClearKeyboardManager();

		void ClearGrabbedWindow();

		void ClearGlobalGrabbedWindows();

	private:
		WindowTree* _windowTree;
		ax::Window* _keyGrabbedWindow;

		std::vector<ax::Window*> _globalKeyGrabbed;

		bool _isCmdDown;
	};
}
}

/// @}
