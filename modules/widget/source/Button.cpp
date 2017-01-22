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

#include "Button.hpp"

namespace ax {
/*
 * axButon::Flags.
 */
const util::Flag Button::Flags::SINGLE_IMG = util::FlagValue::FLAG_1;
const util::Flag Button::Flags::IMG_RESIZE = util::FlagValue::FLAG_2;
const util::Flag Button::Flags::CAN_SELECTED = util::FlagValue::FLAG_3;

/*
 * axButon::Msg.
 */
Button::Msg::Msg()
{
	_sender = nullptr;
}

Button::Msg::Msg(Button* sender, const std::string& msg)
{
	_sender = sender;
	_msg = msg;
}

Button* Button::Msg::GetSender() const
{
	return _sender;
}

std::string Button::Msg::GetMsg() const
{
	return _msg;
}

event::Msg* Button::Msg::GetCopy()
{
	return new Button::Msg(*this);
}

/*
 * ax::Button::Info.
 */
Button::Info::Info(const Color& normal_color, const Color& hover_color, const Color& clicked_color,
	const Color& selected_color, const Color& contour_color, const Color& font_color_,
	const int& corner_radius_)
	: widget::Info() // Heritage.
	, normal(normal_color) // Members.
	, hover(hover_color)
	, clicking(clicked_color)
	, selected(selected_color)
	, contour(contour_color)
	, font_color(font_color_)
	, corner_radius(corner_radius_)
{
}

Button::Info::Info(const std::string& path)
	: widget::Info(path)
{
}

Button::Info::Info(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	SetAttributes(attributes);
}

std::vector<std::string> Button::Info::GetParamNameList() const
{
	return std::vector<std::string>{ "normal", "hover", "clicking", "selected", "contour", "font_color",
		"corner_radius" };
}

std::string Button::Info::GetAttributeValue(const std::string& name)
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
	else if (name == "corner_radius") {
		return std::to_string(corner_radius);
	}

	return "";
}

void Button::Info::SetAttribute(const std::pair<std::string, std::string>& attribute)
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
	else if (attribute.first == "corner_radius") {
		corner_radius = std::stoi(attribute.second);
	}
}

std::vector<widget::ParamInfo> Button::Info::GetParametersInfo() const
{
	return { widget::ParamInfo(widget::ParamType::COLOR, "normal"),
		widget::ParamInfo(widget::ParamType::COLOR, "hover"),
		widget::ParamInfo(widget::ParamType::COLOR, "clicking"),
		widget::ParamInfo(widget::ParamType::COLOR, "selected"),
		widget::ParamInfo(widget::ParamType::COLOR, "contour"),
		widget::ParamInfo(widget::ParamType::COLOR, "font_color"),
		widget::ParamInfo(widget::ParamType::INTEGER, "corner_radius") };
}

Button::Component::Component(ax::Window* win, Info* info)
	: ax::widget::Component(win, info)
{
}

