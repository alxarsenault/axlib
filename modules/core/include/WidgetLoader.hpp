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

#ifndef __AX_WIDGET_LOADER_H__
#define __AX_WIDGET_LOADER_H__

#include "Util.hpp"
#include "Window.hpp"
//#include "Xml.h"
#include "Widget.hpp"

namespace ax {
namespace widget {
	class Loader
	{
	public:
		static Loader* GetInstance();
		
		void AddBuilder(const std::string& name, ax::widget::Builder* builder);
		
		ax::widget::Builder* GetBuilder(const std::string& name);
	
	private:
		static std::shared_ptr<Loader> _instance;
		Loader();
		
		std::map<std::string, ax::widget::Builder*> _builders;
	};
}
}

#endif //__AX_WIDGET_LOADER_H__
