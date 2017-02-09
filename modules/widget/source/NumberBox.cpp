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

#include "NumberBox.hpp"

/*
 * ax::NumberBox::Flags.
 */
const ax::util::Flag ax::NumberBox::Flags::SINGLE_IMG = ax::util::FlagValue::FLAG_1;
const ax::util::Flag ax::NumberBox::Flags::NO_IMG_RESIZE = ax::util::FlagValue::FLAG_2;
const ax::util::Flag ax::NumberBox::Flags::LABEL = ax::util::FlagValue::FLAG_3;
const ax::util::Flag ax::NumberBox::Flags::SLIDER = ax::util::FlagValue::FLAG_4;
const ax::util::Flag ax::NumberBox::Flags::NO_MOUSE = ax::util::FlagValue::FLAG_5;

/*
 * ax::NumberBox::Msg.
 */
ax::NumberBox::Msg::Msg(const double& value)
	: _value(value)
{
}

double ax::NumberBox::Msg::GetValue() const
{
	return _value;
}

ax::event::Msg* ax::NumberBox::Msg::GetCopy()
{
	return new Msg(*this);
}

/*
 * ax::NumberBox::Info.
 */
ax::NumberBox::Info::Info(const ax::Color& normal_color, const ax::Color& hover_color,
	const ax::Color& clicked_color, const ax::Color& selected_color, const ax::Color& contour_color,
	const ax::Color& font_color_, const std::string& imgPath, const bool& singleImg)
	: normal(normal_color)
	, hover(hover_color)
	, clicking(clicked_color)
	, selected(selected_color)
	, contour(contour_color)
	, font_color(font_color_)
	, img(imgPath)
	, single_img(singleImg)
{
}

ax::NumberBox::Info::Info(const std::string& path)
	: ax::widget::Info(path)
{
}

ax::NumberBox::Info::Info(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	SetAttributes(attributes);
}

std::vector<std::string> ax::NumberBox::Info::GetParamNameList() const
{
	return std::vector<std::string>{ "normal", "hover", "clicking", "selected", "contour", "font_color",
		"img", "single_img" };
}

std::string ax::NumberBox::Info::GetAttributeValue(const std::string& name)
{
	if (name == "normal") {
		return normal.ToString();
	}
	else if (name == "hover") {
		return hover.ToString();
	}
	else if (name == "clicking") {
		return clicking.ToString();
	}
	else if (name == "selected") {
		return selected.ToString();
	}
	else if (name == "contour") {
		return contour.ToString();
	}
	else if (name == "font_color") {
		return font_color.ToString();
	}
	else if (name == "img") {
		return img;
	}
	else if (name == "single_img") {
		return std::to_string(single_img);
	}

	return "";
}

void ax::NumberBox::Info::SetAttribute(const std::pair<std::string, std::string>& attribute)
{
	if (attribute.first == "normal") {
		normal = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "hover") {
		hover = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "clicking") {
		clicking = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "selected") {
		selected = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "contour") {
		contour = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "font_color") {
		font_color = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "img") {
		img = attribute.second;
	}
	else if (attribute.first == "single_img") {
		single_img = stoi(attribute.second) == 1 ? true : false;
	}
}

ax::NumberBox::Component::Component(ax::Window* win, Info* info)
	: widget::Component(win, info)
{
}

