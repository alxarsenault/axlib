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
#include "Knob.hpp"
#include "Label.hpp"
#include "Panel.hpp"
#include "Toggle.hpp"
#include "WidgetLoader.hpp"

namespace ax {

/*
 * ax::Button::Info.
 */
Panel::Info::Info()
	: widget::Info() // Heritage.
	, background(1.0) // Members.
	, contour(1.0)
	, round_corner_radius(0)
{
}

Panel::Info::Info(const std::string& path)
	: widget::Info(path) // Heritage.
{
}

Panel::Info::Info(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	SetAttributes(attributes);
}

std::vector<std::string> Panel::Info::GetParamNameList() const
{
	return std::vector<std::string>{ "background", "contour", "round_corner_radius" };
}

std::string Panel::Info::GetAttributeValue(const std::string& name)
{
	if (name == "background") {
		return background.ToString();
	}
	else if (name == "contour") {
		return contour.ToString();
	}
	else if (name == "round_corner_radius") {
		return std::to_string(round_corner_radius);
	}

	return "";
}

void Panel::Info::SetAttribute(const std::pair<std::string, std::string>& attribute)
{
	if (attribute.first == "background") {
		background = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "contour") {
		contour = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "round_corner_radius") {
		round_corner_radius = std::stoi(attribute.second);
	}
}

Panel::Component::Component(ax::Window* win, Info* info)
	: ax::widget::Component(win, info)
{
}

std::vector<std::pair<std::string, std::string>> Panel::Component::GetBuilderAttributes()
{
	ax::Window* win = GetWindow();
	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
	ax::Panel* panel = static_cast<ax::Panel*>(bbone.get());

	std::vector<std::pair<std::string, std::string>> atts;

	ax::Rect rect = win->dimension.GetRect();
	atts.push_back(std::pair<std::string, std::string>("position", std::to_string(rect.position)));
	atts.push_back(std::pair<std::string, std::string>("size", std::to_string(rect.size)));
	atts.push_back(std::pair<std::string, std::string>("name", panel->GetName()));
	atts.push_back(std::pair<std::string, std::string>("bg_img", panel->GetBackgroundImagePath()));

	return atts;
}

ax::Xml::Node Panel::Component::Save(ax::Xml& xml, ax::Xml::Node& node)
{
	ax::Window* win = GetWindow();
	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
	ax::Panel* btn = static_cast<ax::Panel*>(bbone.get());

	ax::Panel::Component* widget_comp
		= static_cast<ax::Panel::Component*>(win->component.Get("Widget").get());

	ax::Panel::Info* info = static_cast<ax::Panel::Info*>(widget_comp->GetInfo());

	ax::Xml::Node widget_node = xml.CreateNode("Widget");
	node.AddNode(widget_node);
	widget_node.AddAttribute("builder", "Panel");
	widget_node.AddAttribute("name", btn->GetName());
	ax::Rect rect = win->dimension.GetRect();

	widget_node.AddNode(xml.CreateNode("position", std::to_string(rect.position)));

	widget_node.AddNode(xml.CreateNode("size", std::to_string(rect.size)));
	widget_node.AddNode(xml.CreateNode("bg_img", btn->GetBackgroundImagePath()));

	ax::Xml::Node info_node = xml.CreateNode("info");
	widget_node.AddNode(info_node);

	info_node.AddAttribute("background", info->background.ToString());
	info_node.AddAttribute("contour", info->contour.ToString());
	info_node.AddAttribute("round_corner_radius", std::to_string(info->round_corner_radius));

	ax::util::Flag flags = btn->GetFlags();
	widget_node.AddNode(xml.CreateNode("flags", std::to_string(flags)));

	// Saving children.
	std::vector<std::shared_ptr<ax::Window>>& children = GetWindow()->node.GetChildren();

	if (children.size()) {
		ax::Xml::Node children_node = xml.CreateNode("Children");
		widget_node.AddNode(children_node);

		for (auto& n : children) {
			if (_save_child_callback) {
				_save_child_callback(xml, children_node, n.get());
			}

			//			ax::widget::Component::Ptr opt
			//				= n->component.Get<ax::widget::Component>("Widget");
			//
			//			if (opt) {
			//
			//				// Save ax::Object.
			//				ax::Xml::Node node = opt->Save(xml, children_node);
			//
			//				//				if(n->component.Has("pyo")) {
			//				//					ax::Print("HAS PYO");
			//				//					pyo::Component::Ptr comp =
			//				// n->component.Get<pyo::Component>("pyo");
			//				//					std::string fct_name =
			//				// comp->GetFunctionName();
			//				//					ax::Xml::Node pyo_node =
			//				// xml.CreateNode("pyo",
			//				// fct_name);
			//				//					node.AddNode(pyo_node);
			//				//				}
			//			}
		}
	}

	return widget_node;
}

void Panel::Component::SetBuilderAttributes(
	const std::vector<std::pair<std::string, std::string>>& attributes)
{
	for (auto& n : attributes) {
		if (n.first == "position") {
			ax::Point pos(n.second);
			GetWindow()->dimension.SetPosition(pos);
		}
		else if (n.first == "size") {
			ax::Size size(n.second);
			GetWindow()->dimension.SetSize(size);
		}
		else if (n.first == "bg_img") {
			// ax::Print("ax::Panel SetBuilderAttributes bg_img -> Not implemented yet.");

			Panel* panel = static_cast<Panel*>(_win->backbone.get());

			if (panel->_bg_img) {
				if (panel->_bg_img->GetImagePath() != n.second) {
					panel->_bg_img.reset(new ax::Image(n.second));
				}
			}
			else {
				panel->_bg_img.reset(new ax::Image(n.second));
			}
		}
	}

	GetWindow()->Update();
}

std::vector<ax::widget::ParamInfo> Panel::Component::GetBuilderAttributesInfo() const
{
	return { ax::widget::ParamInfo(ax::widget::ParamType::POINT, "position"),
		ax::widget::ParamInfo(ax::widget::ParamType::SIZE, "size"),
		ax::widget::ParamInfo(ax::widget::ParamType::FILEPATH, "bg_img") };
}

void Panel::Component::ReloadInfo()
{
	_win->Update();
}

void Panel::Component::SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	_info->SetAttributes(attributes);
}

