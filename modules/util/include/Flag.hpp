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

#include <stdint.h>

/// @defgroup util
/// @{

namespace ax {
namespace util {
	typedef uint16_t Flag;

	bool HasFlag(const Flag& flag_to_verity, Flag flags);

	void SetFlag(const Flag& flag_to_set, bool value, Flag& flags);

	namespace FlagValue {
		extern const Flag NO_FLAG;
		extern const Flag FLAG_1;
		extern const Flag FLAG_2;
		extern const Flag FLAG_3;
		extern const Flag FLAG_4;
		extern const Flag FLAG_5;
		extern const Flag FLAG_6;
		extern const Flag FLAG_7;
		extern const Flag FLAG_8;
		extern const Flag FLAG_9;
		extern const Flag FLAG_10;
		extern const Flag FLAG_11;
		extern const Flag FLAG_12;
		extern const Flag FLAG_13;
		extern const Flag FLAG_14;
		extern const Flag FLAG_15;
		extern const Flag FLAG_16;
	}
} // util.
} // ax.

/// @}
