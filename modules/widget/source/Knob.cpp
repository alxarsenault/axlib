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
//#include "Knob.hpp"
//
//namespace ax {
///*
// * axKnob::Msg.
// */
//Knob::Msg::Msg(const double& value, const std::string& msg)
//	: _value(value)
//	, _msg(msg)
//{
//}
//
//double Knob::Msg::GetValue() const
//{
//	return _value;
//}
//
//std::string Knob::Msg::GetMsg() const
//{
//	return _msg;
//}
//
//Event::Msg* Knob::Msg::GetCopy()
//{
//	return new Msg(*this);
//}
//
///*
// * axKnob::Info.
// */
//Knob::Info::Info()
//	: bgColorNormal(Color(0.0, 0.0))
//	, bgColorHover(Color(0.0, 0.0))
//	, bgColorClicked(Color(0.0, 0.0))
//	, knob_size(Size(50, 50))
//	, n_knob(128)
//{
//}
//
//std::vector<std::string> Knob::Info::GetParamNameList() const
//{
//	return std::vector<std::string>{ "knob_size", "n_knob", "bgColorNormal", "bgColorHover", "bgColorClicked" };
//}
//
//std::string Knob::Info::GetAttributeValue(const std::string& name)
//{
//	if (name == "knob_size") {
//		return std::to_string(knob_size.x) + ", " + std::to_string(knob_size.y);
//	}
//	else if (name == "n_knob") {
//		return std::to_string(n_knob);
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
//	else if (name == "img_path") {
//		return img_path;
//	}
//	else if (name == "selected_img_path") {
//		return selected_img_path;
//	}
//
//	return "";
//}
//
//void Knob::Info::SetAttribute(const StringPair& attribute)
//{
//	if (attribute.first == "knob_size") {
//		knob_size = ax::Xml::StringToSize(attribute.second);
//	}
//	else if (attribute.first == "n_knob") {
//		n_knob = std::stoi(attribute.second);
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
//	else if (attribute.first == "img_path") {
//		img_path = attribute.second;
//	}
//	else if (attribute.first == "selected_img_path") {
//		selected_img_path = attribute.second;
//	}
//}
//
//Knob::Component::Component(Window* win, Info* info)
//	: widget::Component(win, info)
//{
//}
//
//ax::Xml::Node Knob::Component::Save(Xml& xml, Xml::Node& node)
//{
//	ax::Window* win = GetWindow();
//	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
//	ax::Knob* knob = static_cast<ax::Knob*>(bbone.get());
//
//	ax::Knob::Component* widget_comp = static_cast<ax::Knob::Component*>(win->component.Get("Widget").get());
//
//	ax::Knob::Info* info = static_cast<ax::Knob::Info*>(widget_comp->GetInfo());
//
//	ax::Xml::Node widget_node = xml.CreateNode("Widget");
//	node.AddNode(widget_node);
//	widget_node.AddAttribute("builder", "Knob");
//
//	ax::Rect rect = win->dimension.GetRect();
//
//	widget_node.AddNode(xml.CreateNode("position", std::to_string(rect.position)));
//	widget_node.AddNode(xml.CreateNode("size", std::to_string(rect.size)));
//
//	ax::Xml::Node info_node = xml.CreateNode("info");
//	widget_node.AddNode(info_node);
//	info_node.AddAttribute("bgColorNormal", info->bgColorNormal.ToString());
//	info_node.AddAttribute("bgColorHover", info->bgColorHover.ToString());
//	info_node.AddAttribute("bgColorClicked", info->bgColorClicked.ToString());
//	info_node.AddAttribute("img_path", info->img_path);
//	info_node.AddAttribute("selected_img_path", info->selected_img_path);
//	info_node.AddAttribute(
//		"knob_size", std::to_string(info->knob_size.x) + ", " + std::to_string(info->knob_size.y));
//	info_node.AddAttribute("n_knob", std::to_string(info->n_knob));
//
//	widget_node.AddNode(xml.CreateNode("msg", knob->GetMsg()));
//	widget_node.AddNode(xml.CreateNode("flags", std::to_string(knob->GetFlags())));
//
//	return widget_node;
//}
//
//ax::StringPairVector Knob::Component::GetBuilderAttributes()
//{
//	ax::Window* win = GetWindow();
//	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
//	ax::Knob* knob = static_cast<ax::Knob*>(bbone.get());
//
//	ax::StringPairVector atts;
//	ax::Point position = win->dimension.GetRect().position;
//
//	std::string pos_str(std::to_string(position.x) + ", " + std::to_string(position.y));
//	atts.push_back(ax::StringPair("position", pos_str));
//
//	ax::Size size = win->dimension.GetSize();
//	std::string size_str(std::to_string(size.x) + ", " + std::to_string(size.y));
//	atts.push_back(ax::StringPair("size", size_str));
//
//	atts.push_back(ax::StringPair("flags", std::to_string(knob->GetFlags())));
//	atts.push_back(ax::StringPair("msg", knob->GetMsg()));
//
//	return atts;
//}
//
//std::vector<ax::widget::ParamInfo> Knob::Component::GetBuilderAttributesInfo() const
//{
//	return { ax::widget::ParamInfo(ax::widget::ParamType::POINT, "position"),
//		ax::widget::ParamInfo(ax::widget::ParamType::SIZE, "size"),
//		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "flags"),
//		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "msg") };
//}
//
//void Knob::Component::SetBuilderAttributes(const ax::StringPairVector& attributes)
//{
//	ax::Knob* knob = static_cast<ax::Knob*>(GetWindow()->backbone.get());
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
//		else if (n.first == "msg") {
//			knob->SetMsg(n.second);
//		}
//	}
//}
//
//void Knob::Component::SetInfo(const ax::StringPairVector& attributes)
//{
//	_info->SetAttributes(attributes);
//}
//
//void Knob::Component::ReloadInfo()
//{
//	Knob* knob_obj = static_cast<Knob*>(_win->backbone.get());
//	Knob::Info* info = static_cast<Knob::Info*>(_info);
//
//	if (knob_obj->_knobImg->GetImagePath() != info->img_path) {
//		knob_obj->_knobImg.reset(new Image(info->img_path));
//	}
//
//	knob_obj->_currentBgColor = info->bgColorNormal;
//	knob_obj->_nCurrentImg = knob_obj->_knobValue * (info->n_knob - 1);
//
//	_win->Update();
//}
//
//Knob::Builder::Builder()
//{
//}
//
//std::shared_ptr<Window::Backbone> Knob::Builder::Create(const Point& pos, const std::string& file_path)
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
//	std::string obj_name = control.GetAttribute("name");
//
//	//	ax::Print(builder_name, obj_name);
//
//	ax::Size size = ax::Xml::StringToSize(control.GetChildNodeValue("size"));
//	ax::Flag flags = std::stoi(control.GetChildNodeValue("flags"));
//	std::string msg = control.GetChildNodeValue("msg");
//
//	ax::Xml::Node info_node = control.GetNode("info");
//
//	ax::Knob::Info k_info;
//	k_info.bgColorNormal = ax::Xml::StringToColor(info_node.GetAttribute("bgColorNormal"));
//	k_info.bgColorHover = ax::Xml::StringToColor(info_node.GetAttribute("bgColorHover"));
//	k_info.bgColorClicked = ax::Xml::StringToColor(info_node.GetAttribute("bgColorClicked"));
//
//	k_info.img_path = info_node.GetAttribute("img_path");
//	k_info.selected_img_path = info_node.GetAttribute("selected_img_path");
//	k_info.knob_size = ax::Xml::StringToSize(info_node.GetAttribute("knob_size"));
//	k_info.n_knob = std::stoi(info_node.GetAttribute("n_knob"));
//
//	auto knob = ax::shared<ax::Knob>(ax::Rect(pos, size), ax::Knob::Events(), k_info, flags, 0.0, msg);
//
//	return knob;
//}
//
//std::shared_ptr<Window::Backbone> Knob::Builder::Create(Xml::Node& node)
//{
//	ax::Xml::Node control(node);
//	std::string builder_name = control.GetAttribute("builder");
//
//	//	ax::Print(builder_name);
//
//	ax::Size pos = ax::Xml::StringToSize(control.GetChildNodeValue("position"));
//	ax::Size size = ax::Xml::StringToSize(control.GetChildNodeValue("size"));
//
//	ax::Flag flags = std::stoi(control.GetChildNodeValue("flags"));
//	std::string msg = control.GetChildNodeValue("msg");
//
//	ax::Xml::Node info_node = control.GetNode("info");
//
//	ax::Knob::Info k_info;
//	k_info.bgColorNormal = ax::Xml::StringToColor(info_node.GetAttribute("bgColorNormal"));
//	k_info.bgColorHover = ax::Xml::StringToColor(info_node.GetAttribute("bgColorHover"));
//	k_info.bgColorClicked = ax::Xml::StringToColor(info_node.GetAttribute("bgColorClicked"));
//
//	k_info.img_path = info_node.GetAttribute("img_path");
//	k_info.selected_img_path = info_node.GetAttribute("selected_img_path");
//	k_info.knob_size = ax::Xml::StringToSize(info_node.GetAttribute("knob_size"));
//	k_info.n_knob = std::stoi(info_node.GetAttribute("n_knob"));
//
//	auto knob = ax::shared<ax::Knob>(ax::Rect(pos, size), ax::Knob::Events(), k_info, flags, 0.0, msg);
//
//	return knob;
//}
//
///*
// * axKnob.
// */
//Knob::Knob(const Rect& rect, const Knob::Events& events, const Knob::Info& info, Flag flags, double value,
//	const std::string& msg)
//	: _events(events)
//	, _msg(msg)
//	, _flags(flags)
//	, _range(0.0, 1.0)
//	, _knobValue(value)
//	, _zeroToOneValue(value)
//{
//	win = Window::Create(rect);
//
//	win->event.OnPaint = WBind<GC>(this, &Knob::OnPaint);
//	win->event.OnMouseLeftDown = WBind<Point>(this, &Knob::OnMouseLeftDown);
//	win->event.OnMouseLeftUp = WBind<Point>(this, &Knob::OnMouseLeftUp);
//	win->event.OnMouseLeftDragging = WBind<Point>(this, &Knob::OnMouseLeftDragging);
//
//	win->component.Add("Widget", widget::Component::Ptr(new Knob::Component(win, new Knob::Info(info))));
//
//	// Check for share Image first.
//	if (info.img) {
//		_knobImg = info.img;
//		// If no shared image then look for image path.
//	}
//	else if (!info.img_path.empty()) {
//		_knobImg = std::shared_ptr<Image>(new Image(info.img_path));
//	}
//
//	_currentBgColor = info.bgColorNormal;
//
//	_nCurrentImg = _knobValue * (info.n_knob - 1);
//
//	if (_events.value_change) {
//		win->AddConnection(0, _events.value_change);
//	}
//
//	SetValue(_range.GetValueFromZeroToOne(_knobValue), false);
//}
//
//ax::Window::Backbone* Knob::GetCopy()
//{
//	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
//	ax::Knob::Info* info = static_cast<ax::Knob::Info*>(widget->GetInfo());
//	ax::Knob* knob = new ax::Knob(win->dimension.GetRect(), _events, *info, _flags, _knobValue, _msg);
//	return knob;
//}
//
//void Knob::OnMouseLeftDown(const Point& pos)
//{
//	_clickPosY = (pos - win->dimension.GetAbsoluteRect().position).y;
//
//	win->event.GrabMouse();
//	win->Update();
//
//	//    GetApp()->HideMouse();
//
//	win->PushEvent(0, new Msg(_knobValue, _msg));
//}
//
//void Knob::OnMouseLeftUp(const Point& pos)
//{
//	if (win->event.IsGrabbed()) {
//		//        GetApp()->ShowMouse();
//		win->event.UnGrabMouse();
//		win->Update();
//
//		win->PushEvent(0, new Msg(_knobValue, _msg));
//	}
//}
//
//void Knob::OnMouseLeftDragging(const Point& position)
//{
//	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
//
//	Knob::Info& info = *static_cast<Knob::Info*>(widget->GetInfo());
//
//	int cur_img = _nCurrentImg;
//	Point pt(win->dimension.GetAbsoluteRect().position);
//	Point p = position - pt;
//
//	double delta = p.y - _clickPosY;
//
//	_clickPosY = p.y;
//
//	double v = -delta / 100.0;
//	_zeroToOneValue += v;
//
//	_zeroToOneValue = Utils::Clamp<double>(_zeroToOneValue, 0.0, 1.0);
//	_knobValue = _range.GetValueFromZeroToOne(_zeroToOneValue);
//
//	_nCurrentImg = _knobValue * (info.n_knob - 1);
//
//	if (_nCurrentImg != cur_img) {
//		win->Update();
//	}
//
//	win->PushEvent(0, new Msg(_knobValue, _msg));
//}
//
//void Knob::SetValue(const double& value, bool callValueChangeEvent)
//{
//	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
//
//	Knob::Info& info = *static_cast<Knob::Info*>(widget->GetInfo());
//
//	int cur_img = _nCurrentImg;
//	_zeroToOneValue = Utils::Clamp<double>(value, 0.0, 1.0);
//	_knobValue = _zeroToOneValue;
//	_nCurrentImg = _knobValue * (info.n_knob - 1);
//
//	if (_nCurrentImg != cur_img) {
//		win->Update();
//	}
//
//	if (callValueChangeEvent) {
//		win->PushEvent(0, new Msg(_knobValue, _msg));
//	}
//}
//
//void Knob::OnPaint(GC gc)
//{
//	Rect rect(Point(0, 0), win->dimension.GetSize());
//
//	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
//
//	Knob::Info& info = *static_cast<Knob::Info*>(widget->GetInfo());
//
//	gc.SetColor(_currentBgColor);
//	gc.DrawRectangle(rect);
//
//	if (_knobImg) {
//		gc.DrawPartOfImageResize(_knobImg.get(), Point(_nCurrentImg * info.knob_size.x, 0), info.knob_size,
//			ax::Rect(ax::Point(0, 0), rect.size));
//	}
//}
//}