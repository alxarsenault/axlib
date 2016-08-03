/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axLib.
 *
 * axLib is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axFrameworks License.
 *
 * axLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLib. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLib, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#pragma once

/// @defgroup util
/// @{

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

namespace ax {
namespace util {

	class Component {
	public:
		typedef std::shared_ptr<Component> Ptr;

		Component()
		{
		}
		
		virtual ~Component()
		{
//			std::cout << "Delete componetn." << std::endl;
		}
	};

	class ComponentMap : public std::unordered_map<std::string, Component::Ptr> {
	public:
		ComponentMap()
		{
		}
		
		~ComponentMap()
		{
//			std::cout << "Delete componetn map." << std::endl;
		}

		void Add(const std::string& name, Component::Ptr component)
		{
			insert(std::pair<std::string, Component::Ptr>(name, component));
		}

		Component::Ptr Get(const std::string& name)
		{
			auto it = find(name);

			if (it != end()) {
				return it->second;
			}

			return nullptr;
		}

		template <typename T> typename T::Ptr Get(const std::string& name)
		{
			auto it = find(name);

			if (it != end()) {
				return typename T::Ptr(std::static_pointer_cast<T>(it->second));
			}

			return nullptr;
		}

		inline bool Has(const std::string& name)
		{
			return find(name) == this->end() ? false : true;
		}
	};
}
}

/// @}
