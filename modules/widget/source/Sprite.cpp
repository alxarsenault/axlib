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

#include "Sprite.hpp"

namespace ax {
/*
 * Sprite::Info.
 */
Sprite::Info::Info()
	: sprite_size(Size(50, 50))
	, n_sprite(128)
{
}

std::vector<std::string> Sprite::Info::GetParamNameList() const
{
	return std::vector<std::string>{ "sprite_size", "n_sprite", "img_path" };
}

std::string Sprite::Info::GetAttributeValue(const std::string& name)
{
	ax::Size a;
	if (name == "sprite_size") {
		return sprite_size.ToString();
	}
	else if (name == "n_sprite") {
		return std::to_string(n_sprite);
	}
	else if (name == "img_path") {
		return img_path;
	}

	return "";
}

void Sprite::Info::SetAttribute(const std::pair<std::string, std::string>& attribute)
{
	if (attribute.first == "sprite_size") {
		sprite_size = ax::Size(attribute.second);
	}
	else if (attribute.first == "n_sprite") {
		n_sprite = std::stoi(attribute.second);
	}
	else if (attribute.first == "img_path") {
		img_path = attribute.second;
	}
}

Sprite::Component::Component(Window* win, Info* info)
	: widget::Component(win, info)
{
}

void Sprite::Component::SaveFromWidgetNode(ax::Xml& xml, ax::Xml::Node& widget_node)
{
	ax::Window* win = GetWindow();
	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;
	ax::Sprite::Component* widget_comp = static_cast<ax::Sprite::Component*>(win->component.Get("Widget").get());
	ax::Sprite::Info* info = static_cast<ax::Sprite::Info*>(widget_comp->GetInfo());

	widget_node.AddAttribute("builder", "Sprite");

	ax::Rect rect = win->dimension.GetRect();
	widget_node.AddNode(xml.CreateNode("position", std::to_string(rect.position)));
	widget_node.AddNode(xml.CreateNode("size", std::to_string(rect.size)));

	ax::Xml::Node info_node = xml.CreateNode("info");
	widget_node.AddNode(info_node);
	info_node.AddAttribute("img_path", info->img_path);
	info_node.AddAttribute("sprite_size", info->sprite_size.ToString());
	info_node.AddAttribute("n_sprite", std::to_string(info->n_sprite));
}

std::vector<std::pair<std::string, std::string>> Sprite::Component::GetBuilderAttributes()
{
	ax::Window* win = GetWindow();
	std::shared_ptr<ax::Window::Backbone> bbone = win->backbone;

	std::vector<std::pair<std::string, std::string>> atts;
	atts.push_back(std::pair<std::string, std::string>("position", win->dimension.GetRect().position.ToString()));
	atts.push_back(std::pair<std::string, std::string>("size", win->dimension.GetSize().ToString()));

	return atts;
}

std::vector<ax::widget::ParamInfo> Sprite::Component::GetBuilderAttributesInfo() const
{
	return { ax::widget::ParamInfo(ax::widget::ParamType::POINT, "position"),
		ax::widget::ParamInfo(ax::widget::ParamType::SIZE, "size")};
}

void Sprite::Component::SetBuilderAttributes(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	for (auto& n : attributes) {
		if (n.first == "position") {
			ax::Point pos = ax::Point(n.second);
			GetWindow()->dimension.SetPosition(pos);
		}
		else if (n.first == "size") {
			ax::Size size = ax::Size(n.second);
			GetWindow()->dimension.SetSize(size);
		}
	}
}

void Sprite::Component::SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	_info->SetAttributes(attributes);
}

void Sprite::Component::ReloadInfo()
{
	Sprite* sprite_obj = static_cast<Sprite*>(_win->backbone.get());
	Sprite::Info* info = static_cast<Sprite::Info*>(_info);

	if (sprite_obj->_spriteImg->GetImagePath() != info->img_path) {
		sprite_obj->_spriteImg.reset(new Image(info->img_path));
	}

	sprite_obj->_nCurrentImg = 0;

	_win->Update();
}

