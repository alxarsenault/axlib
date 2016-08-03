///*
// * Copyright (c) 2015 Alexandre Arsenault.
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
//#include "axRadio.h"
//#include "axObjectLoader.h"
//
///*
// * axToggle::axToggle.
// */
// axRadio::axRadio(ax::Window* parent,
//                 const ax::Rect& rect,
//                 const axRadio::Events& events,
//                 const axRadio::Info& info,
//                 std::string img_path,
//                 std::string label,
//                 ax::Flag flags,
//                 std::string msg) :
//// Heritage.
// axToggle(parent, rect, events, info, img_path, label, flags, msg)
//{
//
//}
//
// void axRadio::OnPaint()
//{
//    ax::GC gcs = ax::GC();
//    ax::GC* gc = &gcs;
//	ax::Rect rect(GetRect());
//	ax::Rect rect0(GetDrawingRect());
//
//	gc->SetColor(*_currentColor);
//    gc->SetSmoothLine(1);
//    gc->DrawPoint(rect0.GetMiddle(), 5);
////    gc->SetSmoothLine(2);
////    gc->DrawCircle(rect0.GetMiddle(), rect.size.x * 0.5 - 2, 50);
////    gc->SetDefaultLine();
////    gc->DrawRoundedRectangle(rect0, 8);
////	gc->DrawRectangle(rect0);
//
//	if (_bgImg->IsImageReady())
//	{
//        if (static_cast<Info*>(_info)->single_img)
//		{
//			gc->DrawImageResize(_bgImg, ax::Point(0, 0), rect.size, 1.0);
//		}
//		else
//		{
//            ax::Point pos(0, _nCurrentImg * _bgImg->GetSize().y / 6);
//            ax::Size size(_bgImg->GetSize().x, _bgImg->GetSize().y / 6);
//            gc->DrawPartOfImageResize(_bgImg, pos, size,
//                                      ax::Rect(ax::Point(0, 0), GetRect().size));
//		}
//	}
//}
//
////	if_not_empty(_label)
////	{
////        if (static_cast<Info*>(_info)->single_img)
////		{
////			gc->DrawImageResize(_bgImg, ax::Point(0, 0), rect.size, 1.0);
////		}
////		else
////		{
////            ax::Point pos(0, _nCurrentImg * _bgImg->GetSize().y / 6);
////            ax::Size size(_bgImg->GetSize().x, _bgImg->GetSize().y / 6);
////            gc->DrawPartOfImageResize(_bgImg, pos, size,
////                                      ax::Rect(ax::Point(0, 0), dimension.GetRect().size));
////		}
////	}
////
//////	if_not_empty(_label)
//////	{
//////        if(_selected)
//////        {
//////            gc->SetColor(static_cast<Info*>(_info)->selected_font_color);
//////        }
//////        else
//////        {
//////            gc->SetColor(static_cast<Info*>(_info)->font_color);
//////        }
//////
//////		gc->DrawStringAlignedCenter(*_font, _label, rect0);
//////	}
////
////	gc->SetColor(static_cast<Info*>(_info)->contour);
////    gc->SetSmoothLine(1);
////    gc->DrawCircle(rect0.GetMiddle(), rect.size.x * 0.5 - 2, 50);
////    gc->SetDefaultLine();
//////	gc->DrawRectangleContour(rect0);
//////    gc->DrawRoundedRectangleContour(rect0, 8);
////}
////
////
