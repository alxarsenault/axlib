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
//#include "axStaticImage.h"
//
//
///*
// * axStaticImageBuilder.
// */
// axStaticImage::axStaticImageBuilder::axStaticImageBuilder(ax::Window* win):
//_parent(win)
//{
//
//}
//
// axStaticImage* axStaticImage::axStaticImageBuilder::
// Create(ax::StringPairVector attributes)
//{
//    std::string name;
//    ax::Point pos;
//    for(auto& s : attributes)
//    {
//        if(s.first == "name")
//        {
//            name = s.second;
//        }
//        else if(s.first == "pos")
//        {
//            ax::StringVector strVec;
//            strVec = ax::Utils::String::Split(s.second, ",");
////            strVec = GetVectorFromStringDelimiter(s.second, ",");
//
//            pos = ax::Point(stoi(strVec[0]),
//                          stoi(strVec[1]));
//        }
//        else if(s.first == "path")
//        {
//            _img = new ax::Image(s.second);
//            _size = _img->GetSize();
//        }
//    }
//
//    axStaticImage* img = new axStaticImage(_parent, ax::Rect(pos, _size),
//                                           _img);
//
//    _parent->GetResourceManager()->Add(name, img);
//    return img;
//}
//
//
///*
// * axStaticImage.
// */
// axStaticImage::axStaticImage(ax::Window* parent,
//                             const ax::Rect& rect,
//                             const std::string& path):
// axPanel(parent, rect)
//{
//    _img = new ax::Image(path);
////    SetSelectable(false);
//    RemoveProperty("Selectable");
//}
//
// axStaticImage::axStaticImage(ax::Window* parent,
//                             const ax::Rect& rect,
//                             ax::Image* img):
// axPanel(parent, rect),
//_img(img)
//
//{
////    SetSelectable(false);
//    RemoveProperty("Selectable");
//}
//
// void axStaticImage::OnPaint()
//{
////    axGC* gc = GetGC();
//    ax::GC gc = ax::GC();
//    gc.DrawImage(_img, ax::Point(0, 0));
//}
