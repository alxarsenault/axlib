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

#include "Label.hpp"

namespace ax {
/*
 * axLabel::Info.
 */
Label::Info::Info()
{
}

Label::Info::Info(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	SetAttributes(attributes);
}

std::vector<std::string> Label::Info::GetParamNameList() const
{
	return std::vector<std::string>{ "normal", "contour", "font_color", "font_name", "font_size", "alignement" };
}

std::vector<widget::ParamInfo> Label::Info::GetParametersInfo() const
{
	return { widget::ParamInfo(widget::ParamType::COLOR, "normal"),
		widget::ParamInfo(widget::ParamType::COLOR, "contour"),
		widget::ParamInfo(widget::ParamType::COLOR, "font_color"),
		widget::ParamInfo(widget::ParamType::INTEGER, "font_size"),
		widget::ParamInfo(widget::ParamType::TEXT, "font_name"),
		widget::ParamInfo(widget::ParamType::ALIGNEMENT, "alignement") };
}

std::string Label::Info::GetAttributeValue(const std::string& name)
{
	if (name == "normal") {
		return normal.ToString();
	}
	else if (name == "contour") {
		return contour.ToString();
	}
	else if (name == "font_color") {
		return font_color.ToString();
	}
	else if (name == "font_name") {
		return font_name;
	}
	else if (name == "font_size") {
		return std::to_string(font_size);
	}
	else if (name == "alignement") {
		if (alignement == ax::util::axALIGN_LEFT) {
			return "left";
		}
		else if (alignement == ax::util::axALIGN_CENTER) {
			return "center";
		}
		else if (alignement == ax::util::axALIGN_RIGHT) {
			return "right";
		}
	}

	return "";
}

void Label::Info::SetAttribute(const std::pair<std::string, std::string>& attribute)
{
	if (attribute.first == "normal") {
		normal = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "contour") {
		contour = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "font_color") {
		font_color = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "font_name") {
		font_name = attribute.second;
	}
	else if (attribute.first == "font_size") {
		font_size = stoi(attribute.second);
	}
	else if (attribute.first == "alignement") {
		if (attribute.second == "left") {
			alignement = ax::util::axALIGN_LEFT;
		}
		else if (attribute.second == "center") {
			alignement = ax::util::axALIGN_CENTER;
		}
		else if (attribute.second == "right") {
			alignement = ax::util::axALIGN_RIGHT;
		}
	}
}

Label::Component::Component(ax::Window* win, Info* info)
	: ax::widget::Component(win, info)
{
}

ax::Xml::Node Label::Component::Save(ax::Xml& xml, ax::Xml::Node& node)
{
	ax::Window* win = GetWindow();
	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
	ax::Label* label = static_cast<ax::Label*>(bbone.get());

	ax::Label::Component* widget_comp
		= static_cast<ax::Label::Component*>(win->component.Get("Widget").get());

	ax::Label::Info* info = static_cast<ax::Label::Info*>(widget_comp->GetInfo());

	ax::Xml::Node widget_node = xml.CreateNode("Widget");
	node.AddNode(widget_node);
	widget_node.AddAttribute("builder", "Label");

	ax::Rect rect = win->dimension.GetRect();

	// Position.
	widget_node.AddNode(xml.CreateNode("position", std::to_string(rect.position)));

	// Size.
	widget_node.AddNode(xml.CreateNode("size", std::to_string(rect.size)));

	ax::Xml::Node info_node = xml.CreateNode("info");
	widget_node.AddNode(info_node);
	info_node.AddAttribute("normal", info->normal.ToString());
	info_node.AddAttribute("contour", info->contour.ToString());
	info_node.AddAttribute("font_color", info->font_color.ToString());

	info_node.AddAttribute("font_size", std::to_string(info->font_size));
	info_node.AddAttribute("font_name", std::to_string(info->font_name));

	std::string align_str;

	if (info->alignement == ax::util::axALIGN_LEFT) {
		align_str = "left";
	}
	else if (info->alignement == ax::util::axALIGN_CENTER) {
		align_str = "center";
	}
	else if (info->alignement == ax::util::axALIGN_RIGHT) {
		align_str = "right";
	}

	info_node.AddAttribute("alignement", align_str);

	widget_node.AddNode(xml.CreateNode("label", label->GetLabel()));
	return widget_node;
}

std::vector<std::pair<std::string, std::string>> Label::Component::GetBuilderAttributes()
{
	ax::Window* win = GetWindow();
	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
	ax::Label* btn = static_cast<ax::Label*>(bbone.get());

	std::vector<std::pair<std::string, std::string>> atts;

	ax::Point position = win->dimension.GetRect().position;
	std::string pos_str(std::to_string(position.x) + ", " + std::to_string(position.y));
	atts.push_back(std::pair<std::string, std::string>("position", pos_str));

	ax::Size size = win->dimension.GetSize();
	std::string size_str(std::to_string(size.w) + ", " + std::to_string(size.h));
	atts.push_back(std::pair<std::string, std::string>("size", size_str));

	atts.push_back(std::pair<std::string, std::string>("label", btn->GetLabel()));

	return atts;
}

void Label::Component::SetBuilderAttributes(const std::vector<std::pair<std::string, std::string>>& attributes)
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
		else if (n.first == "label") {
			ax::Label* label = static_cast<ax::Label*>(GetWindow()->backbone.get());
			label->SetLabel(n.second);
		}
	}
}

