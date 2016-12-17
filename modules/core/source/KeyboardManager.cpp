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

#include "KeyboardManager.hpp"
#include "Window.hpp"
#include "WindowTree.hpp"

namespace ax {
namespace core {
	KeyboardManager::KeyboardManager()
		: _windowTree(nullptr)
		, _keyGrabbedWindow(nullptr)
		, _isCmdDown(false)
	{
	}

	void KeyboardManager::SetWindowTree(WindowTree* tree)
	{
		_windowTree = tree;
	}

	//	void KeyboardManager::SetPastKeyWindow(ax::Window* win)
	//	{
	//		_keyGrabbedWindow = win;
	//	}

	bool KeyboardManager::IsPastKeySelected(const ax::Window* win)
	{
		return false;
	}

	void KeyboardManager::AddGlobalGrabedWindow(ax::Window* win)
	{
		// Prevent from adding twice.
		if (IsGlobalKeyGrabbed(win) == false) {
			_globalKeyGrabbed.push_back(win);
		}
	}

	bool KeyboardManager::IsGlobalKeyGrabbed(const ax::Window* win)
	{
		for (auto& n : _globalKeyGrabbed) {
			if (n == win) {
				return true;
			}
		}

		return false;
	}

	void KeyboardManager::UnGrabGlobalKey(const ax::Window* win)
	{
		int index = -1;

		for (int i = 0; i < _globalKeyGrabbed.size(); i++) {
			if (_globalKeyGrabbed[i] == win) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			_globalKeyGrabbed.erase(_globalKeyGrabbed.begin() + index);
		}
	}

	bool KeyboardManager::IsCmdDown() const
	{
		return _isCmdDown;
	}

	void KeyboardManager::OnKeyDown(const char& key)
	{
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnKeyDown(key);
		}

		for (auto& n : _globalKeyGrabbed) {
			n->event.OnKeyDown(key);
		}
	}

	void KeyboardManager::OnEnterDown()
	{
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnEnterDown('0');
		}

		for (auto& n : _globalKeyGrabbed) {
			n->event.OnEnterDown('0');
		}
	}

	void KeyboardManager::OnKeyUp(const char& key)
	{
	}

	void KeyboardManager::OnBackSpaceDown()
	{
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnBackSpaceDown('0');
		}

		for (auto& n : _globalKeyGrabbed) {
			n->event.OnBackSpaceDown('0');
		}
	}

	void KeyboardManager::GrabKey(ax::Window* win)
	{
		if (_keyGrabbedWindow != win) {
			if (_keyGrabbedWindow != nullptr) {
				_keyGrabbedWindow->event.OnWasKeyUnGrabbed('0');
			}

			win->event.OnWasKeyGrabbed('0');
		}

		_keyGrabbedWindow = win;
	}

	void KeyboardManager::UnGrabKey()
	{
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnWasKeyUnGrabbed('0');
			_keyGrabbedWindow = nullptr;
		}
	}

	void KeyboardManager::UnGrabKey(const ax::Window* win)
	{
		if (_keyGrabbedWindow != nullptr && (win == _keyGrabbedWindow)) {
			_keyGrabbedWindow->event.OnWasKeyUnGrabbed('0');
			_keyGrabbedWindow = nullptr;
		}
	}

	bool KeyboardManager::IsKeyGrab(const ax::Window* win) const
	{
		return (win == _keyGrabbedWindow);
	}

	void KeyboardManager::ClearKeyboardManager()
	{
		_keyGrabbedWindow = nullptr;
		_globalKeyGrabbed.clear();
	}

	void KeyboardManager::ClearGrabbedWindow()
	{
		_keyGrabbedWindow = nullptr;
	}

	void KeyboardManager::ClearGlobalGrabbedWindows()
	{
		_globalKeyGrabbed.clear();
	}

	void KeyboardManager::OnLeftArrowDown()
	{
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnLeftArrowDown('0');
		}

		for (auto& n : _globalKeyGrabbed) {
			n->event.OnLeftArrowDown('0');
		}
	}

	void KeyboardManager::OnRightArrowDown()
	{
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnRightArrowDown('0');
		}

		for (auto& n : _globalKeyGrabbed) {
			n->event.OnRightArrowDown('0');
		}
	}

	void KeyboardManager::OnUpArrowDown()
	{
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnUpArrowDown('0');
		}

		for (auto& n : _globalKeyGrabbed) {
			n->event.OnUpArrowDown('0');
		}
	}

	void KeyboardManager::OnDownArrowDown()
	{
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnDownArrowDown('0');
		}

		for (auto& n : _globalKeyGrabbed) {
			n->event.OnDownArrowDown('0');
		}
	}

	void KeyboardManager::OnKeyDeleteDown()
	{
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnKeyDeleteDown('0');
		}

		for (auto& n : _globalKeyGrabbed) {
			n->event.OnKeyDeleteDown('0');
		}
	}

	void KeyboardManager::OnCmdDown()
	{
		_isCmdDown = !_isCmdDown;

		if (_keyGrabbedWindow != nullptr) {
			if (_isCmdDown) {
				_keyGrabbedWindow->event.OnCmdDown('0');
			}
			else {
				_keyGrabbedWindow->event.OnCmdUp('0');
			}
		}

		for (auto& n : _globalKeyGrabbed) {
			if (_isCmdDown) {
				n->event.OnCmdDown('0');
			}
			else {
				n->event.OnCmdUp('0');
			}
		}
	}
}
}
