/*
 * Copyright (c) 2017 Alexandre Arsenault.
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

#pragma once

#include "Util.hpp"
#include "FrameInterface.hpp"

namespace ax {

class Frame {
public:
	Frame(const ax::Rect& rect);

	void SetSize(const ax::Size& size);
    
//    void SetDrawFunction(std::function<void()> df);

private:
	std::shared_ptr<FrameInterface> _frame;
//    unsigned long _context_id;
};
} // ax.

/// @}
