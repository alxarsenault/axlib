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
 * @file    axPanel.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axPanel.
 * @date    01/03/2016
 */

/// @defgroup Widgets
/// @{

/// @defgroup Panel
/// @{

#include "axlib.hpp"
#include "Xml.hpp"

namespace ax {

/*
 * ax::Panel.
 */
class Panel : public ax::Window::Backbone {
public:
	/*
	 * ax::Panel::Flags.
	 */
	class Flags {
	public:
		//		static const ax::util::Flag SINGLE_IMG;
		//		static const ax::util::Flag IMG_RESIZE;
		//		static const ax::util::Flag CAN_SELECTED;
	};

	/*
	 * ax::Panel::Info.
	 */
	class Info : public ax::widget::Info {
	public:
		Info(const std::string& path);

		Info(const std::vector<std::pair<std::string, std::string>>& attributes);

		Info();

		/// Info needed for debug editor. Derived from axInfo.
		virtual std::vector<std::string> GetParamNameList() const;
		virtual std::string GetAttributeValue(const std::string& name);
		virtual void SetAttribute(const std::pair<std::string, std::string>& attribute);

		virtual std::vector<widget::ParamInfo> GetParametersInfo() const
		{
			return { widget::ParamInfo(widget::ParamType::COLOR, "background"),
				widget::ParamInfo(widget::ParamType::COLOR, "contour"),
				widget::ParamInfo(widget::ParamType::INTEGER, "round_corner_radius") };
		}

		ax::Color background; /// Normal background color.
		ax::Color contour; /// Contour color.
		int round_corner_radius = 0;
	};

	/*
	 * ax::Panel::Component.
	 */
	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);

		virtual void SaveFromWidgetNode(ax::Xml& xml, ax::Xml::Node& widget_node);

		virtual void SetSaveChildCallback(std::function<void(ax::Xml&, ax::Xml::Node&, ax::Window*)> fct)
		{
			_save_child_callback = fct;
		}

		std::string GetBuilderName() const
		{
			return "Panel";
		}

		std::vector<std::pair<std::string, std::string>> GetBuilderAttributes();
		std::vector<ax::widget::ParamInfo> GetBuilderAttributesInfo() const;

		virtual void SetBuilderAttributes(const std::vector<std::pair<std::string, std::string>>& attributes);

		virtual void SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes);
		virtual void ReloadInfo();

	private:
		std::function<void(ax::Xml&, ax::Xml::Node&, ax::Window*)> _save_child_callback;
	};

	/*
	 * ax::Panel::Builder.
	 */
	class Builder : public ax::widget::Builder {
	public:
		Builder();

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			const ax::Point& pos, const std::string& file_path);

		std::shared_ptr<ax::Window::Backbone> Create(ax::Xml::Node& node);

		virtual void SetCreateCallback(std::function<void(ax::Window*, ax::Xml::Node&)> fct)
		{
			_create_callback = fct;
		}

	private:
		void CreateChildren(ax::Xml::Node& node, ax::Panel* panel);

		std::function<void(ax::Window*, ax::Xml::Node&)> _create_callback;
	};

	/*
	 * ax::Panel.
	 */
	Panel(const ax::Rect& rect, const Panel::Info& info, const std::string& bg_img,
		const std::string& name = "", ax::util::Flag flags = 0);

	ax::Window::Backbone* GetCopy();

	ax::util::Flag GetFlags() const
	{
		return _flags;
	}

	std::string GetName() const
	{
		return _name;
	}

	void SetName(const std::string& name)
	{
		_name = name;
	}

	std::string GetBackgroundImagePath() const
	{
		if(!_bg_img) {
			return "";
		}
		
		if(!_bg_img->IsImageReady()) {
			return "";
		}
		
		return _bg_img->GetImagePath();
	}

protected:
	ax::util::Flag _flags;
	std::string _bg_img_path;
	std::string _name;
	std::unique_ptr<ax::Image> _bg_img;

	void OnPaint(ax::GC gc);
};
}

/// @}
/// @}