void Button::Component::SaveFromWidgetNode(ax::Xml& xml, ax::Xml::Node& widget_node)
{
	ax::Window* win = GetWindow();
	ax::Button* btn = win->GetBackbone<ax::Button>();
	ax::Button::Component::Ptr widget_comp = win->component.Get<ax::Button::Component>("Widget");
	ax::Button::Info* info = widget_comp->GetInfo<ax::Button::Info>();
	
	widget_node.AddAttribute("builder", "Button");
	
	const ax::Rect rect = win->dimension.GetRect();
	
	// Position.
	{
		std::string value_str(std::to_string(rect.position.x) + ", " + std::to_string(rect.position.y));
		widget_node.AddNode(xml.CreateNode("position", value_str));
	}
	
	// Size.
	{
		std::string value_str(std::to_string(rect.size.w) + ", " + std::to_string(rect.size.h));
		widget_node.AddNode(xml.CreateNode("size", value_str));
	}
	
	ax::Xml::Node info_node = xml.CreateNode("info");
	widget_node.AddNode(info_node);
	info_node.AddAttribute("normal", info->normal.ToString());
	info_node.AddAttribute("hover", info->hover.ToString());
	info_node.AddAttribute("clicking", info->clicking.ToString());
	info_node.AddAttribute("selected", info->selected.ToString());
	info_node.AddAttribute("contour", info->contour.ToString());
	info_node.AddAttribute("font_color", info->font_color.ToString());
	info_node.AddAttribute("corner_radius", std::to_string(info->corner_radius));
	
	widget_node.AddNode(xml.CreateNode("img_path", btn->GetImagePath()));
	widget_node.AddNode(xml.CreateNode("label", btn->GetLabel()));
	widget_node.AddNode(xml.CreateNode("msg", btn->GetMsg()));
	
	ax::Xml::Node flag_node = xml.CreateNode("flags");
	widget_node.AddNode(flag_node);
	
	ax::util::Flag flags = btn->GetFlags();
	const bool v_single_img = ax::util::HasFlag(Button::Flags::SINGLE_IMG, flags);
	const bool v_img_resize = ax::util::HasFlag(Button::Flags::IMG_RESIZE, flags);
	const bool v_can_selected = ax::util::HasFlag(Button::Flags::CAN_SELECTED, flags);
	
	flag_node.AddNode(xml.CreateNode("single_img", std::to_string((int)v_single_img)));
	flag_node.AddNode(xml.CreateNode("img_resize", std::to_string((int)v_img_resize)));
	flag_node.AddNode(xml.CreateNode("can_selected", std::to_string((int)v_can_selected)));
}

std::vector<std::pair<std::string, std::string>> Button::Component::GetBuilderAttributes()
{
	ax::Window* win = GetWindow();
	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
	ax::Button* btn = static_cast<ax::Button*>(bbone.get());

	std::vector<std::pair<std::string, std::string>> atts;

	ax::Point position = win->dimension.GetRect().position;
	std::string pos_str(std::to_string(position.x) + ", " + std::to_string(position.y));
	atts.push_back(std::pair<std::string, std::string>("position", pos_str));

	ax::Size size = win->dimension.GetSize();
	std::string size_str(std::to_string(size.w) + ", " + std::to_string(size.h));
	atts.push_back(std::pair<std::string, std::string>("size", size_str));

	atts.push_back(std::pair<std::string, std::string>("img_path", btn->GetImagePath()));
	atts.push_back(std::pair<std::string, std::string>("label", btn->GetLabel()));
	atts.push_back(std::pair<std::string, std::string>("msg", btn->GetMsg()));

	ax::util::Flag flags = btn->GetFlags();
	atts.push_back(std::pair<std::string, std::string>("single_img",
		std::to_string((int)ax::util::HasFlag(Button::Flags::SINGLE_IMG, flags))));
	
	atts.push_back(std::pair<std::string, std::string>("img_resize",
		std::to_string((int)ax::util::HasFlag(Button::Flags::IMG_RESIZE, flags))));
	
	atts.push_back(std::pair<std::string, std::string>("can_selected",
		std::to_string((int)ax::util::HasFlag(Button::Flags::CAN_SELECTED, flags))));

	return atts;
}

std::vector<ax::widget::ParamInfo> Button::Component::GetBuilderAttributesInfo() const
{
	return { ax::widget::ParamInfo(ax::widget::ParamType::POINT, "position"),
		ax::widget::ParamInfo(ax::widget::ParamType::SIZE, "size"),
		ax::widget::ParamInfo(ax::widget::ParamType::FILEPATH, "img_path"),
		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "label"),
//		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "flags"),
		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "msg"),
		ax::widget::ParamInfo(ax::widget::ParamType::BOOLEAN, "single_img"),
		ax::widget::ParamInfo(ax::widget::ParamType::BOOLEAN, "img_resize"),
		ax::widget::ParamInfo(ax::widget::ParamType::BOOLEAN, "can_selected") };
}

void Button::Component::SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	_info->SetAttributes(attributes);
}

void Button::Component::ReloadInfo()
{
	Button* btn = static_cast<Button*>(_win->backbone.get());
	Button::Info* info = static_cast<Button::Info*>(_info);

	switch (btn->_nCurrentImg) {
	case axBTN_NORMAL:
		btn->_currentColor = info->normal;
		break;
	case axBTN_HOVER:
		btn->_currentColor = info->hover;
		break;
	case axBTN_DOWN:
		btn->_currentColor = info->clicking;
		break;
	case axBTN_SELECTED:
		btn->_currentColor = info->selected;
		break;
	}

	_win->Update();
}

