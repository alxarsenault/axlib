/*
 * Copyright (c) 2016 Alexandre Arsenault.
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

#ifndef __AX_CONFIG__
#define __AX_CONFIG__

/*
 * @file    axConfig
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axConfig.
 * @date    13/01/2015
 */

/// @defgroup Core
/// @{

// Operationg system.
#define _AX_MAC_ (1)
#define _AX_WIN32_ (0)
#define _AX_LINUX_ (0)

// Core implementation.
#define _AX_COCOA_ (0)
#define _AX_X11__ (1)
#define _AX_DIRECT_FB_ (0)
#define _AX_WX_WIDGET_ (0)

#define _axDebugEditor_ (1)
#define _axBackBufferWindow_ (1)
#define _axWxWidgetsCore_ (1)

/// @}
#endif //__AX_CONFIG__