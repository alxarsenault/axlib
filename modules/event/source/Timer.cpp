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
#include "Timer.hpp"

namespace ax {
namespace event {
	//*
	// ax::Event::Timer::Msg
	//*
	Timer::Msg::Msg(const TimeMs& t)
		: _time(t)
	{
	}

	Timer::TimeMs Timer::Msg::GetTime() const
	{
		return _time;
	}

	ax::event::Msg* Timer::Msg::GetCopy()
	{
		return new Msg(*this);
	}

	//*
	// ax::Event::Timer
	//*
	Timer::Timer(Manager* evtManager, const Function& fct)
		: ax::event::Object(evtManager)
		, _isRunning(false)
	{
		AddConnection(TIMER_ID, fct);
	}

	Timer::Timer(Manager* evtManager)
		: Object(evtManager)
		, _isRunning(false)
	{
	}

	Timer::Timer(std::shared_ptr<Manager> evtManager, const Function& fct)
		: ax::event::Object(evtManager)
		, _isRunning(false)
	{
		AddConnection(TIMER_ID, fct);
	}

	Timer::Timer(std::shared_ptr<Manager> evtManager)
		: Object(evtManager)
		, _isRunning(false)
	{
	}

	bool Timer::IsRunning() const
	{
		return _isRunning;
	}

	void Timer::StartTimer(const TimeMs& interval_ms, const TimeMs& length_ms)
	{
		timer_mutex.lock();

		_isRunning = true;

		timer_mutex.unlock();

		// Return true if the thread object identifies an active thread
		// of execution, false otherwise.
		if (_timerThread.joinable() == false) {
			_timerThread = std::thread(timer_thread, std::ref(*this), interval_ms, length_ms);
		}
	}

	void Timer::StartTimer(const TimeMs& interval_ms)
	{
		timer_mutex.lock();

		_isRunning = true;

		timer_mutex.unlock();

		// Return true if the thread object identifies an active thread
		// of execution, false otherwise.
		if (_timerThread.joinable() == false) {
			_timerThread = std::thread(timer_thread_no_end, std::ref(*this), interval_ms);
		}
	}

	void Timer::StopTimer()
	{
		timer_mutex.lock();
		_isRunning = false;
		timer_mutex.unlock();

		if (_timerThread.joinable()) {
			_timerThread.join();
		}

		_timerThread = std::thread();
	}

	void Timer::timer_thread_no_end(Timer& timer, const TimeMs& interval_ms)
	{
		TimeMs count_ms(0);

		while (timer.IsRunning()) {
			timer.PushEvent(0, new Timer::Msg(count_ms));
			count_ms += interval_ms;

			std::this_thread::sleep_for(interval_ms);
		}
	}

	void Timer::timer_thread(Timer& timer, const TimeMs& interval_ms, const TimeMs& length_ms)
	{
		TimeMs count_ms(0);

		while (count_ms < length_ms) {
			timer.PushEvent(TIMER_ID, new Timer::Msg(count_ms));
			count_ms += interval_ms;
			std::this_thread::sleep_for(interval_ms);
		}
	}
}
}