Panel::Builder::Builder()
{
}

std::shared_ptr<ax::Window::Backbone> Panel::Builder::Create(
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

	std::string bg_img_path = control.GetChildNodeValue("bg_img");

	std::vector<std::string> flags_strs = ax::util::String::Split(control.GetChildNodeValue("flags"), ",");

	ax::util::Flag flags = 0;

	ax::Xml::Node info_node = control.GetNode("info");

	ax::Panel::Info panel_info;
	panel_info.background = ax::Color::FromString(info_node.GetAttribute("background"));
	panel_info.contour = ax::Color::FromString(info_node.GetAttribute("contour"));
	panel_info.round_corner_radius = std::stoi(info_node.GetAttribute("round_corner_radius"));

	auto panel = ax::shared<ax::Panel>(ax::Rect(pos, size), panel_info, bg_img_path, obj_name, flags);

	CreateChildren(control, panel.get());

	return panel;
}

std::shared_ptr<ax::Window::Backbone> Panel::Builder::Create(ax::Xml::Node& node)
{
	std::string builder_name = node.GetAttribute("builder");
	//	ax::Print("Attribute name");
	std::string name = node.GetAttribute("name");
	//	ax::Print(builder_name, name);

	ax::Point pos(node.GetChildNodeValue("position"));
	ax::Size size(node.GetChildNodeValue("size"));
	std::string bg_img_path = node.GetChildNodeValue("bg_img");

	std::vector<std::string> flags_strs = ax::util::String::Split(node.GetChildNodeValue("flags"), ",");

	ax::util::Flag flags = 0;

	ax::Xml::Node info_node = node.GetNode("info");
	ax::Panel::Info btn_info;
	btn_info.background = ax::Color::FromString(info_node.GetAttribute("background"));
	btn_info.contour = ax::Color::FromString(info_node.GetAttribute("contour"));
	btn_info.round_corner_radius = std::stoi(info_node.GetAttribute("round_corner_radius"));

	auto panel = ax::shared<ax::Panel>(ax::Rect(pos, size), btn_info, bg_img_path, name, flags);

	CreateChildren(node, panel.get());

	return panel;
}

