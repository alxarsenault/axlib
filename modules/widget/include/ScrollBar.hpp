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
//#ifndef __AX_SCROLL_BAR_H__
//#define __AX_SCROLL_BAR_H__
//
///// @defgroup Widgets
///// @{
//
///// @defgroup ScrollBar
///// @{
//
//#include "axlib.hpp"
//
//namespace ax {
//class ScrollBar : public ax::Window::Backbone {
//public:
//	typedef std::shared_ptr<ScrollBar> Ptr;
//
//	typedef ax::Event::StringMsg Msg;
//
//	class Events {
//	public:
//		enum : ax::Event::Id { VALUE_CHANGE };
//
//		Events()
//		{
//		}
//
//		Events(const ax::Event::Function& fct)
//		{
//			value_change = fct;
//		}
//
//		ax::Event::Function value_change;
//	};
//
//	class Info : public ax::widget::Info {
//	public:
//		Info();
//
//		ax::Color normal;
//		ax::Color hover;
//		ax::Color clicking;
//		ax::Color slider_contour;
//		ax::Color contour;
//		ax::Color bg_top;
//		ax::Color bg_bottom;
//	};
//
//	ScrollBar(const ax::Rect& rect, const ScrollBar::Events& events, const ScrollBar::Info& info);
//
//	void SetWindowHandle(ax::Window* win);
//
//	void UpdateWindowSize(const ax::Size& size);
//
//	double GetZeroToOneValue() const;
//	void SetZeroToOneValue(const double& value);
//
//private:
//	ax::ScrollBar::Events _events;
//	ax::ScrollBar::Info _info;
//	ax::Window* _handle;
//
//	int _sliderHeight, _sliderMaxHeight, _sliderPos, _yClickDelta;
//	ax::Size _panelSize;
//
//	ax::Color _currentScrollBarColor;
//
//	double _value;
//
//	void OnPaint(ax::GC gc);
//	void OnResize(const ax::Size& size);
//	void OnMouseLeftDragging(const ax::Point& pos);
//	void OnMouseLeftDown(const ax::Point& pos);
//	void OnMouseLeftUp(const ax::Point& pos);
//	void OnMouseMotion(const ax::Point& pos);
//	void OnMouseEnter(const ax::Point& pos);
//	void OnMouseLeave(const ax::Point& pos);
//};
//}
//
///// @}
///// @}
//#endif // __AX_SCROLL_BAR_H__
