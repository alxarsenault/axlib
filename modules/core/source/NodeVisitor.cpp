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

#include "NodeVisitor.hpp"

namespace ax {
namespace NodeVisitor {
	void VisitFromNode(ax::Window* window, std::function<void(ax::Window*)> fct)
	{
		if (window == nullptr) {
			return;
		}
		
		fct(window);
		
		std::vector<std::shared_ptr<ax::Window>>& children = window->node.GetChildren();
		
		for (auto& n : children) {
			VisitFromNode(n.get(), fct);
		}
	}
	
	void VisitFromChild(ax::Window* window, std::function<void(ax::Window*)> fct)
	{
		if (window == nullptr) {
			return;
		}
		
		std::vector<std::shared_ptr<ax::Window>>& children = window->node.GetChildren();
		
		for (auto& n : children) {
			VisitFromNode(n.get(), fct);
		}
	}
	
	ax::Window* FirstFindFromNode(ax::Window* window, std::function<bool(ax::Window*)> fct)
	{
		if (window == nullptr) {
			return nullptr;
		}
		
		if (fct(window)) {
			return window;
		}
		
		std::vector<std::shared_ptr<ax::Window>>& children = window->node.GetChildren();
		
		for (auto& n : children) {
			ax::Window* tmp = FirstFindFromNode(n.get(), fct);
			if (tmp != nullptr) {
				return tmp;
			}
		}
		
		return nullptr;
	}
	
	ax::Window* FirstFindFromChild(ax::Window* window, std::function<bool(ax::Window*)> fct)
	{
		if (window == nullptr) {
			return nullptr;
		}
		
		std::vector<std::shared_ptr<ax::Window>>& children = window->node.GetChildren();
		
		for (auto& n : children) {
			ax::Window* tmp = FirstFindFromNode(n.get(), fct);
			if (tmp != nullptr) {
				return tmp;
			}
		}
		
		return nullptr;
	}
	
	void RecursiveAccumulate(ax::Window* window, std::vector<ax::Window*>& accumulation, std::function<bool(ax::Window*)> fct)
	{
		if (window == nullptr) {
			return;
		}
		
		if(fct(window)) {
			accumulation.push_back(window);
		}
		
		std::vector<std::shared_ptr<ax::Window>>& children = window->node.GetChildren();
		
		for (auto& n : children) {
			RecursiveAccumulate(n.get(), accumulation, fct);
		}
	}
	
	std::vector<ax::Window*> AccumulateFromNode(ax::Window* window, std::function<bool(ax::Window*)> fct)
	{
		std::vector<ax::Window*> accumulation;
		
		if (window == nullptr) {
			return accumulation;
		}
		
		if(fct(window)) {
			accumulation.push_back(window);
		}
		
		std::vector<std::shared_ptr<ax::Window>>& children = window->node.GetChildren();
		
		for (auto& n : children) {
			RecursiveAccumulate(n.get(), accumulation, fct);
		}
		
		return accumulation;
	}
	
	std::vector<ax::Window*> AccumulateFromChild(ax::Window* window, std::function<bool(ax::Window*)> fct)
	{
		std::vector<ax::Window*> accumulation;
		
		if (window == nullptr) {
			return accumulation;
		}
		
		std::vector<std::shared_ptr<ax::Window>>& children = window->node.GetChildren();
		
		for (auto& n : children) {
			RecursiveAccumulate(n.get(), accumulation, fct);
		}
		
		return accumulation;
	}
}
} // namespace ax