void ax::NumberBox::Component::SaveFromWidgetNode(ax::Xml& xml, ax::Xml::Node& widget_node)
{
	ax::Window* win = GetWindow();
	ax::NumberBox* number_box(win->GetBackbone<ax::NumberBox>());
	ax::NumberBox::Component* widget_comp
		= static_cast<ax::NumberBox::Component*>(win->component.Get("Widget").get());
	ax::NumberBox::Info* info = static_cast<ax::NumberBox::Info*>(widget_comp->GetInfo());

	widget_node.AddAttribute("builder", "NumberBox");

	ax::Rect rect = win->dimension.GetRect();

	widget_node.AddNode(xml.CreateNode("position", std::to_string(rect.position)));
	widget_node.AddNode(xml.CreateNode("size", std::to_string(rect.size)));

	ax::Xml::Node info_node = xml.CreateNode("info");
	widget_node.AddNode(info_node);
	info_node.AddAttribute("normal", info->normal.ToString());
	info_node.AddAttribute("hover", info->hover.ToString());
	info_node.AddAttribute("clicking", info->clicking.ToString());
	info_node.AddAttribute("selected", info->selected.ToString());
	info_node.AddAttribute("contour", info->contour.ToString());
	info_node.AddAttribute("font_color", info->font_color.ToString());

	info_node.AddAttribute("img", info->img);
	info_node.AddAttribute("single_img", std::to_string(info->single_img));

	widget_node.AddNode(xml.CreateNode("flags", std::to_string(number_box->GetFlags())));
	widget_node.AddNode(xml.CreateNode("range", number_box->GetRange().ToString()));
	widget_node.AddNode(xml.CreateNode("type", std::to_string(int(number_box->GetControlType()))));
}

std::vector<std::pair<std::string, std::string>> ax::NumberBox::Component::GetBuilderAttributes()
{
	ax::Window* win = GetWindow();
	ax::NumberBox* number_box(win->GetBackbone<ax::NumberBox>());

	std::vector<std::pair<std::string, std::string>> atts;
	atts.push_back(
		std::pair<std::string, std::string>("position", win->dimension.GetRect().position.ToString()));
	atts.push_back(std::pair<std::string, std::string>("size", win->dimension.GetSize().ToString()));
	atts.push_back(std::pair<std::string, std::string>("flags", std::to_string(number_box->GetFlags())));
	atts.push_back(std::pair<std::string, std::string>("range", number_box->GetRange().ToString()));
	atts.push_back(
		std::pair<std::string, std::string>("type", std::to_string(int(number_box->GetControlType()))));
	return atts;
}

std::vector<ax::widget::ParamInfo> ax::NumberBox::Component::GetBuilderAttributesInfo() const
{
	return { ax::widget::ParamInfo(ax::widget::ParamType::POINT, "position"),
		ax::widget::ParamInfo(ax::widget::ParamType::SIZE, "size"),
		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "flags"),
		ax::widget::ParamInfo(ax::widget::ParamType::RANGE, "range"),
		ax::widget::ParamInfo(ax::widget::ParamType::INTEGER, "type") };
}

void ax::NumberBox::Component::SetBuilderAttributes(
	const std::vector<std::pair<std::string, std::string>>& attributes)
{
	ax::NumberBox* number_box = static_cast<ax::NumberBox*>(GetWindow()->backbone.get());

	for (auto& n : attributes) {
		if (n.first == "position") {
			ax::Point pos = ax::Point(n.second);
			GetWindow()->dimension.SetPosition(pos);
		}
		else if (n.first == "size") {
			ax::Size size = ax::Size(n.second);
			GetWindow()->dimension.SetSize(size);
		}
		else if (n.first == "range") {
			number_box->SetRange(ax::util::Range2D<double>(n.second));
		}
		else if (n.first == "type") {
			number_box->SetControlType(
				ax::util::Control::Type(static_cast<ax::util::Control::Type>(std::stoi(n.second))));
		}
	}
}

void ax::NumberBox::Component::SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	_info->SetAttributes(attributes);
}

void ax::NumberBox::Component::ReloadInfo()
{
	ax::NumberBox* nbox_obj = static_cast<ax::NumberBox*>(_win->backbone.get());
	ax::NumberBox::Info* info = static_cast<ax::NumberBox::Info*>(_info);

	if (nbox_obj->_bgImg->GetImagePath() != info->img) {
		/// @todo Leak --> use shared_ptr.
		nbox_obj->_bgImg = new Image(info->img);
	}

	nbox_obj->_currentColor = info->normal;

	_win->Update();
}

