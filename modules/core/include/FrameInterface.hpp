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
#include "Context.hpp"
#include "shader.h"
#include <functional>
#include <fst/print.h>

namespace ax {

class FrameInterface {
public:
    FrameInterface();
    
	virtual void SetSize(const ax::Size& size) = 0;
    
    void OnTest()
    {
        fst::print("DEBUG TEST :", _debug_int);
    }
    
    void Init(const ax::Size& size);
    
    void OnDraw(const ax::Size& size);
    
//    inline void OnDraw() {
//        fst::print("ONDRAW", _debug_int);
//        if(_on_draw_fct) {
//            _on_draw_fct();
//        }
//    }
    
//    inline void SetDrawFunction(std::function<void()> df) {
//        _on_draw_fct = df;
//    }
    
private:
//    std::function<void()> _on_draw_fct = nullptr;
    int _debug_int;
    unsigned long _context_id;
    ax::rndr::shader _shader;
};
} // ax.

/// @}
