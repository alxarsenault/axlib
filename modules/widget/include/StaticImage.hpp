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
//#ifndef __AX_STATIC_IMAGE__
//#define __AX_STATIC_IMAGE__
//
///// @defgroup Widgets
///// @{
//
///// @defgroup StaticImage
///// @{
//
//#include "axLib.h"
//#include "axObjectLoader.h"
//
///*
// * axStaticImage.
// */
//class axStaticImage: public axPanel
//{
//public:
//    axStaticImage(ax::Window* parent, const ax::Rect& rect, const std::string& path);
//    
//    axStaticImage(ax::Window* parent, const ax::Rect& rect, ax::Image* img);
//    
//    /*
//     * axStaticImageBuilder.
//     */
//    class axStaticImageBuilder
//    {
//    public:
//        axStaticImageBuilder(ax::Window* win);
//        
//        axStaticImage* Create(ax::StringPairVector attributes);
//        
//    private:
//        ax::Window* _parent;
//        std::string _path;
//        ax::Rect _rect;
//        ax::Size _size;
//        ax::Image* _img;
//    };
//    
//private:
//    ax::Image* _img;
//    
//    // Events.
//    virtual void OnPaint();
//};
//
//
///// @}
///// @}
//#endif // __AX_STATIC_IMAGE__.