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
#ifndef __AX_EVENT_MSG__
#define __AX_EVENT_MSG__

/// @defgroup event
/// @{

#include <string>

namespace ax {
namespace event {
	class Msg {
	public:
		Msg();

		virtual ~Msg();

		virtual Msg* GetCopy() = 0;
	};

	template <typename T> class SimpleMsg : public Msg {
	public:
		SimpleMsg(const T& msg)
			: _msg(msg)
		{
		}

		static SimpleMsg<T>& Cast(Msg* msg)
		{
			return *static_cast<SimpleMsg<T>*>(msg);
		}

		virtual Msg* GetCopy()
		{
			return new SimpleMsg<T>(*this);
		};

		T GetMsg() const
		{
			return _msg;
		}

	private:
		T _msg;
	};
	
	class EmptyMsg : public Msg {
	public:
		EmptyMsg()
		{
		}
		
		virtual Msg* GetCopy()
		{
			return new EmptyMsg();
		};
	};

	typedef SimpleMsg<std::string> StringMsg;
	typedef SimpleMsg<double> DoubleMsg;
}
}

/// @}
#endif // __AX_EVENT_MSG__
