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

#include "App.hpp"
#include "Config.hpp"
#include "Core.hpp"
#include "GraphicInterface.hpp"
#include "RenderMath.hpp"
#include "Window.hpp"
#include "WindowTree.hpp"
#include <algorithm>

namespace ax {
namespace core {
	WindowTree::WindowTree()
	{
	}

	void WindowTree::AddTopLevel(std::shared_ptr<ax::Window> win)
	{
		_nodes.push_back(win);
	}

	std::shared_ptr<ax::Window> WindowTree::GetTopLevel()
	{
		if (_nodes.size()) {
			return _nodes[0];
		}

		return nullptr;
	}

	ax::Window* WindowTree::FindMousePosition(const ax::Point& pos)
	{
		std::shared_ptr<ax::Window> node = nullptr;

		// Find first level window in the vector of window with nullptr as
		// parent. There should normally be only one window in this vector.
		for (std::shared_ptr<ax::Window> it : _nodes) {
			ax::Point position = it->dimension.GetAbsoluteRect().position;
			ax::Rect rect(position, it->dimension.GetShownRect().size);

			if (rect.IsPointInside(pos)) {
				node = it;
			}
		}

		// There is either no window in the vector or the window(s) do not
		// cover the entire frame superficy.
		if (node == nullptr) {
			return nullptr;
		}

		// This would normally start with the main window if there was only one
		// window in the vector (_nodes).
		std::shared_ptr<ax::Window> n;

		do { // Look for the deepest child window with mouse over it.
			n = node;

			std::vector<std::shared_ptr<ax::Window>>& childs = n->node.GetChildren();

			// Search for child window backward.
			// This imply that if two windows are superpose, the last
			// one added will have priority.
			for (auto iter = childs.rbegin(); iter != childs.rend(); ++iter) {
				std::shared_ptr<ax::Window> it = *iter;

				ax::Point position = it->dimension.GetAbsoluteRect().position;
				ax::Rect rect(position, it->dimension.GetShownRect().size);
				rect.position += it->dimension.GetScrollDecay();

				// If child is shown and mouse is over child.
				if (it->IsShown() && rect.IsPointInside(pos)) {
					// If window is selectable then node is found.
					if (it->property.HasProperty("Selectable")) {
						// This will go out of the for loop and keep
						// looking deeper in child nodes of the window.
						node = it;
						break;
					}
				}
			}

			// When n == node then there's no more window deeper with mouse over it.
		} while (n != node);

		// These condition should normally never be false.
		if (node != nullptr && node->IsShown()) {
			return node.get();
		}

		return nullptr;
	}

	void WindowTree::Draw()
	{
		for (std::shared_ptr<ax::Window> it : _nodes) {
			if (it != nullptr) {
				it->node.Draw();
			}
		}
	}

	std::vector<std::shared_ptr<ax::Window>>& WindowTree::GetNodeVector()
	{
		return _nodes;
	}
}
}
