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

#include "Toggle.hpp"

/*
 * axToggle::Flags.
 */
const ax::util::Flag ax::Toggle::Flags::SINGLE_IMG = util::FlagValue::FLAG_1;
const ax::util::Flag ax::Toggle::Flags::IMG_RESIZE = util::FlagValue::FLAG_2;
const ax::util::Flag ax::Toggle::Flags::CLICK_ON_LEFT_DOWN = util::FlagValue::FLAG_3;
const ax::util::Flag ax::Toggle::Flags::CANT_UNSELECT_WITH_MOUSE = util::FlagValue::FLAG_4;

/*
 * axToggle::Msg.
 */
ax::Toggle::Msg::Msg()
{
	_sender = nullptr;
}

ax::Toggle::Msg::Msg(ax::Toggle* sender, const bool& selected)
{
	_sender = sender;
	_selected = selected;
	_msg = std::string("");
}

ax::Toggle::Msg::Msg(ax::Toggle* sender, const bool& selected, const std::string& msg)
{
	_sender = sender;
	_selected = selected;
	_msg = msg;
}

ax::Toggle* ax::Toggle::Msg::GetSender() const
{
	return _sender;
}

bool ax::Toggle::Msg::GetSelected() const
{
	return _selected;
}

std::string ax::Toggle::Msg::GetMsg() const
{
	return _msg;
}

ax::event::Msg* ax::Toggle::Msg::GetCopy()
{
	return new Msg(*this);
}

/*
 * axToggle::Info.
 */
ax::Toggle::Info::Info()
	: ax::widget::Info()
	, normal(0.5f)
	, hover(0.6f)
	, clicking(0.4f)
	, font_color(0.0)
	, selected(0.7f)
	, selected_hover(0.8f)
	, selected_clicking(0.6f)
	, contour(0.0)
	, img("")
	, single_img(false)
{
}

std::vector<std::string> ax::Toggle::Info::GetParamNameList() const
{
	return std::vector<std::string>{ "normal", "hover", "clicking", "selected", "selected_hover",
		"selected_clicking", "contour", "font_color", "img", "single_img" };
}

std::string ax::Toggle::Info::GetAttributeValue(const std::string& name)
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
	else if (name == "selected_hover") {
		return selected_hover.ToString();
	}
	else if (name == "selected_clicking") {
		return selected_clicking.ToString();
	}
	else if (name == "selected_font_color") {
		return selected_font_color.ToString();
	}
	else if (name == "contour") {
		return contour.ToString();
	}
	else if (name == "font_color") {
		return font_color.ToString();
	}
	else if (name == "font_size") {
		return std::to_string((int)font_size);
	}
	else if (name == "img") {
		return img;
	}
	else if (name == "single_img") {
		return std::to_string((int)single_img);
	}

	return "";
}

void ax::Toggle::Info::SetAttribute(const std::pair<std::string, std::string>& attribute)
{
	//	if (attribute.first == "normal") {
	//		normal = ax::Color::FromString(attribute.second);
	//	}
	//	else if (attribute.first == "hover") {
	//		hover = ax::Color::FromString(attribute.second);
	//	}
	//	else if (attribute.first == "clicking") {
	//		clicking = ax::Color::FromString(attribute.second);
	//	}
	//	else if (attribute.first == "selected") {
	//		selected = ax::Color::FromString(attribute.second);
	//	}
	//	else if (attribute.first == "selected_hover") {
	//		selected_hover = ax::Color::FromString(attribute.second);
	//	}
	//	else if (attribute.first == "selected_clicking") {
	//		selected_clicking = ax::Color::FromString(attribute.second);
	//	}
	//	else if (attribute.first == "selected_font_color") {
	//		selected_font_color = ax::Color::FromString(attribute.second);
	//	}
	//	else if (attribute.first == "contour") {
	//		contour = ax::Color::FromString(attribute.second);
	//	}
	//	else if (attribute.first == "font_color") {
	//		font_color = ax::Color::FromString(attribute.second);
	//	}
	//	else if (attribute.first == "font_size") {
	//		font_size = std::stoi(attribute.second);
	//	}
	//	else if (attribute.first == "img") {
	//		img = attribute.second;
	//	}
	//	else if (attribute.first == "single_img") {
	//		single_img = std::stoi(attribute.second);
	//	}
}

ax::Toggle::Component::Component(ax::Window* win, Info* info)
	: ax::widget::Component(win, info)
{
}

