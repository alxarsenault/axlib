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

#include "Flag.hpp"

namespace ax {
namespace util {
	bool HasFlag(const Flag& flag_to_verity, Flag flags)
	{
		return ((flags & flag_to_verity) != 0);
	}
	
	void SetFlag(const Flag& flag_to_set, bool value, Flag& flags)
	{
		if(value) {
			flags |= flag_to_set;
			return;
		}
		
		flags &= ~(flag_to_set);
	}

	namespace FlagValue {
		const Flag NO_FLAG = 0;
		const Flag FLAG_1 = 1;
		const Flag FLAG_2 = 2;
		const Flag FLAG_3 = 4;
		const Flag FLAG_4 = 8;
		const Flag FLAG_5 = 16;
		const Flag FLAG_6 = 32;
		const Flag FLAG_7 = 64;
		const Flag FLAG_8 = 128;
		const Flag FLAG_9 = 256;
		const Flag FLAG_10 = 512;
		const Flag FLAG_11 = 1024;
		const Flag FLAG_12 = 2048;
		const Flag FLAG_13 = 4096;
		const Flag FLAG_14 = 8192;
		const Flag FLAG_15 = 16384;
		const Flag FLAG_16 = 32768;
	}
} // util.
} // ax.
