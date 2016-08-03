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

#ifndef __AX_WINDOW_NODE_VISITOR_H__
#define __AX_WINDOW_NODE_VISITOR_H__

/// @defgroup Core
/// @{

#include "Window.hpp"

namespace ax {
namespace NodeVisitor {
	
	void VisitFromNode(ax::Window* window, std::function<void(ax::Window*)> fct);
	
	void VisitFromChild(ax::Window* window, std::function<void(ax::Window*)> fct);
	
	ax::Window* FirstFindFromNode(ax::Window* window, std::function<bool(ax::Window*)> fct);
	
	ax::Window* FirstFindFromChild(ax::Window* window, std::function<bool(ax::Window*)> fct);
	
	std::vector<ax::Window*> AccumulateFromNode(ax::Window* window, std::function<bool(ax::Window*)> fct);
	
	std::vector<ax::Window*> AccumulateFromChild(ax::Window* window, std::function<bool(ax::Window*)> fct);
}
}

/// @}
#endif // __AX_WINDOW_NODE_VISITOR_H__
