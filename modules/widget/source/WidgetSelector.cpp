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
//#include "axWidgetSelector.h"
//
///*
// * axWidgetSelector::Info.
// */
//axWidgetSelector::Info::Info()
//{
//    
//}
//
//axWidgetSelector::Info::Info(const ax::Color& color):
//_color(color)
//{
//    
//}
//
///*
// * axWidgetSelector.
// */
//axWidgetSelector::axWidgetSelector(ax::App* app):
//axPanel(3, app, ax::Rect(0, 0, 20, 20)),
//_info(ax::Color(1.0, 0.33, 0.0)),
//_selectedWidget(nullptr)
//{
//    RemoveProperty("Selectable");
//    RemoveProperty("BackBuffer");
////    SetSelectable(false);
////    SetHasBackBuffer(false);
//    Hide();
//}
//
//void axWidgetSelector::SetSelectedWidget(ax::Window* win)
//{
//    _selectedWidget = win;
//    ax::Rect rect = win->GetAbsoluteRect();
//    
//    SetPosition(ax::Point(rect.position.x - 3, rect.position.y - 3));
//    SetSize(ax::Size(rect.size.x + 6, rect.size.y + 6));
//    
//    Show();
//}
//
//ax::Window* axWidgetSelector::GetSelectedWidget()
//{
//    return _selectedWidget;
//}
//
//void axWidgetSelector::OnPaint()
//{
//    if(_selectedWidget != nullptr && _selectedWidget->IsShown())
//    {
//        ax::Rect sel_rect = _selectedWidget->GetAbsoluteRect();
//        
//        SetPosition(ax::Point(sel_rect.position.x - 3, sel_rect.position.y - 3));
//        SetSize(ax::Size(sel_rect.size.x + 6, sel_rect.size.y + 6));
//        
//        ax::GC gc;
//        ax::Rect rect(GetDrawingRect());
//        
//        gc.SetColor(_info._color, 0.1);
//        gc.DrawRectangleContour(rect);
//        
//        gc.SetColor(_info._color, 0.2);
//        gc.DrawRectangleContour(rect.GetInteriorRect(ax::Point(0, 0)));
//        
//        gc.SetColor(_info._color, 0.4);
//        gc.DrawRectangleContour(rect.GetInteriorRect(ax::Point(1, 1)));
//        
//        gc.SetColor(_info._color, 0.5);
//        gc.DrawRectangleContour(rect.GetInteriorRect(ax::Point(2, 2)));
//    }
//
//}
