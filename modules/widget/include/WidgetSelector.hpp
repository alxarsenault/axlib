///*
// * Copyright (c) 2013 Alexandre Arsenault.
// *
// * This file is part of axFrameworks.
// *
// * axFrameworks is free or commercial software: you can redistribute it and/or
// * modify it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 or any later version of the
// * License or use a commercial axFrameworks License.
// *
// * axFrameworks is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with axFrameworks. If not, see <http://www.gnu.org/licenses/>.
// *
// * To release a closed-source product which uses axFrameworks, commercial
// * licenses are available, email alx.arsenault@gmail.com for more information.
// */
//#ifndef __AX_WIDGET_SELECTOR__
//#define __AX_WIDGET_SELECTOR__
//
///// @defgroup Widgets
///// @{
//
//#include "OpenAX.h"
//#include "axObjectLoader.h"
//
///*
// * axLabel.
// */
//class axWidgetSelector: public axPanel
//{
//public:
//    /*
//     * axWidgetSelector::Info.
//     */
//    class Info : public axInfo
//    {
//    public:
//        Info();
//        
//        Info(const ax::Color& color);
//
//        
//        ax::Color _color;
//    };
//
//    /*
//     * axWidgetSelector::axWidgetSelector.
//     */
//    axWidgetSelector(ax::App* app);
//    
//    void SetSelectedWidget(ax::Window* win);
//    
//    ax::Window* GetSelectedWidget();
//
//private:
//    ax::Window* _selectedWidget;
//    Info _info;
//    
//    // Events.
//    virtual void OnPaint();
//};
//
///// @}
///// @}
//#endif // __AX_WIDGET_SELECTOR__.