ax::NumberBox::Builder::Builder()
{
}

std::shared_ptr<ax::Window::Backbone> ax::NumberBox::Builder::Create(
	const Point& pos, const std::string& file_path)
{
	ax::Xml xml(file_path);

	if (!xml.Parse()) {
		ax::console::Error("Parsing error.");
		return nullptr;
	}

	ax::Xml::Node control = xml.GetNode("Widget");
	std::string builder_name = control.GetAttribute("builder");
	std::string obj_name = control.GetAttribute("name");

	const ax::Size size(control.GetChildNodeValue("size"));
	const ax::util::Flag flags = std::stoi(control.GetChildNodeValue("flags"));
	const ax::util::Range2D<double> range(control.GetChildNodeValue("range"));
	const ax::util::Control::Type type(
		static_cast<ax::util::Control::Type>(std::stoi(control.GetChildNodeValue("type"))));

	ax::Xml::Node info_node = control.GetNode("info");
	ax::NumberBox::Info k_info;
	k_info.normal = ax::Color::FromString(info_node.GetAttribute("normal"));
	k_info.hover = ax::Color::FromString(info_node.GetAttribute("hover"));
	k_info.clicking = ax::Color::FromString(info_node.GetAttribute("clicking"));
	k_info.selected = ax::Color::FromString(info_node.GetAttribute("selected"));
	k_info.contour = ax::Color::FromString(info_node.GetAttribute("contour"));
	k_info.font_color = ax::Color::FromString(info_node.GetAttribute("font_color"));

	k_info.img = info_node.GetAttribute("img");
	k_info.single_img = (bool)std::stoi(info_node.GetAttribute("single_img"));

	return ax::shared<ax::NumberBox>(
		ax::Rect(pos, size), ax::NumberBox::Events(), k_info, flags, 0.0, range, type);
}

std::shared_ptr<ax::Window::Backbone> ax::NumberBox::Builder::Create(Xml::Node& node)
{
	ax::Xml::Node control(node);
	std::string builder_name = control.GetAttribute("builder");

	const ax::Point pos(control.GetChildNodeValue("position"));
	const ax::Size size(control.GetChildNodeValue("size"));

	const ax::util::Flag flags = std::stoi(control.GetChildNodeValue("flags"));
	const ax::util::Range2D<double> range(control.GetChildNodeValue("range"));
	const ax::util::Control::Type type(
		static_cast<ax::util::Control::Type>(std::stoi(control.GetChildNodeValue("type"))));

	ax::Xml::Node info_node = control.GetNode("info");

	ax::NumberBox::Info k_info;
	k_info.normal = ax::Color::FromString(info_node.GetAttribute("normal"));
	k_info.hover = ax::Color::FromString(info_node.GetAttribute("hover"));
	k_info.clicking = ax::Color::FromString(info_node.GetAttribute("clicking"));
	k_info.selected = ax::Color::FromString(info_node.GetAttribute("selected"));
	k_info.contour = ax::Color::FromString(info_node.GetAttribute("contour"));
	k_info.font_color = ax::Color::FromString(info_node.GetAttribute("font_color"));

	k_info.img = info_node.GetAttribute("img");
	k_info.single_img = (bool)std::stoi(info_node.GetAttribute("single_img"));

	return ax::shared<ax::NumberBox>(
		ax::Rect(pos, size), ax::NumberBox::Events(), k_info, flags, 0.0, range, type);
}

/*
 * axNumberBox::axNumberBox.
 */
ax::NumberBox::NumberBox(const ax::Rect& rect, const ax::NumberBox::Events& events,
	const ax::NumberBox::Info& info, ax::util::Flag flags, double value, ax::util::Range2D<double> range,
	ax::util::Control::Type type, ax::util::Control::Unit unit,
	ax::util::Control::Interpolation interpolation, std::string label)
	: _events(events)
	, _flags(flags)
	, _font(nullptr)
	, _type(type)
	, _range(range)
	//	, _interpolation(interpolation)
	, _nCurrentImg(axNUM_BOX_NORMAL)

