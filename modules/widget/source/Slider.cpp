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
//#include "Slider.hpp"
//
//namespace ax {
///*
// * ax::Slider::Flags.
// */
//const Flag Slider::Flags::VERTICAL = FlagValue::FLAG_1;
//const Flag Slider::Flags::CLICK_ANYWHERE = FlagValue::FLAG_2;
//const Flag Slider::Flags::RELEASE_ON_LEAVE = FlagValue::FLAG_3;
//const Flag Slider::Flags::LEFT_CLICK_ENTER = FlagValue::FLAG_4;
//const Flag Slider::Flags::RIGHT_ALIGN = FlagValue::FLAG_5;
//const Flag Slider::Flags::MIDDLE_ALIGN = FlagValue::FLAG_6;
//const Flag Slider::Flags::BACK_SLIDER = FlagValue::FLAG_7;
//const Flag Slider::Flags::NO_SLIDER_LINE = FlagValue::FLAG_8;
//
//Slider::Info::Info(const std::string& path)
//{
//}
//
//Slider::Info::Info(const ax::StringPairVector& attributes)
//{
//}
//
//Slider::Info::Info()
//	: img_path("")
//	, btn_size(0, 0)
//	, bgColorNormal(0.9)
//	, bgColorHover(0.92)
//	, bgColorClicked(0.91)
//	, sliderColorNormal(220, 0, 0)
//	, sliderColorHover(225, 0, 0)
//	, sliderColorClicked(223, 0, 0)
//	, sliderContourColor(0.0)
//	, contourColor(0.0)
//	, backSliderColor(0.5)
//	, backSliderContourColor(0.6)
//	, slider_width(8)
//	, contour_round_radius(0)
//{
//}
//
//std::string Slider::Info::GetAttributeValue(const std::string& name)
//{
//	if (name == "img_path") {
//		return img_path;
//	}
//	else if (name == "btn_size") {
//		return std::to_string(btn_size);
//	}
//	else if (name == "slider_width") {
//		return std::to_string(slider_width);
//	}
//	else if (name == "contour_round_radius") {
//		return std::to_string(contour_round_radius);
//	}
//	else if (name == "bgColorNormal") {
//		return bgColorNormal.ToString();
//	}
//	else if (name == "bgColorHover") {
//		return bgColorHover.ToString();
//	}
//	else if (name == "bgColorClicked") {
//		return bgColorClicked.ToString();
//	}
//	else if (name == "sliderColorNormal") {
//		return sliderColorNormal.ToString();
//	}
//	else if (name == "sliderColorHover") {
//		return sliderColorHover.ToString();
//	}
//	else if (name == "sliderColorClicked") {
//		return sliderColorClicked.ToString();
//	}
//	else if (name == "sliderContourColor") {
//		return sliderContourColor.ToString();
//	}
//	else if (name == "contourColor") {
//		return contourColor.ToString();
//	}
//	else if (name == "backSliderColor") {
//		return backSliderColor.ToString();
//	}
//	else if (name == "backSliderContourColor") {
//		return backSliderContourColor.ToString();
//	}
//
//	return "";
//}
//
//void Slider::Info::SetAttribute(const ax::StringPair& attribute)
//{
//	if (attribute.first == "img_path") {
//		img_path = attribute.second;
//	}
//	else if (attribute.first == "btn_size") {
//		btn_size = ax::Xml::StringToSize(attribute.second);
//	}
//	else if (attribute.first == "slider_width") {
//		slider_width = std::stoi(attribute.second);
//	}
//	else if (attribute.first == "contour_round_radius") {
//		contour_round_radius = std::stoi(attribute.second);
//	}
//	else if (attribute.first == "bgColorNormal") {
//		bgColorNormal = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "bgColorHover") {
//		bgColorHover = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "bgColorClicked") {
//		bgColorClicked = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "sliderColorNormal") {
//		sliderColorNormal = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "sliderColorHover") {
//		sliderColorHover = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "sliderColorClicked") {
//		sliderColorClicked = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "sliderContourColor") {
//		sliderContourColor = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "contourColor") {
//		contourColor = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "backSliderColor") {
//		backSliderColor = ax::Xml::StringToColor(attribute.second);
//	}
//	else if (attribute.first == "backSliderContourColor") {
//		backSliderContourColor = ax::Xml::StringToColor(attribute.second);
//	}
//}
//
///// Info needed for debug editor. Derived from axInfo.
//std::vector<std::string> Slider::Info::GetParamNameList() const
//{
//	return std::vector<std::string>{ "img_path", "btn_size", "bgColorNormal", "bgColorHover",
//		"bgColorClicked", "sliderColorNormal", "sliderColorHover", "sliderColorClicked", "sliderContourColor",
//		"contourColor", "backSliderColor", "backSliderContourColor", "slider_width", "contour_round_radius" };
//}
//
//std::vector<widget::ParamInfo> Slider::Info::GetParametersInfo() const
//{
//	return { widget::ParamInfo(widget::ParamType::COLOR, "bgColorNormal"),
//		widget::ParamInfo(widget::ParamType::COLOR, "bgColorHover"),
//		widget::ParamInfo(widget::ParamType::COLOR, "bgColorClicked"),
//
//		widget::ParamInfo(widget::ParamType::COLOR, "sliderColorNormal"),
//		widget::ParamInfo(widget::ParamType::COLOR, "sliderColorHover"),
//		widget::ParamInfo(widget::ParamType::COLOR, "sliderColorClicked"),
//		widget::ParamInfo(widget::ParamType::COLOR, "sliderContourColor"),
//
//		widget::ParamInfo(widget::ParamType::COLOR, "contourColor"),
//		widget::ParamInfo(widget::ParamType::COLOR, "backSliderColor"),
//		widget::ParamInfo(widget::ParamType::COLOR, "backSliderContourColor"),
//
//		widget::ParamInfo(widget::ParamType::FILEPATH, "img_path"),
//		widget::ParamInfo(widget::ParamType::SIZE, "btn_size"),
//		widget::ParamInfo(widget::ParamType::INTEGER, "slider_width"),
//		widget::ParamInfo(widget::ParamType::INTEGER, "contour_round_radius") };
//}
//
//Slider::Component::Component(ax::Window* win, Info* info)
//	: ax::widget::Component(win, info)
//{
//}
//
//ax::Xml::Node Slider::Component::Save(ax::Xml& xml, ax::Xml::Node& node)
//{
//	ax::Window* win = GetWindow();
//	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
//	ax::Slider* sld = static_cast<ax::Slider*>(bbone.get());
//
//	ax::Slider::Component* widget_comp
//		= static_cast<ax::Slider::Component*>(win->component.Get("Widget").get());
//
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget_comp->GetInfo());
//
//	ax::Xml::Node widget_node = xml.CreateNode("Widget");
//	node.AddNode(widget_node);
//	widget_node.AddAttribute("builder", "Slider");
//
//	ax::Rect rect = win->dimension.GetRect();
//	widget_node.AddNode(xml.CreateNode("position", std::to_string(rect.position)));
//	widget_node.AddNode(xml.CreateNode("size", std::to_string(rect.size)));
//
//	ax::Xml::Node info_node = xml.CreateNode("info");
//	widget_node.AddNode(info_node);
//	info_node.AddAttribute("img_path", info->img_path);
//	info_node.AddAttribute("btn_size", std::to_string(info->btn_size));
//	info_node.AddAttribute("slider_width", std::to_string(info->slider_width));
//	info_node.AddAttribute("contour_round_radius", std::to_string(info->contour_round_radius));
//
//	info_node.AddAttribute("bgColorNormal", std::to_string(info->bgColorNormal));
//	info_node.AddAttribute("bgColorHover", std::to_string(info->bgColorHover));
//	info_node.AddAttribute("bgColorClicked", std::to_string(info->bgColorClicked));
//
//	info_node.AddAttribute("sliderColorNormal", std::to_string(info->sliderColorNormal));
//	info_node.AddAttribute("sliderColorHover", std::to_string(info->sliderColorHover));
//	info_node.AddAttribute("sliderColorClicked", std::to_string(info->sliderColorClicked));
//
//	info_node.AddAttribute("sliderContourColor", std::to_string(info->sliderContourColor));
//	info_node.AddAttribute("contourColor", std::to_string(info->contourColor));
//	info_node.AddAttribute("backSliderColor", std::to_string(info->backSliderColor));
//	info_node.AddAttribute("backSliderContourColor", std::to_string(info->backSliderContourColor));
//
//	widget_node.AddNode(xml.CreateNode("value", std::to_string(sld->GetValue())));
//
//	ax::Flag flags = sld->GetFlags();
//	std::vector<std::string> atts;
//
//	if (ax::IsFlag(Slider::Flags::VERTICAL, flags)) {
//		atts.push_back("VERTICAL");
//	}
//	if (ax::IsFlag(Slider::Flags::CLICK_ANYWHERE, flags)) {
//		atts.push_back("CLICK_ANYWHERE");
//	}
//	if (ax::IsFlag(Slider::Flags::RELEASE_ON_LEAVE, flags)) {
//		atts.push_back("RELEASE_ON_LEAVE");
//	}
//	if (ax::IsFlag(Slider::Flags::LEFT_CLICK_ENTER, flags)) {
//		atts.push_back("LEFT_CLICK_ENTER");
//	}
//	if (ax::IsFlag(Slider::Flags::RIGHT_ALIGN, flags)) {
//		atts.push_back("RIGHT_ALIGN");
//	}
//	if (ax::IsFlag(Slider::Flags::MIDDLE_ALIGN, flags)) {
//		atts.push_back("MIDDLE_ALIGN");
//	}
//	if (ax::IsFlag(Slider::Flags::BACK_SLIDER, flags)) {
//		atts.push_back("BACK_SLIDER");
//	}
//	if (ax::IsFlag(Slider::Flags::NO_SLIDER_LINE, flags)) {
//		atts.push_back("NO_SLIDER_LINE");
//	}
//
//	std::string value_str;
//
//	if (atts.empty()) {
//	}
//	else {
//		value_str = atts[0];
//		for (int i = 1; i < atts.size(); i++) {
//			value_str += ",";
//			value_str += atts[i];
//		}
//	}
//
//	widget_node.AddNode(xml.CreateNode("flags", value_str));
//	//	widget_node.AddNode(xml.CreateNode("msg", btn->GetMsg()));
//
//	return widget_node;
//	//	return node;
//}
//
//ax::StringPairVector Slider::Component::GetBuilderAttributes()
//{
//	std::shared_ptr<ax::Window::Backbone> bbone = _win->backbone;
//	ax::Slider* sld = static_cast<ax::Slider*>(bbone.get());
//
//	std::vector<std::string> flags;
//	ax::Flag flag = sld->GetFlags();
//
//	if (ax::IsFlag(ax::Slider::Flags::VERTICAL, flag)) {
//		flags.push_back("VERTICAL");
//	}
//	if (ax::IsFlag(ax::Slider::Flags::CLICK_ANYWHERE, flag)) {
//		flags.push_back("CLICK_ANYWHERE");
//	}
//	if (ax::IsFlag(ax::Slider::Flags::RELEASE_ON_LEAVE, flag)) {
//		flags.push_back("RELEASE_ON_LEAVE");
//	}
//	if (ax::IsFlag(ax::Slider::Flags::LEFT_CLICK_ENTER, flag)) {
//		flags.push_back("LEFT_CLICK_ENTER");
//	}
//	if (ax::IsFlag(ax::Slider::Flags::RIGHT_ALIGN, flag)) {
//		flags.push_back("RIGHT_ALIGN");
//	}
//	if (ax::IsFlag(ax::Slider::Flags::MIDDLE_ALIGN, flag)) {
//		flags.push_back("MIDDLE_ALIGN");
//	}
//	if (ax::IsFlag(ax::Slider::Flags::BACK_SLIDER, flag)) {
//		flags.push_back("BACK_SLIDER");
//	}
//	if (ax::IsFlag(ax::Slider::Flags::NO_SLIDER_LINE, flag)) {
//		flags.push_back("NO_SLIDER_LINE");
//	}
//
//	std::string flags_str;
//
//	ax::Print("Slider flag size on get :", flags.size());
//	ax::Print("Flag value :", flag);
//
//	if (!flags.empty()) {
//		flags_str = flags[0];
//
//		for (int i = 1; i < flags.size(); i++) {
//			flags_str += ",";
//			flags_str += flags[i];
//		}
//	}
//
//	return ax::StringPairVector{ { "position", std::to_string(_win->dimension.GetRect().position) },
//		{ "size", std::to_string(_win->dimension.GetSize()) }, { "flags", flags_str } };
//}
//
//std::vector<ax::widget::ParamInfo> ax::Slider::Component::GetBuilderAttributesInfo() const
//{
//	return { ax::widget::ParamInfo(ax::widget::ParamType::POINT, "position"),
//		ax::widget::ParamInfo(ax::widget::ParamType::SIZE, "size"),
//		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "flags") };
//}
//
//void Slider::Component::SetInfo(const ax::StringPairVector& attributes)
//{
//	_info->SetAttributes(attributes);
//}
//
//void Slider::Component::SetBuilderAttributes(const ax::StringPairVector& attributes)
//{
//	ax::Slider* sld = static_cast<ax::Slider*>(GetWindow()->backbone.get());
//
//	for (auto& n : attributes) {
//		if (n.first == "position") {
//			ax::Point pos = ax::Xml::StringToSize(n.second);
//			_win->dimension.SetPosition(pos);
//		}
//		else if (n.first == "size") {
//			ax::Size size = ax::Xml::StringToSize(n.second);
//			_win->dimension.SetSize(size);
//		}
//		else if (n.first == "flags") {
//		}
//	}
//}
//
//void Slider::Component::ReloadInfo()
//{
//	Slider* sld = static_cast<Slider*>(_win->backbone.get());
//	Slider::Info* info = static_cast<Slider::Info*>(_info);
//	
//	if(info->img_path != sld->_btnImg->GetImagePath()) {
//		sld->_btnImg.reset(new ax::Image(info->img_path));
//	}
//
//	ax::Rect rect(sld->GetWindow()->dimension.GetRect());
//
//	if (ax::IsFlag(Flags::VERTICAL, sld->_flags)) {
//		sld->_sliderYPos = (rect.size.x - info->slider_width) * 0.5;
//		sld->_btnYPos = (rect.size.x - info->btn_size.x) * 0.5;
//	}
//	else {
//		sld->_sliderYPos = (rect.size.y - info->slider_width) * 0.5;
//		sld->_btnYPos = (rect.size.y - info->btn_size.y) * 0.5;
//	}
//	
//	_win->Update();
//	//
//
//	//	if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//	//		_sliderYPos = (rect.size.x - _info.slider_width) * 0.5;
//	//		_btnYPos = (rect.size.x - _info.btn_size.x) * 0.5;
//	//
//	//		if (ax::IsFlag(Flags::RIGHT_ALIGN, _flags)) {
//	//			_sliderPosition = rect.size.y - _info.btn_size.y;
//	//		}
//	//	}
//	//	else {
//	//		_sliderYPos = (rect.size.y - _info.slider_width) * 0.5;
//	//		_btnYPos = (rect.size.y - _info.btn_size.y) * 0.5;
//	//
//	//		if (ax::IsFlag(Flags::RIGHT_ALIGN, _flags)) {
//	//			_sliderPosition = rect.size.x - _info.btn_size.x;
//	//		}
//	//	}
//
//	//	switch (btn->_nCurrentImg) {
//	//		case axBTN_NORMAL:
//	//			btn->_currentColor = info->normal;
//	//			break;
//	//		case axBTN_HOVER:
//	//			btn->_currentColor = info->hover;
//	//			break;
//	//		case axBTN_DOWN:
//	//			btn->_currentColor = info->clicking;
//	//			break;
//	//		case axBTN_SELECTED:
//	//			btn->_currentColor = info->selected;
//	//			break;
//	//	}
//
//	//			Knob* knob_obj = static_cast<Knob*>(_win->backbone.get());
//	//		Knob::Info* info = static_cast<Knob::Info*>(_info);
//	//
//	//		if (knob_obj->_knobImg->GetImagePath() != info->img_path) {
//	//			knob_obj->_knobImg.reset(new Image(info->img_path));
//	//		}
//	//
//	//		knob_obj->_currentBgColor = info->bgColorNormal;
//	//		knob_obj->_nCurrentImg = knob_obj->_knobValue * (info->n_knob - 1);
//	//
//	//		_win->Update();
//}
//
//Slider::Builder::Builder()
//{
//}
//
//std::shared_ptr<ax::Window::Backbone> Slider::Builder::Create(
//	const ax::Point& pos, const std::string& file_path)
//{
//	ax::Xml xml(file_path);
//
//	if (!xml.Parse()) {
//		ax::Error("Parsing error.");
//		return nullptr;
//	}
//
//	ax::Xml::Node control = xml.GetNode("Widget");
//	std::string builder_name = control.GetAttribute("builder");
//
//	ax::Size size = ax::Xml::StringToSize(control.GetChildNodeValue("size"));
//
//	std::vector<std::string> flags_strs = ax::Utils::String::Split(control.GetChildNodeValue("flags"), ",");
//
//	ax::Flag flags = 0;
//
//	for (auto& n : flags_strs) {
//		//		ax::Print("OPT : ", n);
//		if (n == "VERTICAL") {
//			flags |= Flags::VERTICAL;
//		}
//		else if (n == "CLICK_ANYWHERE") {
//			flags |= Flags::CLICK_ANYWHERE;
//		}
//		else if (n == "RELEASE_ON_LEAVE") {
//			flags |= Flags::RELEASE_ON_LEAVE;
//		}
//		else if (n == "LEFT_CLICK_ENTER") {
//			flags |= Flags::LEFT_CLICK_ENTER;
//		}
//		else if (n == "RIGHT_ALIGN") {
//			flags |= Flags::RIGHT_ALIGN;
//		}
//		else if (n == "MIDDLE_ALIGN") {
//			flags |= Flags::MIDDLE_ALIGN;
//		}
//		else if (n == "BACK_SLIDER") {
//			flags |= Flags::BACK_SLIDER;
//		}
//		else if (n == "NO_SLIDER_LINE") {
//			flags |= Flags::NO_SLIDER_LINE;
//		}
//	}
//
//	ax::Slider::Info sld_info;
//	ax::Xml::Node info_node = control.GetNode("info");
//	auto param_list = sld_info.GetParamNameList();
//
//	for (auto& n : param_list) {
//		sld_info.SetAttribute(ax::StringPair(n, info_node.GetAttribute(n)));
//	}
//
//	auto sld = ax::shared<ax::Slider>(ax::Rect(pos, size), ax::Slider::Events(), sld_info, flags);
//
//	return sld;
//}
//
//std::shared_ptr<ax::Window::Backbone> Slider::Builder::Create(ax::Xml::Node& control)
//{
//
//	ax::Size pos = ax::Xml::StringToSize(control.GetChildNodeValue("position"));
//	ax::Size size = ax::Xml::StringToSize(control.GetChildNodeValue("size"));
//
//	std::vector<std::string> flags_strs = ax::Utils::String::Split(control.GetChildNodeValue("flags"), ",");
//
//	ax::Flag flags = 0;
//
//	for (auto& n : flags_strs) {
//		//		ax::Print("OPT : ", n);
//		if (n == "VERTICAL") {
//			flags |= Flags::VERTICAL;
//		}
//		else if (n == "CLICK_ANYWHERE") {
//			flags |= Flags::CLICK_ANYWHERE;
//		}
//		else if (n == "RELEASE_ON_LEAVE") {
//			flags |= Flags::RELEASE_ON_LEAVE;
//		}
//		else if (n == "LEFT_CLICK_ENTER") {
//			flags |= Flags::LEFT_CLICK_ENTER;
//		}
//		else if (n == "RIGHT_ALIGN") {
//			flags |= Flags::RIGHT_ALIGN;
//		}
//		else if (n == "MIDDLE_ALIGN") {
//			flags |= Flags::MIDDLE_ALIGN;
//		}
//		else if (n == "BACK_SLIDER") {
//			flags |= Flags::BACK_SLIDER;
//		}
//		else if (n == "NO_SLIDER_LINE") {
//			flags |= Flags::NO_SLIDER_LINE;
//		}
//	}
//
//	ax::Slider::Info sld_info;
//	ax::Xml::Node info_node = control.GetNode("info");
//	auto param_list = sld_info.GetParamNameList();
//
//	for (auto& n : param_list) {
//		sld_info.SetAttribute(ax::StringPair(n, info_node.GetAttribute(n)));
//	}
//
//	auto sld = ax::shared<ax::Slider>(ax::Rect(pos, size), ax::Slider::Events(), sld_info, flags);
//
//	return sld;
//
//	//		std::string builder_name = node.GetAttribute("builder");
//	//
//	//		ax::Print(builder_name);
//	//
//	//		ax::Point pos =
//	// ax::Xml::StringToSize(node.GetChildNodeValue("position"));
//	//		ax::Size size =
//	// ax::Xml::StringToSize(node.GetChildNodeValue("size"));
//	//		std::string img_path = node.GetChildNodeValue("img_path");
//	//		std::string label = node.GetChildNodeValue("label");
//	//
//	//		ax::StringVector flags_strs
//	//		= ax::Utils::String::Split(node.GetChildNodeValue("flags"),
//	//",");
//	//
//	//		ax::Flag flags = 0;
//	//
//	//		for (auto& n : flags_strs) {
//	//
//	//			if (n == "SINGLE_IMG") {
//	//				ax::Print("OPT : ", n);
//	//				flags |= ax::Button::Flags::SINGLE_IMG;
//	//			}
//	//			else if (n == "IMG_RESIZE") {
//	//				flags |= ax::Button::Flags::IMG_RESIZE;
//	//			}
//	//			else if (n == "CAN_SELECTED") {
//	//				flags |= ax::Button::Flags::CAN_SELECTED;
//	//			}
//	//		}
//	//
//	//		std::string msg = node.GetChildNodeValue("msg");
//	//
//	//		ax::Xml::Node info_node = node.GetNode("info");
//	//
//	//		ax::Button::Info btn_info;
//	//		btn_info.normal =
//	// ax::Xml::StringToColor(info_node.GetAttribute("normal"));
//	//		btn_info.hover =
//	// ax::Xml::StringToColor(info_node.GetAttribute("hover"));
//	//		btn_info.clicking
//	//		= ax::Xml::StringToColor(info_node.GetAttribute("clicking"));
//	//		btn_info.selected
//	//		= ax::Xml::StringToColor(info_node.GetAttribute("selected"));
//	//		btn_info.contour
//	//		= ax::Xml::StringToColor(info_node.GetAttribute("contour"));
//	//		btn_info.font_color
//	//		= ax::Xml::StringToColor(info_node.GetAttribute("font_color"));
//	//		btn_info.round_corner_radius
//	//		= std::stoi(info_node.GetAttribute("round_corner_radius"));
//	//
//	//		auto btn = ax::shared<ax::Button>(ax::Rect(pos, size),
//	// ax::Button::Events(),
//	//										  btn_info, img_path, label,
//	// flags,
//	// msg);
//	return nullptr;
//}
//}
//
//ax::Slider::Slider(
//	const ax::Rect& rect, const ax::Slider::Events& events, const ax::Slider::Info& info, ax::Flag flags)
//	// Members.
//	: _events(events),
//	  //	  _info(info),
//	  _currentBgColor(info.bgColorNormal),
//	  _currentSliderColor(info.sliderColorNormal),
//
//	  _nCurrentImg(axBTN_NORMAL),
//	  _delta_click(0),
//	  _sliderValue(0.0),
//	  _flags(flags)
////	  _bg_alpha(1.0)
//{
//
//	win = ax::Window::Create(rect);
//	win->event.OnPaint = ax::WBind<ax::GC>(this, &Slider::OnPaint);
//	win->event.OnMouseLeftDown = ax::WBind<ax::Point>(this, &Slider::OnMouseLeftDown);
//	win->event.OnMouseLeftUp = ax::WBind<ax::Point>(this, &Slider::OnMouseLeftUp);
//
//	win->event.OnMouseLeftDragging = ax::WBind<ax::Point>(this, &Slider::OnMouseLeftDragging);
//	win->event.OnMouseMotion = ax::WBind<ax::Point>(this, &Slider::OnMouseMotion);
//	win->event.OnMouseEnter = ax::WBind<ax::Point>(this, &Slider::OnMouseEnter);
//	win->event.OnMouseLeave = ax::WBind<ax::Point>(this, &Slider::OnMouseLeave);
//
//	win->event.OnResize = ax::WBind<ax::Size>(this, &Slider::OnResize);
//
//	_btnImg = std::shared_ptr<ax::Image>(new ax::Image(info.img_path.c_str())),
//
//	_sliderPosition = 0;
//
//	win->component.Add("Widget", widget::Component::Ptr(new Slider::Component(win, new Slider::Info(info))));
//
//	if (_events.slider_value_change) {
//		win->AddConnection(ax::Slider::Events::VALUE_CHANGE, _events.slider_value_change);
//	}
//
//	if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//		_sliderYPos = (rect.size.x - info.slider_width) * 0.5;
//		_btnYPos = (rect.size.x - info.btn_size.x) * 0.5;
//
//		if (ax::IsFlag(Flags::RIGHT_ALIGN, _flags)) {
//			_sliderPosition = rect.size.y - info.btn_size.y;
//		}
//	}
//	else {
//		_sliderYPos = (rect.size.y - info.slider_width) * 0.5;
//		_btnYPos = (rect.size.y - info.btn_size.y) * 0.5;
//
//		if (ax::IsFlag(Flags::RIGHT_ALIGN, _flags)) {
//			_sliderPosition = rect.size.x - info.btn_size.x;
//		}
//	}
//
//	win->Update();
//}
//
//ax::Window::Backbone* ax::Slider::GetCopy()
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//	ax::Slider* sld = new ax::Slider(win->dimension.GetRect(), _events, *info, _flags);
//	return sld;
//}
//
//void ax::Slider::OnResize(const ax::Size& size)
//{
//
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//
//	if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//		_sliderYPos = (size.x - info->slider_width) * 0.5;
//		_btnYPos = (size.x - info->btn_size.x) * 0.5;
//
//		//		if (ax::IsFlag(axSLIDER_FLAG_RIGHT_ALIGN, _flags)) {
//		//			_sliderPosition = size.y - _info.btn_size.y;
//		//		}
//	}
//	else {
//		_sliderYPos = (size.y - info->slider_width) * 0.5;
//		_btnYPos = (size.y - info->btn_size.y) * 0.5;
//
//		//		if (ax::IsFlag(axSLIDER_FLAG_RIGHT_ALIGN, _flags)) {
//		//			_sliderPosition = size.x - _info.btn_size.x;
//		//		}
//	}
//
//	//	SetValue(_sliderValue);
//}
//
//void ax::Slider::SetValue(const double& value)
//{
//	_sliderValue = value;
//
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//
//	if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//		if (ax::IsFlag(Flags::RIGHT_ALIGN, _flags)) {
//			_sliderPosition = double(win->dimension.GetSize().y - info->btn_size.y) * (_sliderValue);
//		}
//		else {
//			_sliderPosition = double(win->dimension.GetSize().y - info->btn_size.y) * (1.0 - _sliderValue);
//		}
//	}
//	else {
//		_sliderPosition = double(win->dimension.GetSize().x - info->btn_size.x - 2) * (_sliderValue);
//		//	 	_sliderValue = (_sliderPosition - 1) /
//		//	 		double(GetSize().x - _info.btn_size.x - 2);
//	}
//	win->Update();
//}
//
//void ax::Slider::OnMouseLeftDown(const ax::Point& mousePos)
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//
//	ax::Point pos = mousePos - win->dimension.GetAbsoluteRect().position;
//
//	ax::Rect sliderBtnRect;
//	if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//		sliderBtnRect = ax::Rect(ax::Point(_btnYPos, _sliderPosition), info->btn_size);
//	}
//	else {
//		sliderBtnRect = ax::Rect(ax::Point(_sliderPosition, _btnYPos), info->btn_size);
//	}
//
//	if (ax::IsFlag(Flags::CLICK_ANYWHERE, _flags)) {
//		_nCurrentImg = axBTN_DOWN;
//		_currentSliderColor = info->sliderColorClicked;
//
//		if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//			_delta_click = -info->btn_size.y * 0.5;
//		}
//		else {
//			_delta_click = -info->btn_size.x * 0.5;
//		}
//
//		blockSliderPosition(pos);
//		win->event.GrabMouse();
//
//		win->PushEvent(ax::Slider::Events::VALUE_CHANGE, new ax::Slider::Msg(this, _sliderValue));
//		win->Update();
//	}
//	// Click on boutton to move.
//	else {
//
//		//		std::cout << "ELSE" << std::endl;
//		if (sliderBtnRect.IsPointInside(pos) && _nCurrentImg != axBTN_DOWN) {
//			//			std::cout << "ELSE IN" << std::endl;
//			_nCurrentImg = axBTN_DOWN;
//			_currentSliderColor = info->sliderColorClicked;
//
//			if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//				_delta_click = sliderBtnRect.position.y - pos.y;
//			}
//			else {
//				_delta_click = sliderBtnRect.position.x - pos.x;
//			}
//
//			//			std::cout << "MOUSE GRAB before" << std::endl;
//			win->event.GrabMouse();
//
//			//			std::cout << "MOUSE GRAB" << std::endl;
//
//			// Send value change event.
//			//			if (_events.slider_value_change)
//			//			{
//			//				_events.slider_value_change(axSliderMsg(_sliderValue));
//			//			}
//			win->PushEvent(ax::Slider::Events::VALUE_CHANGE, new ax::Slider::Msg(this, _sliderValue));
//			win->Update();
//		}
//	}
//}
//
//void ax::Slider::OnMouseLeftUp(const ax::Point& p)
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//
//	ax::Point pos = p - win->dimension.GetAbsoluteRect().position;
//
//	if (win->event.IsGrabbed()) {
//		win->event.UnGrabMouse();
//		blockSliderPosition(pos);
//		_nCurrentImg = axBTN_NORMAL;
//		_currentSliderColor = info->sliderColorNormal;
//
//		win->Update();
//	}
//}
//
//void ax::Slider::OnMouseLeftDragging(const ax::Point& p)
//{
//	//	std::cout << "Drag" << std::endl;
//	// DSTREAM << "DRAG" << endl;
//	ax::Point pos = p - win->dimension.GetAbsoluteRect().position;
//
//	blockSliderPosition(pos);
//
//	//	if (_events.slider_value_change)
//	//	{
//	//		_events.slider_value_change(axSliderMsg(_sliderValue));
//	//	}
//
//	win->PushEvent(ax::Slider::Events::VALUE_CHANGE, new ax::Slider::Msg(this, _sliderValue));
//
//	win->Update();
//}
//
//void ax::Slider::blockSliderPosition(const ax::Point& pos)
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//
//	if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//		int pos_y = pos.y + _delta_click;
//
//		pos_y = ax::Utils::Clamp<double>(pos_y, 1, win->dimension.GetSize().y - info->btn_size.y - 1);
//		// axCLIP(pos_y, 1, GetSize().y - _info.btn_size.y - 1);
//
//		_sliderPosition = pos_y;
//	}
//	else {
//		int pos_x = pos.x + _delta_click;
//
//		//		axCLIP(pos_x, 1, GetSize().x - _info.btn_size.x - 1);
//		pos_x = ax::Utils::Clamp<double>(pos_x, 1, win->dimension.GetSize().x - info->btn_size.x - 1);
//
//		_sliderPosition = pos_x;
//	}
//
//	updateSliderValue();
//}
//
//void ax::Slider::updateSliderValue()
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//
//	if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//		_sliderValue = (_sliderPosition - 1) / double(win->dimension.GetSize().y - info->btn_size.y - 2);
//	}
//	else {
//		_sliderValue = (_sliderPosition - 1) / double(win->dimension.GetSize().x - info->btn_size.x - 2);
//	}
//}
//
//void ax::Slider::OnMouseMotion(const ax::Point& p)
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//	ax::Point pos = p - win->dimension.GetAbsoluteRect().position;
//
//	ax::Rect sliderBtnRect;
//	if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//		sliderBtnRect = ax::Rect(ax::Point(_btnYPos, _sliderPosition), info->btn_size);
//	}
//	else {
//		sliderBtnRect = ax::Rect(ax::Point(_sliderPosition, _btnYPos), info->btn_size);
//	}
//
//	if (sliderBtnRect.IsPointInside(pos)) {
//		if (_nCurrentImg != axBTN_HOVER) {
//			_nCurrentImg = axBTN_HOVER;
//			win->Update();
//		}
//	}
//	else // Mouse is not hover slider button.
//	{
//		if (_nCurrentImg != axBTN_NORMAL) {
//			_nCurrentImg = axBTN_NORMAL;
//			win->Update();
//		}
//	}
//}
//
//void ax::Slider::OnMouseEnter(const ax::Point& p)
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//
//	ax::Point pos = p - win->dimension.GetAbsoluteRect().position;
//
//	if (ax::IsFlag(Flags::LEFT_CLICK_ENTER, _flags)) {
//		// if (GetParent()->LeftIsDown())
//		//{
//		ax::Rect sliderBtnRect(ax::Point(_sliderPosition, _btnYPos), info->btn_size);
//
//		_nCurrentImg = axBTN_DOWN;
//		_currentSliderColor = info->sliderColorClicked;
//		if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//			_delta_click = sliderBtnRect.position.y - pos.y;
//		}
//		else {
//			_delta_click = sliderBtnRect.position.x - pos.x;
//		}
//		win->event.GrabMouse();
//		// SendPaintEvent();
//		win->Update();
//		//}
//	}
//}
//
//void ax::Slider::OnMouseLeave(const ax::Point& p)
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//	ax::Point pos = p - win->dimension.GetAbsoluteRect().position;
//
//	if (ax::IsFlag(Flags::RELEASE_ON_LEAVE, _flags)) {
//		if (win->event.IsGrabbed()) {
//			win->event.UnGrabMouse();
//			blockSliderPosition(pos);
//			_nCurrentImg = axBTN_NORMAL;
//			_currentSliderColor = info->sliderColorNormal;
//			// SendPaintEvent();
//			win->Update();
//		}
//	}
//}
//
//void ax::Slider::DrawLineBehindSlider_Vertical(ax::GC* gc, const ax::Rect& rect0)
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//
//	int half_btn_size = info->btn_size.y * 0.5;
//
//	ax::Rect slider_rect;
//	if (ax::IsFlag(Flags::RIGHT_ALIGN, _flags)) {
//		// slider_rect = ax::Rect(_sliderYPos, _sliderPosition + half_btn_size,
//		// 					 12,// _info.slider_width,
//		// 					 GetSize().y - _sliderPosition - half_btn_size);
//
//		slider_rect = ax::Rect(_sliderYPos, _sliderPosition + half_btn_size, info->slider_width,
//			win->dimension.GetSize().y - _sliderPosition - half_btn_size);
//	}
//	else {
//		slider_rect = ax::Rect(_sliderYPos, 0, info->slider_width, _sliderPosition + half_btn_size);
//	}
//
//	gc->SetColor(_currentSliderColor);
//	gc->DrawRectangle(slider_rect);
//
//	gc->SetColor(info->sliderContourColor);
//	// gc->DrawRectangleContour(slider_rect);
//}
//
//void ax::Slider::DrawVerticalSlider(ax::GC* gc, const ax::Rect& rect0)
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//	//	ax::Size size(rect0.size);
//	//	int half_btn_size = _info.btn_size.y * 0.5;
//
//	if (ax::IsFlag(Flags::BACK_SLIDER, _flags)) {
//		// Back slider.
//		ax::Rect back_slider(_sliderYPos, 0, info->slider_width, rect0.size.y);
//
//		gc->SetColor(info->backSliderColor);
//		gc->DrawRectangle(back_slider);
//
//		gc->SetColor(info->backSliderContourColor);
//		gc->DrawRectangleContour(back_slider);
//	}
//
//	// Draw line behind the slider.
//	if (!ax::IsFlag(Flags::NO_SLIDER_LINE, _flags)) {
//		DrawLineBehindSlider_Vertical(gc, rect0);
//	}
//
//	gc->SetColor(info->contourColor);
//	gc->DrawRectangleContour(rect0);
//
//	if (_btnImg->IsImageReady()) {
//		gc->DrawPartOfImage(_btnImg.get(), ax::Point(0, _nCurrentImg * info->btn_size.y), info->btn_size,
//			ax::Point(_btnYPos, _sliderPosition));
//	}
//}
//
//void ax::Slider::OnPaint(ax::GC gc)
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
//
//	ax::Size size = win->dimension.GetSize();
//	//	ax::Rect rect0(0, 0, size.x, size.y);
//
//	int radius = info->contour_round_radius;
//	ax::Rect rect0(win->dimension.GetDrawingRect());
//
//	if (radius > 1) {
//		gc.SetColor(_currentBgColor);
//		gc.DrawRoundedRectangle(rect0, radius);
//	}
//	else {
//		gc.SetColor(_currentBgColor);
//		gc.DrawRectangle(rect0);
//	}
//
//	// VERTICAL SLIDER.
//	if (ax::IsFlag(Flags::VERTICAL, _flags)) {
//		DrawVerticalSlider(&gc, rect0);
//	}
//
//	// HORIZONTAL SLIDER.
//	else {
//		if (ax::IsFlag(Flags::BACK_SLIDER, _flags)) {
//			// Back slider.
//			ax::Rect back_slider(0, _sliderYPos, size.x, info->slider_width);
//
//			gc.SetColor(info->backSliderColor);
//			gc.DrawRectangle(back_slider);
//
//			gc.SetColor(info->backSliderContourColor);
//			gc.DrawRectangleContour(back_slider);
//		}
//
//		int half_btn_size = info->btn_size.x * 0.5;
//
//		if (!ax::IsFlag(Flags::NO_SLIDER_LINE, _flags)) {
//			ax::Rect slider_rect(0, _sliderYPos, _sliderPosition + half_btn_size, info->slider_width);
//
//			if (ax::IsFlag(Flags::RIGHT_ALIGN, _flags)) {
//				slider_rect = ax::Rect(_sliderPosition, _sliderYPos,
//					win->dimension.GetSize().x - _sliderPosition + half_btn_size, info->slider_width);
//			}
//			else {
//				slider_rect = ax::Rect(0, _sliderYPos, _sliderPosition + half_btn_size, info->slider_width);
//			}
//
//			if (radius > 1) {
//				gc.SetColor(_currentSliderColor);
//				gc.DrawRoundedRectangle(slider_rect, radius);
//
//				gc.SetColor(info->sliderContourColor);
//				gc.DrawRoundedRectangleContour(slider_rect, radius);
//			}
//			else {
//				gc.SetColor(_currentSliderColor);
//				gc.DrawRectangle(slider_rect);
//
//				gc.SetColor(info->sliderContourColor);
//				gc.DrawRectangleContour(slider_rect);
//			}
//		}
//
//		if (radius > 1) {
//			gc.SetColor(info->contourColor);
//			gc.DrawRoundedRectangleContour(rect0, radius);
//		}
//		else {
//			gc.SetColor(info->contourColor);
//			gc.DrawRectangleContour(rect0);
//		}
//
//		if (_btnImg->IsImageReady()) {
//			gc.DrawPartOfImage(_btnImg.get(), ax::Point(0, _nCurrentImg * info->btn_size.y), info->btn_size,
//				ax::Point(_sliderPosition, _btnYPos));
//		}
//	}
//}