ax::Xml::Node ax::Toggle::Component::Save(ax::Xml& xml, ax::Xml::Node& node)
{
	ax::Window* win = GetWindow();
	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
	ax::Toggle* tog = static_cast<ax::Toggle*>(bbone.get());

	ax::Toggle::Component* widget_comp
		= static_cast<ax::Toggle::Component*>(win->component.Get("Widget").get());

	ax::Toggle::Info* info = static_cast<ax::Toggle::Info*>(widget_comp->GetInfo());

	ax::Xml::Node widget_node = xml.CreateNode("Widget");
	node.AddNode(widget_node);
	widget_node.AddAttribute("builder", "Toggle");

	ax::Rect rect = win->dimension.GetRect();

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
	info_node.AddAttribute("selected_hover", info->selected_hover.ToString());
	info_node.AddAttribute("selected_clicking", info->selected_clicking.ToString());
	info_node.AddAttribute("selected_font_color", info->selected_font_color.ToString());
	info_node.AddAttribute("selected", info->selected.ToString());

	info_node.AddAttribute("contour", info->contour.ToString());
	info_node.AddAttribute("font_color", info->font_color.ToString());

	info_node.AddAttribute("font_size", std::to_string(info->font_size));

	info_node.AddAttribute("img", info->img);
	info_node.AddAttribute("single_img", std::to_string((int)info->single_img));

	//	widget_node.AddNode(xml.CreateNode("img_path", tog->GetImagePath()));
	widget_node.AddNode(xml.CreateNode("label", tog->GetLabel()));

	ax::util::Flag flags = tog->GetFlags();
	std::vector<std::string> atts;

	if (ax::util::HasFlag(ax::Toggle::Flags::SINGLE_IMG, flags)) {
		atts.push_back("SINGLE_IMG");
	}

	if (ax::util::HasFlag(ax::Toggle::Flags::IMG_RESIZE, flags)) {
		atts.push_back("IMG_RESIZE");
	}

	if (ax::util::HasFlag(ax::Toggle::Flags::CLICK_ON_LEFT_DOWN, flags)) {
		atts.push_back("CLICK_ON_LEFT_DOWN");
	}

	if (ax::util::HasFlag(ax::Toggle::Flags::CANT_UNSELECT_WITH_MOUSE, flags)) {
		atts.push_back("CANT_UNSELECT_WITH_MOUSE");
	}

	std::string value_str;

	if (atts.empty()) {
	}
	else {
		value_str = atts[0];
		for (int i = 1; i < atts.size(); i++) {
			value_str += ",";
			value_str += atts[i];
		}
	}

	widget_node.AddNode(xml.CreateNode("flags", value_str));
	widget_node.AddNode(xml.CreateNode("msg", tog->GetMsg()));

	return widget_node;
}

std::vector<std::pair<std::string, std::string>> ax::Toggle::Component::GetBuilderAttributes()
{
	ax::Window* win = GetWindow();
	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
	ax::Toggle* btn = static_cast<ax::Toggle*>(bbone.get());

	std::vector<std::pair<std::string, std::string>> atts;

	ax::Point position = win->dimension.GetRect().position;
	std::string pos_str(std::to_string(position.x) + ", " + std::to_string(position.y));
	atts.push_back(std::pair<std::string, std::string>("position", pos_str));

	ax::Size size = win->dimension.GetSize();
	std::string size_str(std::to_string(size.w) + ", " + std::to_string(size.h));
	atts.push_back(std::pair<std::string, std::string>("size", size_str));
	atts.push_back(std::pair<std::string, std::string>("label", btn->GetLabel()));
	atts.push_back(std::pair<std::string, std::string>("msg", btn->GetMsg()));
	atts.push_back(std::pair<std::string, std::string>("flags", std::to_string(btn->GetFlags())));

	return atts;
}

std::vector<ax::widget::ParamInfo> ax::Toggle::Component::GetBuilderAttributesInfo() const
{
	return { ax::widget::ParamInfo(ax::widget::ParamType::POINT, "position"),
		ax::widget::ParamInfo(ax::widget::ParamType::SIZE, "size"),
		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "label"),
		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "msg"),
		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "flags") };
}

void ax::Toggle::Component::SetBuilderAttributes(
	const std::vector<std::pair<std::string, std::string>>& attributes)
{
	//	ax::Toggle* tog = static_cast<ax::Toggle*>(GetWindow()->backbone.get());
	//
	//	for (auto& n : attributes) {
	//		if (n.first == "position") {
	//			ax::Point pos = ax::Xml::StringToSize(n.second);
	//			GetWindow()->dimension.SetPosition(pos);
	//		}
	//		else if (n.first == "size") {
	//			ax::Size size = ax::Xml::StringToSize(n.second);
	//			GetWindow()->dimension.SetSize(size);
	//		}
	//		else if (n.first == "label") {
	//			tog->SetLabel(n.second);
	//		}
	//		else if (n.first == "msg") {
	//			tog->SetMsg(n.second);
	//		}
	//	}
	//
	//	GetWindow()->Update();
}

