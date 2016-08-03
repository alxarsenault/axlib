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
//#include "axTextControl.h"
//
// axTextControl::axTextControl(ax::Window* parent,
//                             const ax::Rect& rect,
//                             const axTextControlEvents& events,
//                             const axTextControlInfo& info,
//                             std::string img_path,
//                             std::string label,
//                             ax::Flag flags) :
//// Heritage.
// axPanel(parent, rect),
//// Members.
//_events(events),
//_info(info),
//_label(label),
//_flags(flags),
//_nCurrentImg(axBTN_NORMAL),
//_cursorBarXPosition(5),
//_lastCharXPosition(5),
//_flashingCursor(nullptr),
//_cursorFlashActive(true),
//_isHightlight(false),
//_findClickCursorIndex(false)
//{
//	_currentColor = &_info.normal;
//
//    _btnImg = new ax::Image(img_path);
//
//    if(_events.button_click)
//    {
//        AddConnection(axTextControlEvents::BUTTON_CLICK, _events.button_click);
//    }
//
//    if(ax::IsFlag(axTEXT_CTRL_FLASHING_CURSOR, _flags))
//    {
//        _flashingCursor = new ax::Event::Timer(ax::App::GetMainApp()->GetEventManager());
//        _flashingCursor->AddConnection(0, GetOnFlashingCursorTimer());
//    }
//
//    _cursorIndex = (int)_label.size();
//
//    _font = new ax::Font(0);
//
//    SetShownRect(ax::Rect(-5,
//                        -5,
//                        rect.size.x + 10,
//                        rect.size.y + 10));
//}
//
// void axTextControl::SetLabel(const std::string& label)
//{
//    _label = label;
//    Update();
//}
//
// void axTextControl::OnMouseLeftDown(const ax::Point& pos)
//{
//    _findClickCursorIndex = true;
//    _clickPosition = pos - GetAbsoluteRect().position;
//
//    if(_isHightlight)
//    {
//        _isHightlight = false;
//    }
//
//    GrabMouse();
//    GrabKey();
//    Update();
//}
//
// void axTextControl::OnFlashingCursorTimer(const ax::Event::Timer::Msg& msg)
//{
//    _cursorFlashActive = !_cursorFlashActive;
//    Update();
//}
//
// void axTextControl::OnMouseLeftUp(const ax::Point& pos)
//{
//    if(IsGrabbed())
//    {
//        UnGrabMouse();
//    }
//}
//
// void axTextControl::OnMouseEnter()
//{
//
//}
//
// void axTextControl::OnMouseLeave()
//{
//
//}
//
// void axTextControl::OnMouseLeftDragging(const ax::Point& pos)
//{
//    _clickPosition = pos - GetAbsoluteRect().position;
//    Update();
//
//}
//
// void axTextControl::OnMouseLeftDoubleClick(const ax::Point& pos)
//{
//    _isHightlight = true;
//    Update();
//}
//
// void axTextControl::OnWasKeyUnGrabbed()
//{
//    if(ax::IsFlag(axTEXT_CTRL_FLASHING_CURSOR, _flags))
//    {
//        _flashingCursor->StopTimer();
//    }
//
//    _currentColor = &_info.normal;
//
//    Update();
//}
//
// void axTextControl::OnWasKeyGrabbed()
//{
//    _currentColor = &_info.selected;
//
//    if(ax::IsFlag(axTEXT_CTRL_FLASHING_CURSOR, _flags))
//    {
//        _flashingCursor->StartTimer(ax::Event::Timer::TimeMs(500));
//    }
//
//    Update();
//}
//
// void axTextControl::OnKeyDown(const char& key)
//{
//    if(_isHightlight)
//    {
//        _label.resize(0);
//        _label.insert(0, &key);
//        _cursorIndex = 1;
//        _isHightlight = false;
//        Update();
//    }
//    else
//    {
//        if(_lastCharXPosition < GetRect().size.x - 10)
//        {
//            _label.insert(_cursorIndex, &key);
//            ++_cursorIndex;
//            Update();
//        }
//    }
//}
//
// void axTextControl::OnBackSpaceDown()
//{
//    if(_isHightlight)
//    {
//        _label.resize(0);
//        _cursorIndex = 0;
//        _isHightlight = false;
//        Update();
//    }
//    else if(_label.size() && _cursorIndex)
//    {
//        _label.erase(_cursorIndex-1, 1);
//        --_cursorIndex;
//
//        if(_cursorIndex < 0)
//        {
//            _cursorIndex = 0;
//        }
//        Update();
//    }
//
//}
//
// void axTextControl::OnKeyDeleteDown()
//{
//    if(_isHightlight)
//    {
//        _label.resize(0);
//        _cursorIndex = 0;
//        _isHightlight = false;
//        Update();
//    }
//    else if(_label.size() && _cursorIndex < _label.size())
//    {
//        _label.erase(_cursorIndex, 1);
//        --_cursorIndex;
//
//        if(_cursorIndex < 0)
//        {
//            _cursorIndex = 0;
//        }
//        Update();
//    }
//}
//
// void axTextControl::OnLeftArrowDown()
//{
//    --_cursorIndex;
//
//    if(_cursorIndex < 0)
//    {
//        _cursorIndex = 0;
//    }
//
//    if(_isHightlight)
//    {
//        _isHightlight = false;
//    }
//
//
//    Update();
//}
//
// void axTextControl::OnRightArrowDown()
//{
//    ++_cursorIndex;
//
//    if(_cursorIndex > _label.size())
//    {
//        _cursorIndex = (int)_label.size();
//    }
//
//    if(_isHightlight)
//    {
//        _isHightlight = false;
//    }
//
//
//    Update();
//}
//
// void axTextControl::DrawContourRectangle(ax::GC* gc)
//{
//    ax::Rect rect(GetRect());
//
//    if(ax::IsFlag(axTEXT_CTRL_CONTOUR_HIGHLIGHT, _flags))
//    {
//        if(IsKeyGrab())
//        {
//            if(ax::IsFlag(axTEXT_CTRL_CONOUR_NO_FADE, _flags)) // Shadow fade.
//            {
//                gc->SetColor(_info.selected_shadow);
//                gc->DrawRectangle(ax::Rect(ax::Point(-5, -5),
//                                         ax::Size(rect.size + ax::Size(9, 9))));
//            }
//            else
//            {
//                ax::Color col(_info.selected_shadow);
//                gc->SetColor(col);
//
//                int nRect = 5;
//                for(int i = 0; i < nRect; i++)
//                {
//                    gc->DrawRectangleContour(ax::Rect(ax::Point(-i, -i),
//                                                    ax::Size(rect.size + ax::Size(2*i, 2*i))));
//
//                    double alpha = _info.selected_shadow.GetAlpha();
//                    double mu = double(i) / double(nRect);
//
//                    col.SetAlpha(alpha - alpha * mu);
//                    gc->SetColor(col);
//                }
//            }
//        }
//    }
//}
//
// void axTextControl::OnPaint()
//{
//    ax::GC gcs = ax::GC();
//    ax::GC* gc = &gcs;
//	ax::Rect rect(GetRect());
//	ax::Rect rect0(ax::Point(0, 0), rect.size);
//
//    DrawContourRectangle(gc);
//
//	gc->SetColor(*_currentColor);
//	gc->DrawRectangle(rect0);
//
//    ax::Point next_pos(5, 5);
//
//    if_not_empty(_label)
//    {
//        _cursorBarXPosition = 5;
//
//        for(int i = 0; i < _label.size(); i++)
//        {
//            int x_past_pos = next_pos.x;
//
//            gc->SetColor(_info.font_color);
//            next_pos = gc->DrawChar(*_font, _label[i], next_pos);
//
//            if(_isHightlight) // hightlight on.
//            {
//                gc->SetColor(_info.hightlight);
//                gc->DrawRectangle(ax::Rect(x_past_pos, 5,
//                                         next_pos.x - x_past_pos, rect0.size.y - 10));
//            }
//
//            if(_findClickCursorIndex)
//            {
//                if(_clickPosition.x >= x_past_pos &&
//                   _clickPosition.x < next_pos.x)
//                {
//                    _cursorIndex = i;
//                    _cursorBarXPosition = x_past_pos;
//                }
//                else if(i == _label.size() - 1 && _clickPosition.x > next_pos.x)
//                {
//                    _cursorIndex = i + 1;
//                    _cursorBarXPosition = next_pos.x;
//                }
//            }
//            else if(_cursorIndex - 1 == i)
//            {
//                _cursorBarXPosition = next_pos.x;
//            }
//        }
//
//        if(_findClickCursorIndex)
//        {
//            _findClickCursorIndex = false;
//        }
//
//        _lastCharXPosition = next_pos.x;
//    }
//    else
//    {
//        _cursorBarXPosition = 5;
//    }
//
//    if(IsKeyGrab() && _cursorFlashActive)
//    {
//        gc->SetColor(_info.cursor);
//
//        gc->DrawLine(ax::Point(_cursorBarXPosition, 5),
//                     ax::Point(_cursorBarXPosition, rect0.size.y - 5));
//    }
//
//	gc->SetColor(_info.contour);
//	gc->DrawRectangleContour(ax::Rect(ax::Point(0, 0), rect.size));
//}
//>>>>>>> f96fac03fa26d3d50be57db1ab4b2dea10dbd93a
