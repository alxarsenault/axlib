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

#include "Plugin.hpp"
#include "FileSystem.hpp"

namespace ax {
namespace os {
	Plugin::Plugin()
		: _handle(nullptr)
	{
	}

	Plugin::Plugin(const std::string& plugin_path)
		: _plugin_path(plugin_path)
		, _handle(nullptr)
	{
		// Check path validity.
		Path ppath(_plugin_path);

		if (!ppath.IsValid()) {
			ax::util::console::Error("Invalid plugin path :", _plugin_path);
			return;
		}

		_handle = dlopen(_plugin_path.c_str(), RTLD_NOW | RTLD_LOCAL);

		if (_handle == nullptr) {
			ax::util::console::Error("Can't open plugin :", _plugin_path, "", dlerror());
		}
	}

	Plugin::~Plugin()
	{
		Close();
	}

	bool Plugin::Open(const std::string& plugin_path, bool reload)
	{
		// Check path validity.
		Path ppath(plugin_path);

		if (!ppath.IsValid()) {
			ax::util::console::Error("Invalid plugin path :", plugin_path);
			return false;
		}

		if (_handle != nullptr) {
			if (!reload) {
				ax::util::console::Warning("Plugin", _plugin_path, "is already loaded.");
				return false;
			}

			Close();
		}

		_plugin_path = plugin_path;
		_handle = dlopen(_plugin_path.c_str(), RTLD_NOW | RTLD_LOCAL);

		if (_handle == nullptr) {
			ax::util::console::Error("Can't open plugin :", _plugin_path);
			return false;
		}

		return true;
	}

	void Plugin::Close()
	{
		if (_handle != nullptr) {
			dlclose(_handle);
			_handle = nullptr;
		}
	}

	bool Plugin::IsOpen() const
	{
		return _handle != nullptr;
	}
} // os.
} // ax.