void ax::Toggle::Component::ReloadInfo()
{
	Toggle* tog = static_cast<Toggle*>(_win->backbone.get());
	Toggle::Info* info = static_cast<Toggle::Info*>(_info);

	switch (tog->_nCurrentImg) {
	case axTOG_NORMAL:
		tog->_currentColor = info->normal;
		break;
	case axTOG_HOVER:
		tog->_currentColor = info->hover;
		break;
	case axTOG_CLICK:
		tog->_currentColor = info->clicking;
		break;
	case axTOG_SEL_NORMAL:
		tog->_currentColor = info->selected;
		break;
	case axTOG_SEL_HOVER:
		tog->_currentColor = info->selected_hover;
		break;
	case axTOG_SEL_CLICK:
		tog->_currentColor = info->selected_clicking;
		break;
	}

	if (tog->_bgImg->GetImagePath() != info->img) {
		tog->_bgImg.reset(new ax::Image(info->img));
	}

	_win->Update();
}

void ax::Toggle::Component::SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	_info->SetAttributes(attributes);
}

ax::Toggle::Builder::Builder()
{
}

std::shared_ptr<ax::Window::Backbone> ax::Toggle::Builder::Create(
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

	//	ax::Print(builder_name, obj_name);

	ax::Size size(control.GetChildNodeValue("size"));
	//	std::string img_path = control.GetChildNodeValue("img_path");
	std::string label = control.GetChildNodeValue("label");

	std::vector<std::string> flags_strs = ax::util::String::Split(control.GetChildNodeValue("flags"), ",");

	ax::util::Flag flags = 0;
	for (auto& n : flags_strs) {

		if (n == "SINGLE_IMG") {
			flags |= ax::Toggle::Flags::SINGLE_IMG;
		}
		else if (n == "IMG_RESIZE") {
			flags |= ax::Toggle::Flags::IMG_RESIZE;
		}
		else if (n == "CLICK_ON_LEFT_DOWN") {
			flags |= ax::Toggle::Flags::CLICK_ON_LEFT_DOWN;
		}
		else if (n == "CANT_UNSELECT_WITH_MOUSE") {
			flags |= ax::Toggle::Flags::CANT_UNSELECT_WITH_MOUSE;
		}
	}

	std::string msg = control.GetChildNodeValue("msg");

	ax::Xml::Node info_node = control.GetNode("info");
	ax::Toggle::Info tog_info;
	tog_info.normal = ax::Color::FromString(info_node.GetAttribute("normal"));
	tog_info.hover = ax::Color::FromString(info_node.GetAttribute("hover"));
	tog_info.clicking = ax::Color::FromString(info_node.GetAttribute("clicking"));
	tog_info.selected = ax::Color::FromString(info_node.GetAttribute("selected"));
	tog_info.selected_hover = ax::Color::FromString(info_node.GetAttribute("selected_hover"));
	tog_info.selected_clicking = ax::Color::FromString(info_node.GetAttribute("selected_clicking"));
	tog_info.selected_font_color = ax::Color::FromString(info_node.GetAttribute("selected_font_color"));
	tog_info.contour = ax::Color::FromString(info_node.GetAttribute("contour"));
	tog_info.font_color = ax::Color::FromString(info_node.GetAttribute("font_color"));
	tog_info.font_size = std::stoi(info_node.GetAttribute("font_size"));
	tog_info.img = info_node.GetAttribute("img");
	tog_info.single_img = std::stoi(info_node.GetAttribute("single_img"));

	auto tog
		= ax::shared<ax::Toggle>(ax::Rect(pos, size), ax::Toggle::Events(), tog_info, "", label, flags, msg);

	return tog;
}

