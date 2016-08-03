/*
 * Copyright (c) 2013 Alexandre Arsenault.
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
#include "Object.hpp"
#include "EventManager.hpp"

namespace ax {
namespace event {
	ID Object::_global_id_count = 0;

	ID Object::IncrementGlobalIdCount()
	{
		return ++_global_id_count;
	}

	Object::Object(Manager* evtManager)
		: _evtManager(evtManager)
		, _id(IncrementGlobalIdCount())
	{
	}

	Object::Object(std::shared_ptr<Manager> evtManager)
		: _evtManager(evtManager.get())
		, _id(IncrementGlobalIdCount())
	{
	}

	Object::~Object()
	{
//		std::cout << "Delete object id : " << _id << std::endl;
	}

	void Object::AddConnection(const Id& evtId, Function fct) const
	{
		_evtManager->AddConnection(_id, evtId, fct);
	}

	void Object::PushEvent(const Id& evtId, Msg* msg)
	{
		_evtManager->PushEvent(_id, evtId, msg);
	}

	void Object::ChangeId(const ID& id)
	{
		_id = id;
	}

	void Object::AddEventFunction(const std::string& name, Function fct)
	{
		_evtMap.insert(std::pair<std::string, Function>(name, fct));
	}

	Function Object::GetEventFunction(const std::string& name)
	{
		std::map<std::string, Function>::iterator it = _evtMap.find(name);

		if (it != _evtMap.end()) {
			return it->second;
		}

		return nullptr;
	}
}
}
