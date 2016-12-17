/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of OpenAX.
 *
 * OpenAX is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * license or use a commercial OpenAX License.
 *
 * OpenAX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenAX. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses OpenAX, commercial
 * licenses are available, email ax.frameworks@gmail.com for more information.
 */

#include "ScrollBar.hpp"

namespace ax {
/*
 * ax::ScrollBar::Info.
 */
ScrollBar::Info::Info()
{
}

/*
 * ax::ScrollBar.
 */
ScrollBar::ScrollBar(const ax::Rect& rect, const ScrollBar::Events& events, const ScrollBar::Info& info)
	: _events(events)
	, _info(info)
	, _handle(nullptr)
{
	win = ax::Window::Create(rect);
	win->event.OnPaint = ax::WBind<ax::GC>(this, &ScrollBar::OnPaint);
	win->event.OnMouseLeftDown = ax::WBind<ax::Point>(this, &ScrollBar::OnMouseLeftDown);
	win->event.OnMouseLeftUp = ax::WBind<ax::Point>(this, &ScrollBar::OnMouseLeftUp);
	win->event.OnMouseEnter = ax::WBind<ax::Point>(this, &ScrollBar::OnMouseEnter);
	win->event.OnMouseLeave = ax::WBind<ax::Point>(this, &ScrollBar::OnMouseLeave);
	win->event.OnMouseLeftDragging = ax::WBind<ax::Point>(this, &ScrollBar::OnMouseLeftDragging);
	win->event.OnMouseMotion = ax::WBind<ax::Point>(this, &ScrollBar::OnMouseMotion);

	_panelSize = rect.size;
	_sliderMaxHeight = rect.size.h;

	double ratio = double(_panelSize.h - rect.size.h) / double(_panelSize.h);

	_sliderHeight = _sliderMaxHeight * (1.0 - ratio);
	_sliderPos = 0;

	_currentScrollBarColor = _info.normal;

	if (_events.value_change) {
		win->AddConnection(ax::ScrollBar::Events::VALUE_CHANGE, _events.value_change);
	}
}

void ScrollBar::SetWindowHandle(ax::Window* win)
{
	_handle = win;
	UpdateWindowSize(win->dimension.GetShownRect().size);
}

void ScrollBar::UpdateWindowSize(const ax::Size& size)
{
	_panelSize = size;
	ax::Size win_size(win->dimension.GetSize());
	_sliderMaxHeight = win_size.h;

	if (_panelSize.h <= win_size.h) {
		_sliderPos = 0;
		_value = 0.0;
		_sliderHeight = _sliderMaxHeight;
		win->Update();
		return;
	}

	double ratio = double(_panelSize.h - win_size.h) / double(_panelSize.h);
	_sliderHeight = _sliderMaxHeight * (1.0 - ratio);

	SetZeroToOneValue(_value);

	win->Update();
}

double ScrollBar::GetZeroToOneValue() const
{
	double d = win->dimension.GetRect().size.h - _sliderHeight - 1.0;
	
	if(d <= 0.0) {
		return 0.0;
	}
	
	return _sliderPos / d;
}

void ScrollBar::SetZeroToOneValue(const double& value)
{
	double v = ax::util::Clamp<double>(value, 0.0, 1.0);
	_sliderPos = v * double(win->dimension.GetRect().size.h - _sliderHeight - 1);

	// Slider position ratio.
	_value = (_sliderPos) / double(_sliderMaxHeight - _sliderHeight - 1);
	_value = ax::util::Clamp<double>(_value, 0.0, 1.0);

	win->PushEvent(ax::ScrollBar::Events::VALUE_CHANGE, new ax::ScrollBar::Msg(""));

	if (_handle != nullptr) {
		const ax::Rect& rect(win->dimension.GetRect());
		_handle->dimension.SetScrollDecay(ax::Point(0, _value * (_panelSize.h - rect.size.h)));
	}

	win->Update();
}

void ScrollBar::OnMouseMotion(const ax::Point& position)
{
	const ax::Rect& rect(win->dimension.GetRect());
	ax::Point pos = position - win->dimension.GetAbsoluteRect().position;

	if (ax::Rect(0, _sliderPos, rect.size.w, _sliderHeight).IsPointInside(pos)) {
		_currentScrollBarColor = _info.hover;
		win->Update();
	}
	else if (_currentScrollBarColor != _info.normal) {
		_currentScrollBarColor = _info.normal;
		win->Update();
	}
}

void ScrollBar::OnMouseLeftDown(const ax::Point& position)
{
	const ax::Rect& rect(win->dimension.GetRect());
	ax::Point pos = position - win->dimension.GetAbsoluteRect().position;

	if (ax::Rect(0, _sliderPos, rect.size.w, _sliderHeight).IsPointInside(pos)) {
		_currentScrollBarColor = _info.hover;
		_yClickDelta = pos.y - _sliderPos;

		win->event.GrabMouse();
		win->Update();
	}
}

void ScrollBar::OnMouseLeftUp(const ax::Point& pos)
{
	if (win->event.IsGrabbed()) {
		win->event.UnGrabMouse();
	}
}

void ScrollBar::OnMouseLeftDragging(const ax::Point& position)
{
	const ax::Rect& rect(win->dimension.GetRect());
	ax::Point pos = position - win->dimension.GetAbsoluteRect().position;

	if (_sliderHeight < _sliderMaxHeight) {
		// m_sliderPosition move with mouse position.
		_sliderPos = pos.y - _yClickDelta;

		// If m_sliderPosition reach bottom, clip m_sliderPosition.
		if (_sliderPos + _sliderHeight > rect.size.h - 1) {
			_sliderPos = rect.size.h - 1 - _sliderHeight;
		}

		// Clip top.
		if (_sliderPos < 0) {
			_sliderPos = 0;
		}

		// Slider position ratio.
		_value = (_sliderPos) / double(_sliderMaxHeight - _sliderHeight - 1);
		_value = ax::util::Clamp<double>(_value, 0.0, 1.0);

		win->PushEvent(ax::ScrollBar::Events::VALUE_CHANGE, new ax::ScrollBar::Msg(""));

		if (_handle != nullptr) {
			_handle->dimension.SetScrollDecay(ax::Point(0, _value * (_panelSize.h - rect.size.h)));
		}

		win->Update();
	}
}

void ScrollBar::OnMouseEnter(const Point& pos)
{
}

void ScrollBar::OnMouseLeave(const Point& pos)
{
	if (_currentScrollBarColor != _info.normal) {
		_currentScrollBarColor = _info.normal;
		win->Update();
	}
}

void ScrollBar::OnResize(const Size& size)
{
}

void ScrollBar::OnPaint(GC gc)
{
	const Rect& rect(win->dimension.GetDrawingRect());

	gc.DrawRectangleColorFade(rect, _info.bg_top, _info.bg_bottom);

	gc.SetColor(_currentScrollBarColor);
	Rect bar_rect(rect.position.x + 1, _sliderPos, rect.size.w - 2, _sliderHeight);
	gc.DrawRectangle(bar_rect);

	gc.SetColor(_info.slider_contour);
	gc.DrawRectangleContour(bar_rect);

	gc.SetColor(_info.contour);
	gc.DrawRectangleContour(rect);
}
}