Sprite::Builder::Builder()
{
}

std::shared_ptr<Window::Backbone> Sprite::Builder::Create(const Point& pos, const std::string& file_path)
{
	ax::Xml xml(file_path);

	if (!xml.Parse()) {
		ax::console::Error("Parsing error.");
		return nullptr;
	}

	ax::Xml::Node control = xml.GetNode("Widget");
	std::string builder_name = control.GetAttribute("builder");
	std::string obj_name = control.GetAttribute("name");

	ax::Size size(control.GetChildNodeValue("size"));
	ax::Xml::Node info_node = control.GetNode("info");

	ax::Sprite::Info k_info;
	k_info.img_path = info_node.GetAttribute("img_path");
	k_info.sprite_size = ax::Size(info_node.GetAttribute("sprite_size"));
	k_info.n_sprite = std::stoi(info_node.GetAttribute("n_sprite"));

	return ax::shared<ax::Sprite>(ax::Rect(pos, size), k_info);;
}

std::shared_ptr<Window::Backbone> Sprite::Builder::Create(Xml::Node& node)
{
	ax::Xml::Node control(node);
	std::string builder_name = control.GetAttribute("builder");

	ax::Point pos(control.GetChildNodeValue("position"));
	ax::Size size(control.GetChildNodeValue("size"));

	ax::Xml::Node info_node = control.GetNode("info");

	ax::Sprite::Info k_info;
	k_info.img_path = info_node.GetAttribute("img_path");
	k_info.sprite_size = ax::Size(info_node.GetAttribute("sprite_size"));
	k_info.n_sprite = std::stoi(info_node.GetAttribute("n_sprite"));

	return ax::shared<ax::Sprite>(ax::Rect(pos, size), k_info);
}

/*
 * Sprite.
 */
Sprite::Sprite(const Rect& rect, const Sprite::Info& info)
	: _nCurrentImg(0)
{
	win = Window::Create(rect);

	win->event.OnPaint = WBind<GC>(this, &Sprite::OnPaint);
	win->component.Add("Widget", widget::Component::Ptr(new Sprite::Component(win, new Sprite::Info(info))));

	// Check for share Image first.
	if (info.img) {
		_spriteImg = info.img;
		// If no shared image then look for image path.
	}
	else if (!info.img_path.empty()) {
		_spriteImg = std::shared_ptr<Image>(new Image(info.img_path));
	}
}

ax::Window::Backbone* Sprite::GetCopy()
{
	widget::Component* widget = win->component.Get<widget::Component>("Widget").get();
	ax::Sprite::Info* info = widget->GetInfo<ax::Sprite::Info>();
	ax::Sprite* knob = new ax::Sprite(win->dimension.GetRect(), *info);
	return knob;
}

void Sprite::SetCurrentIndex(int index)
{
	if(_nCurrentImg != index) {
		/// @todo Do check for index bounds.
		_nCurrentImg = index;
		win->Update();
	}
}

	int Sprite::GetNumberOfSprite() const {
		if(!(_spriteImg && _spriteImg->IsImageReady())) {
			return 0;
		}
		
		widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
		Sprite::Info& info = *static_cast<Sprite::Info*>(widget->GetInfo());
		return _spriteImg->GetSize().w / info.sprite_size.w;
	}

void Sprite::OnPaint(GC gc)
{
	const Rect rect(Point(0, 0), win->dimension.GetSize());
	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	Sprite::Info& info = *static_cast<Sprite::Info*>(widget->GetInfo());

	if (_spriteImg) {
		gc.DrawPartOfImageResize(_spriteImg.get(), Point(_nCurrentImg * info.sprite_size.w, 0), info.sprite_size,
			ax::Rect(ax::Point(0, 0), rect.size));
	}
}
}
