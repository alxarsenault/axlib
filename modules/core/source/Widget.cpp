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

#include "Widget.hpp"

namespace ax {
namespace widget {
	/*
	 * ax::Info.
	 */
	Info::Info()
	{
	}

	Info::~Info()
	{
	}

	Info::Info(const std::string& path)
		: _path(path)
	{
		if (_path.size()) {
			_isEditable = true;
		}
	}

	std::string Info::GetPath() const
	{
		return _path;
	}

	bool Info::IsEditable() const
	{
		return _isEditable;
	}

	std::vector<std::string> Info::GetParamNameList() const
	{
		return std::vector<std::string>();
	}

	void Info::SetAttribute(const std::pair<std::string, std::string>& attribute)
	{
	}

	void Info::SetAttributes(const std::vector<std::pair<std::string, std::string>>& attributes)
	{
		for (auto& n : attributes) {
			SetAttribute(n);
		}
	}

	std::string Info::GetAttributeValue(const std::string& name)
	{
		return "";
	}

	/*
	 * ax::WidgetComponent.
	 */
	Component::Component(ax::Window* win, Info* info)
		: _win(win)
		, _info(info)
		, _isEditable(false)
		, _isInfoEditable(false)
		, _acceptChild(false)
	{
	}

	Component::~Component()
	{
		if (_info) {
			delete _info;
			_info = nullptr;
		}
	}

	bool Component::IsEditable() const
	{
		return _isEditable;
	}

	bool Component::IsInfoEditable() const
	{
		return _isInfoEditable;
	}

	bool Component::AcceptChild() const
	{
		return _acceptChild;
	}

	void Component::SetInfo(const std::vector<std::pair<std::string, std::string>>& att)
	{
	}

	Info* Component::GetInfo()
	{
		return _info;
	}

	void Component::SetBuilderAttributes(const std::vector<std::pair<std::string, std::string>>& att)
	{
	}

	std::vector<std::pair<std::string, std::string>> Component::GetBuilderAttributes()
	{
		return std::vector<std::pair<std::string, std::string>>();
	}
}
}