{
	win = ax::Window::Create(rect);

	win->component.Add(
		"Widget", widget::Component::Ptr(new ax::NumberBox::Component(win, new ax::NumberBox::Info(info))));

	win->property.AddProperty("Editable");

	_currentColor = info.normal;

	// Builtin event connection.
	win->event.OnPaint = ax::WBind<ax::GC>(this, &NumberBox::OnPaint);
	win->event.OnMouseLeftDown = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftDown);
	win->event.OnMouseLeftUp = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftUp);
	win->event.OnMouseLeftDragging = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftDragging);
	win->event.OnMouseEnter = ax::WBind<ax::Point>(this, &NumberBox::OnMouseEnter);
	win->event.OnMouseLeave = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeave);

	_bgImg = new ax::Image(info.img);

	_value = ax::util::Clamp<double>(value, _range.left, _range.right);

	_font = new ax::Font(0);
	_font->SetFontSize(10);

	_zeroToOneValue = _range.GetZeroToOneValue(_value);

	if (_events.value_change) {
		win->AddConnection(Events::VALUE_CHANGE, _events.value_change);
	}
}

ax::NumberBox::NumberBox(const ax::Point& pos, const ax::NumberBox::Events& events,
	const ax::NumberBox::Info& info, ax::util::Flag flags, double value, ax::util::Range2D<double> range,
	ax::util::Control::Type type, ax::util::Control::Unit unit,
	ax::util::Control::Interpolation interpolation, std::string label)
	: _events(events)
	, _flags(flags)
	, _font(nullptr)
	, _type(type)
	, _range(range)
	//	, _interpolation(interpolation)
	, _nCurrentImg(axNUM_BOX_NORMAL)

{
	win = ax::Window::Create(ax::Rect(pos, ax::Size(50, 20)));

	win->component.Add(
		"Widget", widget::Component::Ptr(new ax::NumberBox::Component(win, new ax::NumberBox::Info(info))));

	win->property.AddProperty("Editable");

	_currentColor = info.normal;

	// Builtin event connection.
	win->event.OnPaint = ax::WBind<ax::GC>(this, &NumberBox::OnPaint);
	win->event.OnMouseLeftDown = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftDown);
	win->event.OnMouseLeftUp = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftUp);
	win->event.OnMouseLeftDragging = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeftDragging);
	win->event.OnMouseEnter = ax::WBind<ax::Point>(this, &NumberBox::OnMouseEnter);
	win->event.OnMouseLeave = ax::WBind<ax::Point>(this, &NumberBox::OnMouseLeave);

	_bgImg = new ax::Image(info.img);

	_value = ax::util::Clamp<double>(value, _range.left, _range.right);

	_font = new ax::Font(0);
	_font->SetFontSize(10);

	_zeroToOneValue = _range.GetZeroToOneValue(_value);

	if (_events.value_change) {
		win->AddConnection(Events::VALUE_CHANGE, _events.value_change);
	}
}

ax::Window::Backbone* ax::NumberBox::GetCopy()
{
	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
	ax::NumberBox::Info* info = static_cast<ax::NumberBox::Info*>(widget->GetInfo());
	ax::NumberBox* nbox
		= new ax::NumberBox(win->dimension.GetRect(), _events, *info, _flags, _value, _range, _type,
			ax::util::Control::Unit::axCTRL_NO_UNIT, ax::util::Control::Interpolation::axCTRL_LINEAR, _label);
	return nbox;
}

double ax::NumberBox::GetValue()
{
	return _value;
}

