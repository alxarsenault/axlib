///*
// * Copyright (c) 2016 Alexandre Arsenault.
// *
// * This file is part of OpenAX.
// *
// * OpenAX is free or commercial software: you can redistribute it and/or
// * modify it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 or any later version of the
// * license or use a commercial OpenAX License.
// *
// * OpenAX is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with OpenAX. If not, see <http://www.gnu.org/licenses/>.
// *
// * To release a closed-source product which uses OpenAX, commercial
// * licenses are available, email ax.frameworks@gmail.com for more information.
// */
//
//#ifndef __AX_TEXT_CONTROL__
//#define __AX_TEXT_CONTROL__
//
///// @defgroup Widgets
///// @{
//
///// @defgroup TextControl
///// @{
//
//#include "axlib.hpp"
//
/////*
//// * axTextControlFlags.
////*/
////#define axTEXT_CTRL_FLASHING_CURSOR      ax::util::FlagValue::FLAG_1
////#define axTEXT_CTRL_CONTOUR_HIGHLIGHT    ax::util::FlagValue::FLAG_2
////#define axTEXT_CTRL_CONOUR_NO_FADE       ax::util::FlagValue::FLAG_3
////
//// class axTextControl;
////
//// class axTextControlMsg : public ax::event::Msg
////{
//// public:
////    axTextControlMsg()
////    {
////        _sender = nullptr;
////    }
////
////    axTextControlMsg(axTextControl* sender, const std::string& msg)
////    {
////        _sender = sender;
////        _msg = msg;
////    }
////
////    axTextControl* GetSender() const
////    {
////        return _sender;
////    }
////
////    std::string GetMsg() const
////    {
////        return _msg;
////    }
////
////    ax::event::Msg* GetCopy()
////    {
////        return new axTextControlMsg(*this);
////    }
////
//// private:
////    axTextControl* _sender;
////    std::string _msg;
////};
////
//// struct axTextControlEvents
////{
////    enum : ax::event::Id { BUTTON_CLICK };
////
////	axTextControlEvents(){}
////    axTextControlEvents(ax::event::Function& fct){ button_click = fct; }
////
////    ax::event::Function button_click;
////};
////
//// struct axTextControlInfo
////{
////	ax::Color normal;
////	ax::Color hover;
////    ax::Color hightlight; // This needs to be transparent.
////	ax::Color selected;
////    ax::Color selected_shadow;
////	ax::Color cursor;
////	ax::Color contour;
////	ax::Color font_color;
////
////	axTextControlInfo(){}
////	axTextControlInfo(const ax::Color& normal_color,
////                  const ax::Color& hover_color,
////                  const ax::Color& hightlight_color,
////                  const ax::Color& selected_color,
////                  const ax::Color& selected_shadow_color,
////                  const ax::Color& cursor_color,
////                  const ax::Color& contour_color,
////                  const ax::Color& font_color_) :
////    normal(normal_color),
////    hover(hover_color),
////    hightlight(hightlight_color),
////    selected(selected_color),
////    selected_shadow(selected_shadow_color),
////    cursor(cursor_color),
////    contour(contour_color),
////    font_color(font_color_)
////    {
////
////    }
////
////    axTextControlInfo(const std::string& path)
////    {
////        SerializeInput(path);
////    }
////
////    void SerializeOutput(const std::string& path)
////    {
////        std::fstream file;
////        file.open(path, std::fstream::out | std::fstream::binary);
////
////        if (file.fail())
////        {
////            std::cerr << "Problem opening file " << path << std::endl;
////        }
////        else
////        {
////            normal.SerializeOutput(file);
////            hover.SerializeOutput(file);
////            selected.SerializeOutput(file);
////            cursor.SerializeOutput(file);
////            contour.SerializeOutput(file);
////            font_color.SerializeOutput(file);
////        }
////
////    }
////
////    void SerializeInput(const std::string& path)
////    {
////        std::fstream file;
////        file.open(path, std::fstream::in | std::fstream::binary);
////
////        if (file.fail())
////        {
////            std::cerr << "Problem opening file " << path << std::endl;
////        }
////        else
////        {
////            normal.SerializeInput(file);
////            hover.SerializeInput(file);
////            selected.SerializeInput(file);
////            cursor.SerializeInput(file);
////            contour.SerializeInput(file);
////            font_color.SerializeInput(file);
////        }
////    }
////};
////
//// class axTextControl : public axPanel
////{
//// public:
////	axTextControl(ax::Window* parent,
////                  const ax::Rect& rect,
////                  const axTextControlEvents& events,
////                  const axTextControlInfo& info,
////                  std::string img_path = "",
////                  std::string label = "",
////                  ax::util::Flag flags = 0);
////
////    void SetLabel(const std::string& label);
////
////
////    axEVENT_ACCESSOR(ax::event::Timer::Msg, OnFlashingCursorTimer);
////
//// protected:
////    axTextControlEvents _events;
////    axTextControlInfo _info;
////    std::string _label;
////    ax::Image* _btnImg;
////    ax::util::Flag _flags;
////    ax::Font* _font;
////
////    ax::Color* _currentColor;
////    int _nCurrentImg;
////    int _cursorIndex;
////    bool _isHightlight;
////    bool _findClickCursorIndex;
////    ax::Point _clickPosition;
////
////    int _cursorBarXPosition, _lastCharXPosition;
////
////    enum axTextControlState
////    {
////        axBTN_NORMAL,
////        axBTN_HOVER,
////        axBTN_DOWN,
////        axBTN_SELECTED
////    };
////
////    ax::event::Timer* _flashingCursor;
////
////	virtual void OnPaint();
////	virtual void OnMouseLeftDown(const ax::Point& pos);
////    virtual void OnMouseLeftDragging(const ax::Point& pos);
////	virtual void OnMouseLeftUp(const ax::Point& pos);
////	virtual void OnMouseEnter();
////	virtual void OnMouseLeave();
////    virtual void OnMouseLeftDoubleClick(const ax::Point& pos);
////    virtual void OnKeyDown(const char& key);
////    virtual void OnBackSpaceDown();
////
////    virtual void OnLeftArrowDown();
////    virtual void OnRightArrowDown();
////    virtual void OnWasKeyUnGrabbed();
////    virtual void OnWasKeyGrabbed();
////    virtual void OnKeyDeleteDown();
////
////    //
////    virtual void DrawContourRectangle(ax::GC* gc);
////
////    void OnFlashingCursorTimer(const ax::event::Timer::Msg& msg);
////
////    bool _cursorFlashActive;
////};
//
///// @}
///// @}
//#endif // __AX_TEXT_CONTROL__
//
////>>>>>>> f96fac03fa26d3d50be57db1ab4b2dea10dbd93a