void Button::Component::SetBuilderAttributes(
	const std::vector<std::pair<std::string, std::string>>& attributes)
{
	ax::Button* btn = static_cast<ax::Button*>(GetWindow()->backbone.get());

	for (auto& n : attributes) {
		if (n.first == "position") {
			ax::Point pos(n.second);
			GetWindow()->dimension.SetPosition(pos);
		}
		else if (n.first == "size") {
			ax::Size size(n.second);
			GetWindow()->dimension.SetSize(size);
		}
		else if (n.first == "img_path") {
			btn->_btnImg.reset(new Image(n.second));
		}
		else if (n.first == "label") {
			btn->SetLabel(n.second);
		}
		else if (n.first == "msg") {
			btn->SetMsg(n.second);
		}
		else if (n.first == "single_img") {
			bool f_value = (bool)std::stoi(n.second);
			ax::util::Flag flags = btn->GetFlags();
			ax::util::SetFlag(Button::Flags::SINGLE_IMG, f_value, flags);
			btn->SetFlags(flags);
		}
		else if (n.first == "img_resize") {
			bool f_value = (bool)std::stoi(n.second);
			ax::util::Flag flags = btn->GetFlags();
			ax::util::SetFlag(Button::Flags::IMG_RESIZE, f_value, flags);
			btn->SetFlags(flags);
		}
		else if (n.first == "can_selected") {
			bool f_value = (bool)std::stoi(n.second);
			ax::util::Flag flags = btn->GetFlags();
			ax::util::SetFlag(Button::Flags::CAN_SELECTED, f_value, flags);
			btn->SetFlags(flags);
		}
	}

	_win->Update();
}

Button::Builder::Builder()
{
}

std::shared_ptr<ax::Window::Backbone> Button::Builder::Create(
	const ax::Point& pos, const std::string& file_path)
{
	ax::Xml xml(file_path);

	if (!xml.Parse()) {
		ax::console::Error("Parsing error.");
		return nullptr;
	}

	ax::Xml::Node control = xml.GetNode("Widget");
	std::string builder_name = control.GetAttribute("builder");
	std::string obj_name = control.GetAttribute("name");
	return CreateFromNodePosition(control, pos);
}

std::shared_ptr<ax::Window::Backbone> Button::Builder::Create(ax::Xml::Node& node)
{
	ax::Point pos(node.GetChildNodeValue("position"));
	return CreateFromNodePosition(node, pos);
}

std::shared_ptr<ax::Window::Backbone> Button::Builder::Create(ax::Attribute& node)
{
	return nullptr;
}

std::shared_ptr<ax::Window::Backbone> Button::Builder::CreateFromNodePosition(ax::Xml::Node& node, const ax::Point& pos)
{
	ax::Size size(node.GetChildNodeValue("size"));
	std::string img_path = node.GetChildNodeValue("img_path");
	std::string label = node.GetChildNodeValue("label");
	
	
	ax::Xml::Node flags_node = node.GetNode("flags");
	const std::string f_single_img = flags_node.GetChildNodeValue("single_img");
	const std::string f_img_resize = flags_node.GetChildNodeValue("img_resize");
	const std::string f_can_selected = flags_node.GetChildNodeValue("can_selected");
	
	bool v_single_img = (bool)std::stoi(f_single_img);
	bool v_img_resize = (bool)std::stoi(f_img_resize);
	bool v_can_selected = (bool)std::stoi(f_can_selected);
	
	ax::util::Flag flags = 0;
	ax::util::SetFlag(Flags::SINGLE_IMG, v_single_img, flags);
	ax::util::SetFlag(Flags::IMG_RESIZE, v_img_resize, flags);
	ax::util::SetFlag(Flags::CAN_SELECTED, v_can_selected, flags);
	
	std::string msg = node.GetChildNodeValue("msg");
	
	ax::Xml::Node info_node = node.GetNode("info");
	
	ax::Button::Info btn_info;
	btn_info.normal = ax::Color::FromString(info_node.GetAttribute("normal"));
	btn_info.hover = ax::Color::FromString(info_node.GetAttribute("hover"));
	btn_info.clicking = ax::Color::FromString(info_node.GetAttribute("clicking"));
	btn_info.selected = ax::Color::FromString(info_node.GetAttribute("selected"));
	btn_info.contour = ax::Color::FromString(info_node.GetAttribute("contour"));
	btn_info.font_color = ax::Color::FromString(info_node.GetAttribute("font_color"));
	btn_info.corner_radius = std::stoi(info_node.GetAttribute("corner_radius"));
	
	auto btn = ax::shared<ax::Button>(
		ax::Rect(pos, size), ax::Button::Events(), btn_info, img_path, label, flags, msg);
	
	return btn;
}