std::shared_ptr<ax::Window::Backbone> ax::Toggle::Builder::Create(ax::Xml::Node& node)
{
	std::string builder_name = node.GetAttribute("builder");

	//	ax::Print(builder_name);

	ax::Point pos(node.GetChildNodeValue("position"));
	ax::Size size(node.GetChildNodeValue("size"));
	std::string label = node.GetChildNodeValue("label");

	std::vector<std::string> flags_strs = ax::util::String::Split(node.GetChildNodeValue("flags"), ",");

	ax::util::Flag flags = 0;
	for (auto& n : flags_strs) {

		if (n == "SINGLE_IMG") {
			flags |= ax::Toggle::Flags::SINGLE_IMG;
		}
		else if (n == "IMG_RESIZE") {
			flags |= ax::Toggle::Flags::IMG_RESIZE;
		}
		else if (n == "CLICK_ON_LEFT_DOWN") {
			flags |= ax::Toggle::Flags::CLICK_ON_LEFT_DOWN;
		}
		else if (n == "CANT_UNSELECT_WITH_MOUSE") {
			flags |= ax::Toggle::Flags::CANT_UNSELECT_WITH_MOUSE;
		}
	}

	std::string msg = node.GetChildNodeValue("msg");

	ax::Xml::Node info_node = node.GetNode("info");
	ax::Toggle::Info tog_info;
	tog_info.normal = ax::Color::FromString(info_node.GetAttribute("normal"));
	tog_info.hover = ax::Color::FromString(info_node.GetAttribute("hover"));
	tog_info.clicking = ax::Color::FromString(info_node.GetAttribute("clicking"));
	tog_info.selected = ax::Color::FromString(info_node.GetAttribute("selected"));
	tog_info.selected_hover = ax::Color::FromString(info_node.GetAttribute("selected_hover"));
	tog_info.selected_clicking = ax::Color::FromString(info_node.GetAttribute("selected_clicking"));
	tog_info.selected_font_color = ax::Color::FromString(info_node.GetAttribute("selected_font_color"));
	tog_info.contour = ax::Color::FromString(info_node.GetAttribute("contour"));
	tog_info.font_color = ax::Color::FromString(info_node.GetAttribute("font_color"));
	tog_info.font_size = std::stoi(info_node.GetAttribute("font_size"));
	tog_info.img = info_node.GetAttribute("img");
	tog_info.single_img = std::stoi(info_node.GetAttribute("single_img"));

	auto tog
		= ax::shared<ax::Toggle>(ax::Rect(pos, size), ax::Toggle::Events(), tog_info, "", label, flags, msg);

	return tog;
}

/*
 * axToggle::axToggle.
 */
ax::Toggle::Toggle(const ax::Rect& rect, const ax::Toggle::Events& events, const ax::Toggle::Info& info,
	std::string img_path, std::string label, ax::util::Flag flags, std::string msg)
	: _nCurrentImg(axTOG_NORMAL)
	, _events(events)
	, _label(label)
	, _msg(msg)
	, _font(nullptr)
	, _selected(false)
	, _flags(flags)
{
	win = ax::Window::Create(rect);
	win->event.OnPaint = ax::WBind<ax::GC>(this, &Toggle::OnPaint);
	win->event.OnMouseLeftDown = ax::WBind<ax::Point>(this, &Toggle::OnMouseLeftDown);
	win->event.OnMouseLeftUp = ax::WBind<ax::Point>(this, &Toggle::OnMouseLeftUp);
	win->event.OnMouseEnter = ax::WBind<ax::Point>(this, &Toggle::OnMouseEnter);
	win->event.OnMouseLeave = ax::WBind<ax::Point>(this, &Toggle::OnMouseLeave);
	win->event.OnMouseLeftDoubleClick = ax::WBind<ax::Point>(this, &Toggle::OnMouseLeftDoubleClick);

	// Add info component.
	win->component.Add(
		"Widget", widget::Component::Ptr(new ax::Toggle::Component(win, new ax::Toggle::Info(info))));

	// Local info pointer.
	_info = static_cast<ax::Toggle::Info*>(win->component.Get<widget::Component>("Widget")->GetInfo());

	_currentColor = info.normal;
	_bgImg = std::shared_ptr<ax::Image>(new ax::Image(_info->img));

	_font = std::unique_ptr<ax::Font>(new ax::Font(0));
	_font->SetFontSize(info.font_size);

	if (_events.button_click) {
		win->AddConnection(Events::BUTTON_CLICK, _events.button_click);
	}
}

ax::Window::Backbone* ax::Toggle::GetCopy()
{
	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
	ax::Toggle::Info* info = static_cast<ax::Toggle::Info*>(widget->GetInfo());
	ax::Toggle* tog = new ax::Toggle(
		win->dimension.GetRect(), _events, *info, _bgImg->GetImagePath(), _label, _flags, _msg);
	return tog;
}

void ax::Toggle::SetMsg(const std::string& msg)
{
	_msg = msg;
}

