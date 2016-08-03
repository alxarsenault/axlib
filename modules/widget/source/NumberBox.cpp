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
//#include "NumberBox.hpp"
//
///*
// * ax::NumberBox::Flags.
// */
//const ax::Flag ax::NumberBox::Flags::SINGLE_IMG = ax::FlagValue::FLAG_1;
//const ax::Flag ax::NumberBox::Flags::NO_IMG_RESIZE = ax::FlagValue::FLAG_2;
//const ax::Flag ax::NumberBox::Flags::LABEL = ax::FlagValue::FLAG_3;
//const ax::Flag ax::NumberBox::Flags::SLIDER = ax::FlagValue::FLAG_4;
//const ax::Flag ax::NumberBox::Flags::NO_MOUSE = ax::FlagValue::FLAG_5;
//
///*
// * ax::NumberBox::Msg.
// */
//ax::NumberBox::Msg::Msg(const double& value)
//	: _value(value)
//{
//}
//
//double ax::NumberBox::Msg::GetValue() const
//{
//	return _value;
//}
//
//ax::Event::Msg* ax::NumberBox::Msg::GetCopy()
//{
//	return new Msg(*this);
//}
//
///*
// * ax::NumberBox::Info.
// */
//ax::NumberBox::Info::Info(const ax::Color& normal_color, const ax::Color& hover_color,
//	const ax::Color& clicked_color, const ax::Color& selected_color, const ax::Color& contour_color,
//	const ax::Color& font_color_, const std::string& imgPath, const bool& singleImg)
//	: normal(normal_color)
//	, hover(hover_color)
//	, clicking(clicked_color)
//	, selected(selected_color)
//	, contour(contour_color)
//	, font_color(font_color_)
//	, img(imgPath)
//	, single_img(singleImg)
//{
//}
//
//ax::NumberBox::Info::Info(const std::string& path)
//	: ax::widget::Info(path)
//{
//}
//
//ax::NumberBox::Info::Info(const ax::StringPairVector& attributes)
//{
//	SetAttributes(attributes);
//}
//
//std::vector<std::string> ax::NumberBox::Info::GetParamNameList() const
//{
//	return std::vector<std::string>{ "normal", "hover", "clicking", "selected", "contour", "font_color", "img",
//		"single_img" };
//}
//
//std::string ax::NumberBox::Info::GetAttributeValue(const std::string& name)
//{
//	if (name == "normal") {
//		return normal.ToString();
//	}
//	else if (name == "hover") {
//		return hover.ToString();
//	}
//	else if (name == "clicking") {
//		return clicking.ToString();
//	}
//	else if (name == "selected") {
//		return selected.ToString();
//	}
//	else if (name == "contour") {
//		return contour.ToString();
//	}
//	else if (name == "font_color") {
//		return font_color.ToString();
//	}
//	else if (name == "img") {
//		return img;
//	}
//	else if (name == "single_img") {
//		return std::to_string(single_img);
//	}
//
//	return "";
//}
//
//void ax::NumberBox::Info::SetAttribute(const ax::StringPair& attribute)
//{
//	if (attribute.first == "normal") {
//		normal = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "hover") {
//		hover = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "clicking") {
//		clicking = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "selected") {
//		selected = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "contour") {
//		contour = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "font_color") {
//		font_color = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "img") {
//		img = attribute.second;
//	}
//	else if (attribute.first == "single_img") {
//		single_img = stoi(attribute.second) == 1 ? true : false;
//	}
//}
//
///*
// * axNumberBox::axNumberBox.
// */
//ax::NumberBox::NumberBox(const ax::Rect& rect, const ax::NumberBox::Events& events,
//	const ax::NumberBox::Info& info, ax::Flag flags, double value, ax::FloatRange range,
//	ax::Utils::Control::Type type, ax::Utils::Control::Unit unit,
//	ax::Utils::Control::Interpolation interpolation, std::string label)
//	: _events(events)
//	, _flags(flags)
//	, _font(nullptr)
//	, _type(type)
//	, _range(range)
//	//	, _interpolation(interpolation)
//	, _nCurrentImg(axNUM_BOX_NORMAL)
//
//{
//	win = ax::Window::Create(rect);
//
//	win->component.Add(
//		"Widget", widget::Component::Ptr(new widget::Component(win, new ax::NumberBox::Info(info))));
//
//	win->property.AddProperty("Editable");
//
//	_currentColor = info.normal;
//
//	// Builtin event connection.
//	win->event.OnPaint = ax::WBind<ax::GC>(this, &NumberBox::OnPaint);
//	win->event.OnMouseLeftDown = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftDown);
//	win->event.OnMouseLeftUp = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftUp);
//	win->event.OnMouseLeftDragging = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftDragging);
//	win->event.OnMouseEnter = ax::WBind<ax::Point>(this, &NumberBox::OnMouseEnter);
//	win->event.OnMouseLeave = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeave);
//
//	_bgImg = new ax::Image(info.img);
//
//	_value = ax::Utils::Clamp<double>(value, _range.left, _range.right);
//
//	_font = new ax::Font(0);
//	_font->SetFontSize(10);
//
//	_zeroToOneValue = _range.GetZeroToOneValue(_value);
//
//	if (_events.value_change) {
//		win->AddConnection(Events::VALUE_CHANGE, _events.value_change);
//	}
//}
//
//ax::NumberBox::NumberBox(const ax::Point& pos, const ax::NumberBox::Events& events,
//	const ax::NumberBox::Info& info, ax::Flag flags, double value, ax::FloatRange range,
//	ax::Utils::Control::Type type, ax::Utils::Control::Unit unit,
//	ax::Utils::Control::Interpolation interpolation, std::string label)
//	: _events(events)
//	, _flags(flags)
//	, _font(nullptr)
//	, _type(type)
//	, _range(range)
//	//	, _interpolation(interpolation)
//	, _nCurrentImg(axNUM_BOX_NORMAL)
//
//{
//	win = ax::Window::Create(ax::Rect(pos, ax::Size(50, 20)));
//
//	win->component.Add(
//		"Widget", widget::Component::Ptr(new widget::Component(win, new ax::NumberBox::Info(info))));
//
//	win->property.AddProperty("Editable");
//
//	_currentColor = info.normal;
//
//	// Builtin event connection.
//	win->event.OnPaint = ax::WBind<ax::GC>(this, &NumberBox::OnPaint);
//	win->event.OnMouseLeftDown = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftDown);
//	win->event.OnMouseLeftUp = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftUp);
//	win->event.OnMouseLeftDragging = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftDragging);
//	win->event.OnMouseEnter = ax::WBind<ax::Point>(this, &NumberBox::OnMouseEnter);
//	win->event.OnMouseLeave = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeave);
//
//	_bgImg = new ax::Image(info.img);
//
//	_value = ax::Utils::Clamp<double>(value, _range.left, _range.right);
//
//	_font = new ax::Font(0);
//	_font->SetFontSize(10);
//
//	_zeroToOneValue = _range.GetZeroToOneValue(_value);
//
//	if (_events.value_change) {
//		win->AddConnection(Events::VALUE_CHANGE, _events.value_change);
//	}
//}
//
//ax::Window::Backbone* ax::NumberBox::GetCopy()
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::NumberBox::Info* info = static_cast<ax::NumberBox::Info*>(widget->GetInfo());
//	ax::NumberBox* nbox = new ax::NumberBox(win->dimension.GetRect(), _events, *info, _flags, _value, _range,
//		_type, ax::Utils::Control::Unit::axCTRL_NO_UNIT, ax::Utils::Control::Interpolation::axCTRL_LINEAR,
//		_label);
//	return nbox;
//}
//
//double ax::NumberBox::GetValue()
//{
//	return _value;
//}
//
//void ax::NumberBox::OnMouseEnter(const ax::Point& pos)
//{
//	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
//	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());
//
//	_currentColor = info.hover;
//	_nCurrentImg = axNUM_BOX_HOVER;
//	win->Update();
//}
//
//void ax::NumberBox::OnMouseLeave(const ax::Point& pos)
//{
//	if (win->event.IsGrabbed()) {
//		return;
//	}
//
//	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
//	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());
//	_currentColor = info.normal;
//	_nCurrentImg = axNUM_BOX_NORMAL;
//	win->Update();
//}
//
//void ax::NumberBox::OnMouseLeftDown(const ax::Point& pos)
//{
//	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
//	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());
//
//	_clickPosY = (pos - win->dimension.GetAbsoluteRect().position).y;
//	_nCurrentImg = axNUM_BOX_DOWN;
//	_currentColor = info.clicking;
//
//	win->event.GrabMouse();
//	win->Update();
//}
//
//void ax::NumberBox::OnMouseLeftUp(const ax::Point& pos)
//{
//	if (!win->event.IsGrabbed()) {
//		return;
//	}
//
//	win->event.UnGrabMouse();
//	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
//	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());
//
//	if (win->event.IsMouseHoverWindow()) {
//		_currentColor = info.hover;
//		_nCurrentImg = axNUM_BOX_HOVER;
//	}
//	else {
//		_currentColor = info.normal;
//		_nCurrentImg = axNUM_BOX_NORMAL;
//	}
//
//	win->PushEvent(Events::VALUE_CHANGE, new Msg(_value));
//	win->Update();
//}
//
//void ax::NumberBox::OnMouseLeftDragging(const ax::Point& pos)
//{
//	ax::Point pt(win->dimension.GetAbsoluteRect().position);
//	ax::Point p = pos - pt;
//
//	double delta = p.y - _clickPosY;
//
//	_clickPosY = p.y;
//
//	double v = -delta / 100.0;
//	_zeroToOneValue += v;
//
//	_zeroToOneValue = ax::Utils::Clamp<double>(_zeroToOneValue, 0.0, 1.0);
//	_value = _range.GetValueFromZeroToOne(_zeroToOneValue);
//
//	win->PushEvent(Events::VALUE_CHANGE, new Msg(_value));
//
//	win->Update();
//}
//
//void ax::NumberBox::OnPaint(ax::GC gcs)
//{
//	ax::GC* gc = &gcs;
//	ax::Rect rect0(win->dimension.GetDrawingRect());
//	ax::Rect rect(win->dimension.GetRect());
//
//	gc->SetColor(_currentColor);
//	gc->DrawRectangle(rect0);
//
//	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
//	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());
//
//	if (_bgImg->IsImageReady()) {
//		if (info.single_img) {
//			if (ax::IsFlag(Flags::NO_IMG_RESIZE, _flags)) {
//				gc->DrawImage(_bgImg, ax::Point(0, 0));
//			}
//			else {
//				gc->DrawImageResize(_bgImg, ax::Point(0, 0), rect0.size);
//			}
//		}
//		else {
//			gc->DrawPartOfImage(_bgImg, ax::Point(0, _nCurrentImg * rect.size.y), rect.size, ax::Point(0, 0));
//		}
//	}
//
//	gc->SetColor(info.font_color);
//
//	if (_type == ax::Utils::Control::Type::REAL) {
//		std::string v = std::to_string(_value);
//		if (_value < 0) {
//			v.resize(5);
//		}
//		else {
//			v.resize(4);
//		}
//
//		gc->DrawStringAlignedCenter(*_font, v, rect0);
//	}
//	else if (_type == ax::Utils::Control::Type::INTEGER) {
//		std::string v = std::to_string((int)_value);
//		gc->DrawStringAlignedCenter(*_font, v, rect0);
//	}
//
//	gc->SetColor(info.contour);
//	gc->DrawRectangleContour(rect0);
//}
