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

#include <string>
#include <vector>

namespace ax {
namespace os {
	std::string ExecuteProgram(
		const std::string& folder, const std::string& path, const std::vector<std::string>& args);

	std::vector<const char*> GetCharVectorFromArgs(
		const std::string& prog_name, const std::vector<std::string>& args);

	std::string GetChildProgramOutput(const int& stdin_fd);
}
}

/// @}