void ax::NumberBox::SetRange(const ax::util::Range2D<double>& range)
{
	_range = range;
	_value = ax::util::Clamp<double>(_value, _range.left, _range.right);
	_zeroToOneValue = _range.GetZeroToOneValue(_value);
	win->Update();
}

void ax::NumberBox::SetControlType(ax::util::Control::Type type)
{
	_type = type;
	win->Update();
}

void ax::NumberBox::OnMouseEnter(const ax::Point& pos)
{
	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());

	_currentColor = info.hover;
	_nCurrentImg = axNUM_BOX_HOVER;
	win->Update();
}

void ax::NumberBox::OnMouseLeave(const ax::Point& pos)
{
	if (win->event.IsGrabbed()) {
		return;
	}

	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());
	_currentColor = info.normal;
	_nCurrentImg = axNUM_BOX_NORMAL;
	win->Update();
}

void ax::NumberBox::OnMouseLeftDown(const ax::Point& pos)
{
	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());

	_clickPosY = (pos - win->dimension.GetAbsoluteRect().position).y;
	_nCurrentImg = axNUM_BOX_DOWN;
	_currentColor = info.clicking;

	win->event.GrabMouse();
	win->Update();
}

void ax::NumberBox::OnMouseLeftUp(const ax::Point& pos)
{
	if (!win->event.IsGrabbed()) {
		return;
	}

	win->event.UnGrabMouse();
	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());

	if (win->event.IsMouseHoverWindow()) {
		_currentColor = info.hover;
		_nCurrentImg = axNUM_BOX_HOVER;
	}
	else {
		_currentColor = info.normal;
		_nCurrentImg = axNUM_BOX_NORMAL;
	}

	win->PushEvent(Events::VALUE_CHANGE, new Msg(_value));
	win->Update();
}

void ax::NumberBox::OnMouseLeftDragging(const ax::Point& pos)
{
	ax::Point pt(win->dimension.GetAbsoluteRect().position);
	ax::Point p = pos - pt;

	double delta = p.y - _clickPosY;

	_clickPosY = p.y;

	double v = -delta / 100.0;
	_zeroToOneValue += v;

	_zeroToOneValue = ax::util::Clamp<double>(_zeroToOneValue, 0.0, 1.0);
	_value = _range.GetValueFromZeroToOne(_zeroToOneValue);

	win->PushEvent(Events::VALUE_CHANGE, new Msg(_value));

	win->Update();
}

void ax::NumberBox::OnPaint(ax::GC gcs)
{
	ax::GC* gc = &gcs;
	ax::Rect rect0(win->dimension.GetDrawingRect());
	ax::Rect rect(win->dimension.GetRect());

	gc->SetColor(_currentColor);
	gc->DrawRectangle(rect0);

	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	ax::NumberBox::Info& info = *static_cast<ax::NumberBox::Info*>(widget->GetInfo());

	if (_bgImg->IsImageReady()) {
		if (info.single_img) {
			if (ax::util::HasFlag(Flags::NO_IMG_RESIZE, _flags)) {
				gc->DrawImage(_bgImg, ax::Point(0, 0));
			}
			else {
				gc->DrawImageResize(_bgImg, ax::Point(0, 0), rect0.size);
			}
		}
		else {
			gc->DrawPartOfImage(_bgImg, ax::Point(0, _nCurrentImg * rect.size.h), rect.size, ax::Point(0, 0));
		}
	}

	gc->SetColor(info.font_color);

	if (_type == ax::util::Control::Type::REAL) {
		std::string v = std::to_string(_value);
		if (_value < 0) {
			v.resize(5);
		}
		else {
			v.resize(4);
		}

		gc->DrawStringAlignedCenter(*_font, v, rect0);
	}
	else if (_type == ax::util::Control::Type::INTEGER) {
		std::string v = std::to_string((int)_value);
		gc->DrawStringAlignedCenter(*_font, v, rect0);
	}

	gc->SetColor(info.contour);
	gc->DrawRectangleContour(rect0);
}
