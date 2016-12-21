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

#include "Var.hpp"
#include <string>
#include <map>
#include <mutex>

namespace ax {
namespace util {

	/// @todo Add a remove resource function.
	class ResourceStorage {
	public:
		ResourceStorage();

		~ResourceStorage();

		void Add(std::string id, Var value);

		Var GetResource(const std::string& id);

		void Lock()
		{
			_resourceMutex.lock();
		}

		void Unlock()
		{
			_resourceMutex.unlock();
		}

	private:
		std::map<std::string, Var> _resourceMap;

		typedef std::map<std::string, Var>::iterator MapIterator;
		typedef std::pair<std::string, Var> Pair;

		std::mutex _resourceMutex;
	};
}
}

/// @}