std::vector<ax::widget::ParamInfo> Label::Component::GetBuilderAttributesInfo() const
{
	return { ax::widget::ParamInfo(ax::widget::ParamType::POINT, "position"),
		ax::widget::ParamInfo(ax::widget::ParamType::SIZE, "size"),
		ax::widget::ParamInfo(ax::widget::ParamType::TEXT, "label") };
}

void Label::Component::SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	_info->SetAttributes(attributes);
}

void Label::Component::ReloadInfo()
{
	Label* label_obj = static_cast<Label*>(_win->backbone.get());
	Label::Info* info = static_cast<Label::Info*>(_info);

	if (!info->font_name.empty()) {
		label_obj->_font->SetFontType(info->font_name);
	}
	label_obj->_font->SetFontSize(info->font_size);

	_win->Update();
}

Label::Builder::Builder()
{
}

std::shared_ptr<ax::Window::Backbone> Label::Builder::Create(
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
	std::string label = control.GetChildNodeValue("label");

	ax::Xml::Node info_node = control.GetNode("info");
	ax::Label::Info l_info;
	l_info.SetAttribute(std::pair<std::string, std::string>("normal", info_node.GetAttribute("normal")));
	l_info.SetAttribute(std::pair<std::string, std::string>("contour", info_node.GetAttribute("contour")));
	l_info.SetAttribute(std::pair<std::string, std::string>("font_color", info_node.GetAttribute("font_color")));
	l_info.SetAttribute(std::pair<std::string, std::string>("font_size", info_node.GetAttribute("font_size")));
	l_info.SetAttribute(std::pair<std::string, std::string>("font_name", info_node.GetAttribute("font_name")));
	l_info.SetAttribute(std::pair<std::string, std::string>("alignement", info_node.GetAttribute("alignement")));

	auto l = ax::shared<ax::Label>(ax::Rect(pos, size), l_info, label);
	return l;
}

std::shared_ptr<ax::Window::Backbone> Label::Builder::Create(ax::Xml::Node& node)
{
	ax::Point pos(node.GetChildNodeValue("position"));
	ax::Size size(node.GetChildNodeValue("size"));
	std::string label = node.GetChildNodeValue("label");

	ax::Xml::Node info_node = node.GetNode("info");
	ax::Label::Info l_info;
	l_info.SetAttribute(std::pair<std::string, std::string>("normal", info_node.GetAttribute("normal")));
	l_info.SetAttribute(std::pair<std::string, std::string>("contour", info_node.GetAttribute("contour")));
	l_info.SetAttribute(std::pair<std::string, std::string>("font_color", info_node.GetAttribute("font_color")));
	l_info.SetAttribute(std::pair<std::string, std::string>("font_size", info_node.GetAttribute("font_size")));
	l_info.SetAttribute(std::pair<std::string, std::string>("font_name", info_node.GetAttribute("font_name")));
	l_info.SetAttribute(std::pair<std::string, std::string>("alignement", info_node.GetAttribute("alignement")));

	auto l = ax::shared<ax::Label>(ax::Rect(pos, size), l_info, label);
	return l;
}

/*
 * ax::Label.
 */
Label::Label(const ax::Rect& rect, const Label::Info& info, const std::string& label)
	: _label(label)
	, _font(nullptr)
{
	win = ax::Window::Create(rect);

	// Builtin event connection.
	win->event.OnPaint = ax::WBind<ax::GC>(this, &Label::OnPaint);

	win->component.Add(
		"Widget", widget::Component::Ptr(new ax::Label::Component(win, new ax::Label::Info(info))));

	//	win->property.RemoveProperty("Selectable");

	if (!info.font_name.empty()) {
		_font = std::unique_ptr<ax::Font>(new ax::Font(info.font_name));
	}
	else {
		_font = std::unique_ptr<ax::Font>(new ax::Font(0));
	}

	_font->SetFontSize(info.font_size);
}

ax::Window::Backbone* Label::GetCopy()
{
	widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
	ax::Label::Info* info = static_cast<ax::Label::Info*>(widget->GetInfo());
	ax::Label* label = new ax::Label(win->dimension.GetRect(), *info, _label);
	return label;
}

void Label::SetLabel(const std::string& label)
{
	_label = label;
	win->Update();
}

void Label::OnPaint(ax::GC gc)
{
	const ax::Rect rect(win->dimension.GetDrawingRect());
	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	ax::Label::Info& info = *static_cast<ax::Label::Info*>(widget->GetInfo());

	gc.SetColor(info.normal);
	gc.DrawRectangle(rect);

	gc.SetColor(info.font_color);

	if (info.alignement == ax::util::axALIGN_CENTER) {
		gc.DrawStringAlignedCenter(*_font, _label, rect);
	}
	else if (info.alignement == ax::util::axALIGN_LEFT) {
		gc.DrawString(*_font, _label, ax::Point(5, 2));
	}

	gc.SetColor(info.contour);
	gc.DrawRectangleContour(rect);
}
}
