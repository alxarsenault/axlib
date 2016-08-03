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

#include "WindowManager.hpp"
#include "Window.hpp"
#include "App.hpp"
#include "Core.hpp"
#include "Config.hpp"

namespace ax {
namespace core {
	WindowManager::WindowManager()
		: MouseManager()
		, KeyboardManager()
	{
		MouseManager::SetWindowTree(&_windowTree);
		KeyboardManager::SetWindowTree(&_windowTree);
	}

	WindowManager::~WindowManager()
	{
	}

	void WindowManager::Add(Window* win)
	{
		//            _windowTree.AddWindow(win);
	}

	void WindowManager::OnPaint()
	{
		_windowTree.Draw();
	}

	void WindowManager::OnFocusIn()
	{
	}

	void WindowManager::OnUpdate()
	{
	}

	WindowTree* WindowManager::GetWindowTree()
	{
		return &_windowTree;
	}

	void WindowManager::OnSize(const ax::Size& size)
	{
		std::shared_ptr<ax::Window> win = _windowTree.GetTopLevel();
		
		if(win) {
			win->dimension.SetSize(size);
		}
	}
	
	void WindowManager::Clear()
	{
		ClearMouseManager();
		ClearKeyboardManager();
		_windowTree.GetNodeVector().clear();
	}
}
}
