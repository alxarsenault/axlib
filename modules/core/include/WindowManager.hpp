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
 
#ifndef __AX_MANAGER__
#define __AX_MANAGER__

/// @defgroup Core
/// @{

#include <map>
#include "Object.hpp"
#include "Math.hpp"
#include "WindowTree.hpp"

#include "MouseManager.hpp"
#include "KeyboardManager.hpp"

namespace ax {
namespace core {
	/*
	 * ax::core::WindowManager.
	 */
	class WindowManager : public MouseManager, public KeyboardManager {
	public:
		WindowManager();

		~WindowManager();

		void Add(ax::Window* win);

		// Events.
		void OnPaint();
		void OnFocusIn();
		void OnUpdate();
		void OnSize(const ax::Size& size);

		std::string _managerName;
		WindowTree* GetWindowTree();
		
		void Clear();

	private:
		WindowTree _windowTree;
	};
}
}

/// @}
#endif //__AX_MANAGER__
