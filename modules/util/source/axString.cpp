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

#include "axString.hpp"
#include <algorithm>

namespace ax {
namespace util {
	namespace String {
		std::string GetExtension(const std::string& path)
		{
			std::size_t last_dot = path.find_last_of(".");

			if (last_dot == std::string::npos) {
				return "";
			}

			return std::string(path.substr(last_dot + 1));
		}

		std::vector<std::string> Split(const std::string& str, const std::string& delimiter)
		{
			std::vector<std::string> vec;

			std::string r = str;
			size_t pos = 0;
			std::string token;

			while ((pos = r.find(delimiter)) != std::string::npos) {
				token = r.substr(0, pos);
				vec.push_back(token);
				r.erase(0, pos + delimiter.length());
			}

			vec.push_back(r);

			return vec;
		}

		void ReplaceCharWithString(std::string& input_str, const char& c, const std::string& replacement)
		{
			std::size_t dist = 0;

			while (dist < input_str.size()) {
				auto it
					= std::find_if(input_str.begin() + dist, input_str.end(), [c](char x) { return x == c; });

				if (it == input_str.end()) {
					return;
				}

				dist = std::distance(input_str.begin(), it);
				input_str.replace(dist, 1, replacement);
			}
		}
	}
}
}
