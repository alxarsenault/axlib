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

/// @defgroup os
/// @{

#include "ConsolePrint.hpp"
#include <dlfcn.h>

namespace ax {
namespace os {
	/*
	 * Plugin
	 */
	class Plugin {
	public:
		Plugin();

		Plugin(const std::string& plugin_path);

		~Plugin();

		bool Open(const std::string& plugin_path, bool reload = false);

		void Close();

		bool IsOpen() const;

		template <typename R, typename... A> std::function<R(A...)> GetFunction(const std::string& fct_name)
		{
			if (!IsOpen()) {
				ax::util::console::Error("Plugin is not yet loaded.");
				return std::function<R(A...)>();
			}

			std::function<R(A...)> fct = reinterpret_cast<R (*)(A...)>(dlsym(_handle, fct_name.c_str()));

			// Check if function exist in plugin.
			char* error = dlerror();
			if (error) {
				ax::util::console::Error("Cannot load function", fct_name, "from plugin ", _plugin_path);
				ax::util::console::Error(
					"Either function doesn't exist or hasn't been exported as extern C.");
				ax::util::console::Error("Use extern \"C\" { <function declaration> } in C++ files.");

				return std::function<R(A...)>();
			}

			return std::move(fct);
		}

	private:
		std::string _plugin_path;
		void* _handle;
	};
} // os.
} // ax.

/// @}