void ax::Toggle::SetSelected(const bool& selected)
{
	if (_selected != selected) {
		_selected = selected;

		widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
		ax::Toggle::Info& info = *static_cast<ax::Toggle::Info*>(widget->GetInfo());

		if (_selected) {
			_nCurrentImg = axTOG_SEL_NORMAL;
			if (_currentColor == info.normal) {
				_currentColor = info.selected;
				win->Update();
			}
		}
		else {
			_nCurrentImg = axTOG_NORMAL;
			if (_currentColor == info.selected) {
				_currentColor = info.normal;
				win->Update();
			}
		}
	}
}

void ax::Toggle::OnMouseLeftDown(const ax::Point& pos)
{
	if (_selected && ax::util::HasFlag(Flags::CANT_UNSELECT_WITH_MOUSE, _flags)) {
		// Don't do anything.
	}
	else {
		// Only switch selection on toggle_on_left_down.
		if (ax::util::HasFlag(Flags::CLICK_ON_LEFT_DOWN, _flags)) {
			_selected = !_selected;
		}

		if (_selected) {
			_currentColor = _info->selected_clicking;
			_nCurrentImg = axTOG_SEL_CLICK;
		}
		else {
			_currentColor = _info->clicking;
			_nCurrentImg = axTOG_CLICK;
		}

		win->event.GrabMouse();

		if (ax::util::HasFlag(Flags::CLICK_ON_LEFT_DOWN, _flags)) {
			win->PushEvent(Events::BUTTON_CLICK, new Msg(this, _selected, _msg));
		}

		win->Update();
	}
}

void ax::Toggle::OnMouseLeftUp(const ax::Point& pos)
{
	if (win->event.IsGrabbed()) {
		win->event.UnGrabMouse();

		// If mouse release if still on the toggle.
		if (win->event.IsMouseHoverWindow()) {
			// Only invert selection on toggle_on_left_up.
			if (!ax::util::HasFlag(Flags::CLICK_ON_LEFT_DOWN, _flags)) {
				_selected = !_selected;
			}

			if (_selected) {
				_currentColor = _info->selected_hover;
				_nCurrentImg = axTOG_SEL_HOVER;
			}
			else {
				_currentColor = _info->hover;
				_nCurrentImg = axTOG_HOVER;
			}

			// If toggle on left up.
			if (!ax::util::HasFlag(Flags::CLICK_ON_LEFT_DOWN, _flags)) {
				win->PushEvent(Events::BUTTON_CLICK, new Msg(this, _selected, _msg));
			}
		}
		else {
			if (_selected) {
				_currentColor = _info->selected;
				_nCurrentImg = axTOG_SEL_NORMAL;
			}
			else {
				_currentColor = _info->normal;
				_nCurrentImg = axTOG_NORMAL;
			}
		}

		win->Update();
	}
}

void ax::Toggle::OnMouseEnter(const ax::Point& pos)
{
	if (!win->event.IsGrabbed()) {
		if (_selected) {
			_currentColor = _info->selected_hover;
			_nCurrentImg = axTOG_SEL_HOVER;
		}
		else {
			_currentColor = _info->hover;
			_nCurrentImg = axTOG_HOVER;
		}

		win->Update();
	}
}

void ax::Toggle::OnMouseLeave(const ax::Point& pos)
{
	if (!win->event.IsGrabbed()) {
		if (_selected) {
			_currentColor = _info->selected;
			_nCurrentImg = axTOG_SEL_NORMAL;
		}
		else {
			_currentColor = _info->normal;
			_nCurrentImg = axTOG_NORMAL;
		}
	}

	win->Update();
}

void ax::Toggle::OnMouseLeftDoubleClick(const ax::Point& pos)
{
	OnMouseLeftDown(pos);
}

void ax::Toggle::OnPaint(ax::GC gc)
{
	ax::Rect rect(win->dimension.GetRect());
	ax::Rect rect0(win->dimension.GetDrawingRect());

	gc.SetColor(_currentColor);
	gc.DrawRectangle(rect0);

	if (_bgImg->IsImageReady()) {
		if (_info->single_img) {
			gc.DrawImageResize(_bgImg.get(), ax::Point(0, 0), rect.size, 1.0);
		}
		else {
			ax::Point pos(0, _nCurrentImg * _bgImg->GetSize().h / 6);
			ax::Size size(_bgImg->GetSize().w, _bgImg->GetSize().h / 6);

			gc.DrawPartOfImageResize(_bgImg.get(), pos, size, ax::Rect(ax::Point(0, 0), rect.size));
		}
	}

	if (!_label.empty()) {
		if (_selected) {
			gc.SetColor(_info->selected_font_color);
		}
		else {
			gc.SetColor(_info->font_color);
		}

		gc.DrawStringAlignedCenter(*_font, _label, rect0);
	}

	gc.SetColor(_info->contour);
	gc.DrawRectangleContour(rect0);
}
