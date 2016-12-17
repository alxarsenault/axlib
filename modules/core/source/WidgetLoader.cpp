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

#include "WidgetLoader.hpp"

namespace ax {
namespace widget {
	std::shared_ptr<Loader> Loader::_instance = nullptr;

	Loader* Loader::GetInstance()
	{
		if (_instance == nullptr) {
			_instance.reset(new Loader());
		}
		return _instance.get();
	}

	Loader::Loader()
	{
	}

	void Loader::AddBuilder(const std::string& name, ax::widget::Builder* builder)
	{
		auto it = _builders.find(name);

		if (it == _builders.end()) {
			_builders.insert(std::pair<std::string, ax::widget::Builder*>(name, builder));
		}
	}

	ax::widget::Builder* Loader::GetBuilder(const std::string& name)
	{
		auto it = _builders.find(name);

		if (it != _builders.end()) {
			return it->second;
		}

		return nullptr;
	}
}
}