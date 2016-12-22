/*
 * Copyright (c) 2016 Alexandre Arsenault.
 * Copyright (c) 2015 Philippe Groarke.
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

#ifndef __AX_APP_H__
#define __AX_APP_H__

/*
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @author  Philippe Groarke <philippe.groarke@gmail.com>
 * @brief   Main application singleton. Creates and manages the application.
 */

/// @defgroup Core
/// @{

#include "CoreFacade.hpp"
#include "Event.hpp"
#include "Window.hpp"

#include <memory>
#include <mutex>
#include <thread>

namespace ax {

namespace event {
	class Manager;
}

namespace util {
	class ResourceStorage;
}

/*
 * Starting point of any application.
 * It is the highest abstraction of the ax::Core for user simplicity.
 */
class App : public core::Facade {
public:
	/// Create or access the application.
	static ax::App& GetInstance();

	static ax::App* Create(core::Core* core);

	/// Use this before getInstance to set your application window size.
	static inline void SetSize(const ax::Size& appSize)
	{
		_frameSize = appSize;
	}

	//	inline std::shared_ptr<ax::event::Manager> GetEventManager()
	//	{
	//		return _evtManager;
	//	}

	/// Store data accessible from any windows in app.
	/// Use the resource storage lock mecanisme for multi-thread use.
	inline std::shared_ptr<ax::util::ResourceStorage> GetResourceManager()
	{
		return _resourceManager;
	}

	//	/// Add a GUI init main entry callback function.
	//	/// This function will be call when the ax::Core is done initializing.
	//	inline void AddMainEntry(std::function<void()> fct)
	//	{
	//		_mainEntryFunction = fct;
	//	}
	//
	//	/// Add a callback function to load after the GUI is loaded.
	//	inline void AddAfterGUILoadFunction(std::function<void()> fct)
	//	{
	//		_afterGuiLoadFunction = fct;
	//	}

	//	/// Call the main entry callback..
	//	/// This function should only be called by the ax::Core or any backend
	//	/// implementatiion.
	//	void CallMainEntryFunction();
	//
	//	/// Call the after gui load callback when the gui is done loading.
	//	/// This function should only be called by the ax::Core or any backend
	//	/// implementatiion.
	//	void CallAfterGUILoadFunction();

	/// Add the main window.
	void AddTopLevel(std::shared_ptr<ax::Window> win);

	void AddTopLevel(std::shared_ptr<ax::Window::Backbone> win);

	void AddPopupTopLevel(std::shared_ptr<ax::Window> win);

	void AddPopupTopLevel(std::shared_ptr<ax::Window::Backbone> win);

	std::shared_ptr<ax::Window> GetTopLevel();

	void CloseApplication();

	inline std::string AppOpenFilePath() const
	{
		return _app_open_file_path;
	}

	inline void SetAppOpenFilePath(const std::string& path)
	{
		_app_open_file_path = path;
	}

protected:
	static ax::Size _frameSize;
	App();
	//	std::function<void()> _mainEntryFunction; /// Main GUI callback.
	//	std::function<void()> _afterGuiLoadFunction; /// After GUI callback.
	std::string _app_open_file_path;

private:
	/* Singleton */
	static std::shared_ptr<ax::App> _instance;
	static std::once_flag _onlyOne;

	App(const ax::App& a);
	App(core::Core* core);
	App& operator=(const ax::App& a);

	/* Managers */
	//	std::shared_ptr<ax::event::Manager> _evtManager;
	std::shared_ptr<ax::util::ResourceStorage> _resourceManager;
};
}

/// @}
#endif // __AX_APP_H__