/*
 * ax::Buton::Button.
 */
Button::Button(const Rect& rect, const Button::Events& events, const Button::Info& info, std::string img_path,
	std::string label, util::Flag flags, std::string msg)
	: _events(events)
	, _flags(flags)
	, _label(label)
	, _msg(msg)
	, _font(0)
	, _selected(false)
	, _nCurrentImg(axBTN_NORMAL)
{
	win = Window::Create(rect);

	// Builtin event connection.
	win->event.OnPaint = WBind<GC>(this, &Button::OnPaint);
	win->event.OnMouseLeftDown = WBind<Point>(this, &Button::OnMouseLeftDown);
	win->event.OnMouseLeftUp = WBind<Point>(this, &Button::OnMouseLeftUp);
	win->event.OnMouseEnter = WBind<Point>(this, &Button::OnMouseEnter);
	win->event.OnMouseLeave = WBind<Point>(this, &Button::OnMouseLeave);
	win->event.OnMouseLeftDoubleClick = WBind<Point>(this, &Button::OnMouseLeftDoubleClick);

	win->component.Add("Widget", widget::Component::Ptr(new Button::Component(win, new Button::Info(info))));

	win->property.AddProperty("Editable");

	_currentColor = info.normal;

	_btnImg = std::unique_ptr<ax::Image>(new Image(img_path));

	if (_events.button_click) {
		win->AddConnection(Events::BUTTON_CLICK, _events.button_click);
	}
}

ax::Window::Backbone* Button::GetCopy()
{
	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
	ax::Button::Info* info = static_cast<ax::Button::Info*>(widget->GetInfo());
	ax::Button* btn = new ax::Button(
		win->dimension.GetRect(), _events, *info, _btnImg->GetImagePath(), _label, _flags, _msg);
	return btn;
}

Button::Button(const Point& pos, const Button::Events& events, std::string label, std::string img_path,
	const Button::Info& info, util::Flag flags,
	std::string msg)
	: _events(events) // Members.
	, _flags(flags)
	, _label(label)
	, _msg(msg)
	, _font(0)
	, _selected(false)
	, _nCurrentImg(axBTN_NORMAL)
{
	win = Window::Create(Rect(pos, Size(60, 25)));

	// Builtin event connection.
	win->event.OnPaint = WBind<GC>(this, &Button::OnPaint);
	win->event.OnMouseLeftDown = WBind<Point>(this, &Button::OnMouseLeftDown);
	win->event.OnMouseLeftUp = WBind<Point>(this, &Button::OnMouseLeftUp);
	win->event.OnMouseEnter = WBind<Point>(this, &Button::OnMouseEnter);
	win->event.OnMouseLeave = WBind<Point>(this, &Button::OnMouseLeave);
	win->event.OnMouseLeftDoubleClick = WBind<Point>(this, &Button::OnMouseLeftDoubleClick);

	win->component.Add("Widget", widget::Component::Ptr(new Button::Component(win, new Button::Info(info))));

	win->property.AddProperty("Editable");

	_currentColor = info.normal;

	_btnImg = std::unique_ptr<ax::Image>(new Image(img_path));

	if (_events.button_click) {
		win->AddConnection(Events::BUTTON_CLICK, _events.button_click);
	}
}

void Button::SetFlags(ax::util::Flag flags)
{
	if(flags == _flags) {
		// Nothing to do.
		return;
	}
	
	_flags = flags;
	win->Update();
}

void Button::SetMsg(const std::string& msg)
{
	_msg = msg;
}

