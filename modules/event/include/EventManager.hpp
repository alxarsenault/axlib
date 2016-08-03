/*
 * Copyright (c) 2015 Alexandre Arsenault.
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
#ifndef __AX_EVENT_MANAGER__
#define __AX_EVENT_MANAGER__

/// @defgroup event
/// @{

/**
 * @file    axEventManager
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   Event queue of axEventFunction (std::function<void(axMsg*)>).
 * @date    16/07/2014
 */

#include <deque>
#include <map>
#include <mutex>
#include "Event.hpp"
#include "Object.hpp"

extern std::mutex manager_mutex;

namespace ax {
class App;

namespace event {
	/**
	 * axEventManager.
	 */
	class Manager {
	public:
		Manager();

		Manager(std::function<void()> unblock_main_thread_fct);

		void AddConnection(const ID& id, const Id& evtId, Function fct);

		void PushEvent(const ID& id, const Id& evtId, Msg* msg);

		void CallNext();

		int GetEventQueueSize() const;

		void RemoveObjectConnection(const ID& id);

		void RemoveEventConnection(const ID& id, const Id& evtId);

	private:
		void AddFunction(axBindedEvent fct);

		typedef std::multimap<Id, Function> Multimap;
		typedef std::pair<const Id, Function> MultimapPair;

		typedef std::map<ID, Multimap> Map;
		typedef std::pair<ID, Multimap> MapPair;

		typedef std::deque<axBindedEvent> Queue;

		Queue _evtQueue;
		Map _event_fct_map;
		std::function<void()> _unblockMainThreadFct;
	};
}
}

/// @}
#endif // __AX_EVENT_MANAGER__