/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axLibrary.
 *
 * axLibrary is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axLibrary License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLibrary. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLibrary, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#include "MouseManager.hpp"
#include "Window.hpp"
#include "WindowTree.hpp"

namespace ax {
namespace core {

	MouseManager::MouseManager()
		: _windowTree(nullptr)
		, _mouseCaptureWindow(nullptr)
		, _pastWindow(nullptr)
		, _currentWindow(nullptr)
		, _scrollCaptureWindow(nullptr)
		, _evtHasReachWindow(false)
	{
	}

	void MouseManager::SetWindowTree(WindowTree* tree)
	{
		_windowTree = tree;
	}

	bool MouseManager::IsEventReachWindow() const
	{
		return _evtHasReachWindow;
	}

	void MouseManager::VerifyAndProcessWindowChange()
	{
		if (_pastWindow != _currentWindow) {
			ax::Window* last_past = _pastWindow;
			_pastWindow = _currentWindow;

			// Mouse leave event first.
			if (last_past != nullptr) {
				last_past->event.OnMouseLeave(_mousePosition);

				/// @todo This is called a lot for nothing.
				/// 	  Realy not a good idea but practical.
				ax::Window* win = last_past->node.GetParent();

				while (win) {
					win->event.OnMouseLeaveChild(_mousePosition);
					win = win->node.GetParent();
				}
			}

			// Then mouse enter event.
			if (_currentWindow != nullptr) {
				_currentWindow->event.OnMouseEnter(_mousePosition);

				// Enter one of child window.
				ax::Window* win = _currentWindow->node.GetParent();

				/// @todo This is called a lot for nothing.
				/// 	  Realy not a good idea but practical.
				while (win) {
					win->event.OnMouseEnterChild(_mousePosition);
					win = win->node.GetParent();
				}
			}
		}
	}

	void MouseManager::OnMouseLeftDragging(const ax::Point& pos)
	{
		if (_mouseCaptureWindow != nullptr) {
			_mouseCaptureWindow->event.OnMouseLeftDragging(pos);
			_evtHasReachWindow = true;
		}
		else {
			_evtHasReachWindow = false;
		}
	}

	void MouseManager::OnMouseMotion(const ax::Point& pos)
	{
		_mousePosition = pos;

		// Only for Windows and Linux
		if (_mouseCaptureWindow != nullptr) {
			_mouseCaptureWindow->event.OnMouseLeftDragging(pos);
			_evtHasReachWindow = true;
		}
		else {
			ax::Window* win = _windowTree->FindMousePosition(pos);

			if (win != nullptr && win->property.HasProperty("Selectable")) {
				_currentWindow = win;

				if (_currentWindow != nullptr) {
					_currentWindow->event.OnMouseMotion(pos);
					_evtHasReachWindow = true;
				}
				else {
					_evtHasReachWindow = false;
				}

				VerifyAndProcessWindowChange();
			}
			else {
				_evtHasReachWindow = false;
			}
		}
	}

	void MouseManager::OnMouseLeftDoubleClick(const ax::Point& pos)
	{
		_mousePosition = pos;

		//	ax::Print("OnMouseLeftDoubleClick");

		if (_mouseCaptureWindow != nullptr) {
			//		ax::Print("Captured");
			//		_mouseCaptureWindow->event.OnMouseLeftDoubleClick(pos);
			//		_evtHasReachWindow = true;
		}
		else {
			//		ax::Print("Not Captured");
			ax::Window* win = _windowTree->FindMousePosition(pos);

			_currentWindow = win;

			if (win != nullptr) {
				ax::console::Print("Win id :", win->GetId());
				win->event.OnMouseLeftDoubleClick(pos);
				_evtHasReachWindow = true;
				//			ax::Print("Win not null");
			}
			else {
				_evtHasReachWindow = false;
			}

			VerifyAndProcessWindowChange();
		}
	}

	void MouseManager::OnMouseLeftDown(const ax::Point& pos)
	{
		_mousePosition = pos;

		if (_global_click_listener.size()) {
			for (auto& n : _global_click_listener) {
				ax::Window::Event::GlobalClick msg;
				msg.type = ax::Window::Event::GlobalClick::LEFT_CLICK_DOWN;
				msg.pos = pos;
				n->event.OnGlobalClick(msg);
			}
		}

		// If mouse is already grabbed.
		if (_mouseCaptureWindow != nullptr) {
			_mouseCaptureWindow->event.OnMouseLeftDown(pos);
			_evtHasReachWindow = true;
		}
		else {

			ax::Window* win = _windowTree->FindMousePosition(pos);

			if (win != nullptr && win->property.HasProperty("Selectable")) {
				_currentWindow = win;

				if (win != nullptr) {
					win->event.OnMouseLeftDown(pos);
					_evtHasReachWindow = true;
				}
				else {
					_evtHasReachWindow = false;
				}

				VerifyAndProcessWindowChange();
			}
			else {
				_evtHasReachWindow = false;
			}
		}
	}

	void MouseManager::OnMouseRightDown(const ax::Point& pos)
	{
		_mousePosition = pos;

		if (_global_click_listener.size()) {
			for (auto& n : _global_click_listener) {
				ax::Window::Event::GlobalClick msg;
				msg.type = ax::Window::Event::GlobalClick::RIGHT_CLICK_DOWN;
				msg.pos = pos;
				n->event.OnGlobalClick(msg);
			}
		}

		if (_mouseCaptureWindow) {
			_mouseCaptureWindow->event.OnMouseRightDown(pos);
			_evtHasReachWindow = true;
		}
		else {
			ax::Window* win = _windowTree->FindMousePosition(pos);
			_currentWindow = win;

			if (win != nullptr) {

				win->event.OnMouseRightDown(pos);
				_evtHasReachWindow = true;
			}
			else {
				_evtHasReachWindow = false;
			}

			VerifyAndProcessWindowChange();
		}
	}