void Panel::Builder::CreateChildren(ax::Xml::Node& node, ax::Panel* panel)
{
	ax::widget::Loader* loader = ax::widget::Loader::GetInstance();

	ax::Xml::Node children = node.GetNode("Children");

	if (children.IsValid()) {
		ax::Xml::Node child = children.GetNode("Widget");

		while (child.IsValid()) {

			std::string child_node_name = child.GetName();

			if (child_node_name == "Widget") {
				std::string buider_name = child.GetAttribute("builder");
				//				std::string name = child.GetAttribute("name");

				ax::widget::Builder* builder = loader->GetBuilder(buider_name);
				if (builder == nullptr) {
					ax::console::Error("Panel builder", buider_name, "doesn't exist.");
					child = child.GetNextSibling();
					continue;
				}

				auto obj = builder->Create(child);

				panel->GetWindow()->node.Add(obj);

				if (_create_callback) {
					_create_callback(obj->GetWindow(), child);
				}
			}
			child = child.GetNextSibling();
		}
	}
}

/*
 * ax::Panel.
 */
Panel::Panel(const Rect& rect, const Panel::Info& info, const std::string& bg_img, const std::string& name,
	ax::util::Flag flags)
	: _flags(flags)
	, _bg_img_path(bg_img)
	, _name(name)
{
	win = Window::Create(rect);

	// Builtin event connection.
	win->event.OnPaint = WBind<GC>(this, &Panel::OnPaint);

	win->component.Add("Widget", widget::Component::Ptr(new Panel::Component(win, new Panel::Info(info))));

	win->property.AddProperty("Editable");
	win->property.AddProperty("AcceptWidget");

	if (!_bg_img_path.empty()) {
		_bg_img = ax::shared<ax::Image>(_bg_img_path);
	}
	else {
		_bg_img = nullptr;
	}
	//	win->property.AddProperty("BlockDrawing");
}

ax::Window::Backbone* Panel::GetCopy()
{
	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
	ax::Panel::Info* info = static_cast<ax::Panel::Info*>(widget->GetInfo());
	ax::Panel* panel = new ax::Panel(win->dimension.GetRect(), *info, _bg_img_path, _name, _flags);

	std::vector<std::shared_ptr<ax::Window>>& children = win->node.GetChildren();

	if (children.size()) {
		for (auto& n : children) {
			std::shared_ptr<ax::Window::Backbone> child_bck_bone(n->backbone->GetCopy());
			panel->win->node.Add(child_bck_bone);
		}
	}

	return panel;
}

void Panel::OnPaint(GC gc)
{
	Rect rect(win->dimension.GetDrawingRect());

	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	Panel::Info* info = static_cast<Panel::Info*>(widget->GetInfo());

	const int radius = info->round_corner_radius;

	if (radius > 0.0) {
		gc.SetColor(info->background);
		gc.DrawRoundedRectangle(rect, radius);

		gc.SetColor(info->contour);
		gc.DrawRoundedRectangleContour(rect, radius);
	}
	else {
		gc.SetColor(info->background);
		gc.DrawRectangle(rect);

		if (_bg_img.get() != nullptr) {
			if (_bg_img->IsImageReady()) {
				gc.DrawImage(_bg_img.get(), ax::Point(0, 0));
			}
		}

		gc.SetColor(info->contour);
		gc.DrawRectangleContour(rect);
	}
}
}
