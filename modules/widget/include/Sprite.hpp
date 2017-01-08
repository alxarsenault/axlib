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
#pragma once

/*
 * @file    Sprite
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   Sprite widget.
 * @date    30/12/2016
 */

/// @defgroup Widgets
/// @{

/// @defgroup Sprite
/// @{

#include "axlib.hpp"

namespace ax {
/*
 * ax::Sprite.
 */
class Sprite : public ax::Window::Backbone {
public:
	/*
	 * ax::Sprite::Info.
	 */
	class Info : public ax::widget::Info {
	public:
		Info();

		virtual std::vector<std::string> GetParamNameList() const;
		virtual std::string GetAttributeValue(const std::string& name);
		virtual void SetAttribute(const std::pair<std::string, std::string>& attribute);

		virtual std::vector<widget::ParamInfo> GetParametersInfo() const
		{
			return {
				widget::ParamInfo(widget::ParamType::FILEPATH, "img_path"),
				widget::ParamInfo(widget::ParamType::SIZE, "sprite_size"),
				widget::ParamInfo(widget::ParamType::INTEGER, "n_sprite") };
		}

		std::string img_path;
		ax::Size sprite_size;
		unsigned int n_sprite;

		std::shared_ptr<ax::Image> img;
	};

	/*
	 * ax::Sprite::Component.
	 */
	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);

		virtual void SaveFromWidgetNode(ax::Xml& xml, ax::Xml::Node& widget_node);

		std::string GetBuilderName() const
		{
			return "Sprite";
		}

		virtual std::vector<std::pair<std::string, std::string>> GetBuilderAttributes();
		virtual std::vector<ax::widget::ParamInfo> GetBuilderAttributesInfo() const;

		virtual void SetBuilderAttributes(const std::vector<std::pair<std::string, std::string>>& attributes);
		virtual void SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes);
		virtual void ReloadInfo();
	};

	class Builder : public ax::widget::Builder {
	public:
		Builder();

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			const ax::Point& pos, const std::string& file_path);

		std::shared_ptr<ax::Window::Backbone> Create(ax::Xml::Node& node);
	};

	/*
	 * Sprite.
	 */
	Sprite(const ax::Rect& rect, const ax::Sprite::Info& info);

	ax::Window::Backbone* GetCopy();
	
	void SetCurrentIndex(int index);
	
	int GetCurrentIndex() const {
		return _nCurrentImg;
	}
	
	int GetNumberOfSprite() const;

protected:
	std::shared_ptr<ax::Image> _spriteImg;
	unsigned int _nCurrentImg;

	void OnPaint(ax::GC gc);
};
}

/// @}
/// @}