void Button::SetSelected(const bool& selected)
{
	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");

	Button::Info& info = *static_cast<Button::Info*>(widget->GetInfo());

	if (_selected != selected) {
		_selected = selected;

		if (_selected) {
			if (_currentColor == info.normal) {
				_currentColor = info.selected;
			}
		}
		else {
			if (_currentColor == info.selected) {
				_currentColor = info.normal;
			}
		}
		win->Update();
	}
}

void Button::SetLabel(const std::string& label)
{
	_label = label;
	win->Update();
}

void Button::OnMouseLeftDown(const Point& pos)
{
	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	Button::Info& info = *static_cast<Button::Info*>(widget->GetInfo());

	_currentColor = info.clicking;
	_nCurrentImg = axBTN_DOWN;

	win->event.GrabMouse();

	win->PushEvent(Events::BUTTON_CLICK, new Msg(this, _msg));

	win->Update();
}

void Button::OnMouseLeftDoubleClick(const ax::Point& pos)
{
	OnMouseLeftDown(pos);
}

void Button::OnMouseLeftUp(const Point& pos)
{
	// If not grabbed.
	if (!win->event.IsGrabbed()) {
		return;
	}

	win->event.UnGrabMouse();

	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	Button::Info& info = *static_cast<Button::Info*>(widget->GetInfo());

	if (win->event.IsMouseHoverWindow()) {
		_currentColor = info.hover;
		_nCurrentImg = axBTN_HOVER;
		_selected = true;
	}
	else {
		if (_selected) {
			_currentColor = info.selected;
			_nCurrentImg = axBTN_SELECTED;
		}
		else {
			_currentColor = info.normal;
			_nCurrentImg = axBTN_NORMAL;
		}
	}

	win->Update();
}

void Button::OnMouseEnter(const Point& pos)
{
	// If window is grabbed.
	if (win->event.IsGrabbed()) {
		return;
	}

	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	Button::Info& info = *static_cast<Button::Info*>(widget->GetInfo());

	_currentColor = info.hover;
	_nCurrentImg = axBTN_HOVER;
	win->Update();
}

void Button::OnMouseLeave(const Point& pos)
{
	if (win->event.IsGrabbed()) {
		return;
	}

	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	Button::Info& info = *static_cast<Button::Info*>(widget->GetInfo());

	if (_selected) {
		_currentColor = info.selected;
		_nCurrentImg = axBTN_SELECTED;
	}
	else {
		_currentColor = info.normal;
		_nCurrentImg = axBTN_NORMAL;
	}

	win->Update();
}

void Button::OnPaint(GC gc)
{
	Rect rect(win->dimension.GetRect());
	Rect rect0(win->dimension.GetDrawingRect());

	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	Button::Info* info = static_cast<Button::Info*>(widget->GetInfo());

	gc.SetColor(_currentColor);

	int radius = info->corner_radius;

	if (radius > 1) {
		gc.DrawRoundedRectangle(rect0, radius);
	}
	else {
		gc.DrawRectangle(rect0);
	}

	if (_btnImg->IsImageReady()) {
		if (ax::util::HasFlag(Flags::SINGLE_IMG, _flags)) {
			gc.DrawImageResize(_btnImg.get(), rect0.position, rect0.size - ax::Size(1, 1), 1.0);
		}
		else {
			//			gc.DrawPartOfImage(_btnImg.get(), Point(0, _nCurrentImg * rect.size.y), rect.size,
			// Point(0, 0));
			// rect0.size - ax::Size(1, 1)

			int in_img_h = _btnImg->GetSize().h / 3;

			gc.DrawPartOfImageResize(_btnImg.get(), Point(0, _nCurrentImg * in_img_h),
				ax::Size(_btnImg->GetSize().w, in_img_h), ax::Rect(ax::Point(0, 0), rect.size));
		}
	}

	if (!_label.empty()) {
		gc.SetColor(info->font_color, 1.0);
		gc.DrawStringAlignedCenter(_font, _label, rect0);
	}

	gc.SetColor(info->contour);

	if (radius > 1) {
		gc.DrawRoundedRectangleContour(rect0, radius);
	}
	else {
		gc.DrawRectangleContour(rect0);
	}
}
}