	void MouseManager::OnMouseLeftUp(const ax::Point& pos)
	{
		_mousePosition = pos;

		if (_global_click_listener.size()) {
			for (auto& n : _global_click_listener) {
				ax::Window::Event::GlobalClick msg;
				msg.type = ax::Window::Event::GlobalClick::LEFT_CLICK_UP;
				msg.pos = pos;
				n->event.OnGlobalClick(msg);
			}
		}

		// If mouse is already grabbed.
		if (_mouseCaptureWindow != nullptr) {
			_mouseCaptureWindow->event.OnMouseLeftUp(pos);
			_evtHasReachWindow = true;
		}
		else {

			ax::Window* win = _windowTree->FindMousePosition(pos);

			if (win != nullptr && win->property.HasProperty("Selectable")) {
				_currentWindow = win;

				if (win != nullptr) {
					win->event.OnMouseLeftUp(pos);
					_evtHasReachWindow = true;
				}
				else {
					_evtHasReachWindow = false;
				}

				VerifyAndProcessWindowChange();
			}
			else {
				_evtHasReachWindow = false;
			}
		}

		//		if (_mouseCaptureWindow) {
		//			_currentWindow = _windowTree->FindMousePosition(pos);
		//			_mouseCaptureWindow->event.OnMouseLeftUp(pos);
		//			_evtHasReachWindow = true;
		//		}
		//		else {
		//			ax::Window* win = _windowTree->FindMousePosition(pos);
		//			_currentWindow = win;
		//
		//			if (win != nullptr) {
		//				win->event.OnMouseLeftUp(pos);
		//				_evtHasReachWindow = true;
		//			}
		//			else {
		//				_evtHasReachWindow = false;
		//			}
		//
		//			VerifyAndProcessWindowChange();
		//		}
	}

	void MouseManager::OnScrollWheel(const ax::Point& delta)
	{
		if (_scrollCaptureWindow == nullptr) {
			_evtHasReachWindow = false;
			return;
		}

		_scrollCaptureWindow->event.OnScrollWheel(delta);
		_evtHasReachWindow = true;
	}

	void MouseManager::OnMouseRightUp()
	{
		_evtHasReachWindow = false;
	}

	void MouseManager::ReleaseMouseHover()
	{
		_currentWindow = nullptr;
		_pastWindow = nullptr;
	}

	void MouseManager::GrabMouse(ax::Window* win)
	{
		_mouseCaptureWindow = win;
	}

	void MouseManager::UnGrabMouse()
	{
		_mouseCaptureWindow = nullptr;
	}

	void MouseManager::UnGrabMouse(const ax::Window* win)
	{
		if (_mouseCaptureWindow == win) {
			_mouseCaptureWindow = nullptr;
		}
	}

	bool MouseManager::IsGrab(const ax::Window* win) const
	{
		return _mouseCaptureWindow == win;
	}

	bool MouseManager::IsMouseHoverWindow(const ax::Window* win) const
	{
		return (win == _currentWindow);
	}

	void MouseManager::GrabScroll(ax::Window* win)
	{
		_scrollCaptureWindow = win;
	}

	void MouseManager::UnGrabScroll()
	{
		_scrollCaptureWindow = nullptr;
	}

	void MouseManager::UnGrabScroll(const ax::Window* win)
	{
		if (_scrollCaptureWindow == win) {
			_scrollCaptureWindow = nullptr;
		}
	}

	bool MouseManager::IsScrollGrabbed(const ax::Window* win)
	{
		return _scrollCaptureWindow == win;
	}

	bool MouseManager::IsMouseStillInChildWindow(const ax::Window* win) const
	{
		ax::Window* w = _currentWindow;

		while (w != nullptr) {
			if (w == win) {
				return true;
			}

			w = w->node.GetParent();
		}

		return false;
	}

	void MouseManager::SetPastWindow(ax::Window* win)
	{
		_pastWindow = win;
	}

	void MouseManager::RemoveIfPastWindow(const ax::Window* win)
	{
		if (_pastWindow == win) {
			_pastWindow = nullptr;
		}
	}

	void MouseManager::GrabGlobalMouse(ax::Window* win)
	{
		// Prevent from adding twice.
		if (IsGlobalMouseGrabbed(win) == false) {
			_global_click_listener.push_back(win);
		}
	}

	void MouseManager::UnGrabGlobalMouse(ax::Window* win)
	{
		int index = -1;

		for (int i = 0; i < _global_click_listener.size(); i++) {
			if (_global_click_listener[i] == win) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			_global_click_listener.erase(_global_click_listener.begin() + index);
		}
	}

	void MouseManager::ClearGlobalMouseGrab()
	{
		_global_click_listener.clear();
	}

	bool MouseManager::IsGlobalMouseGrabbed() const
	{
		return (bool)_global_click_listener.size();
	}

	bool MouseManager::IsGlobalMouseGrabbed(const ax::Window* win) const
	{
		for (auto& n : _global_click_listener) {
			if (n == win) {
				return true;
			}
		}

		return false;
	}
}
}