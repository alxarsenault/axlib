/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axlib.
 *
 * axlib is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axlib License.
 *
 * axlib is distributed in the hope that it will be useful,
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

#include "Var.hpp"

bool ax::Var::is_null() const
{
	return ptr == nullptr ? true : false;
}

bool ax::Var::not_null() const
{
	return ptr == nullptr ? false : true;
}