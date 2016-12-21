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

#ifndef __AX_TOGGLE__
#define __AX_TOGGLE__

/*
 * @file    axToggle.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axToggle.
 * @date    19/07/2013
 */

/// @defgroup Widgets
/// @{

/// @defgroup Toggle
/// @{

#include "axlib.hpp"
#include <fstream>

namespace ax {
/*
 * ax::Toggle.
 */
class Toggle : public ax::Window::Backbone {
public:
	/*
	 * ax::Toggle::Flags.
	 */
	class Flags {
	public:
		static const ax::util::Flag SINGLE_IMG;
		static const ax::util::Flag IMG_RESIZE;
		static const ax::util::Flag CLICK_ON_LEFT_DOWN;
		static const ax::util::Flag CANT_UNSELECT_WITH_MOUSE;
	};

	/*
	 * ax::Toggle::Msg.
	 */
	class Msg : public ax::event::Msg {
	public:
		Msg();

		Msg(ax::Toggle* sender, const bool& selected);

		Msg(ax::Toggle* sender, const bool& selected, const std::string& msg);

		ax::Toggle* GetSender() const;

		bool GetSelected() const;

		std::string GetMsg() const;

		ax::event::Msg* GetCopy();

	private:
		ax::Toggle* _sender;
		bool _selected;
		std::string _msg;
	};

	/*
	 * axToggle::Events.
	 */
	class Events {
	public:
		enum : ax::event::Id { BUTTON_CLICK };

		ax::event::Function button_click;

		Events()
		{
		}

		Events(const ax::event::Function& fct)
		{
			button_click = fct;
		}
	};

	/*
	 * axToggle::Info.
	 */
	class Info : public ax::widget::Info {
	public:
		Info();

		ax::Color normal;
		ax::Color hover;
		ax::Color clicking;
		ax::Color font_color;

		ax::Color selected;
		ax::Color selected_hover;
		ax::Color selected_clicking;
		/// @todo Add select font color to axToggle.
		ax::Color selected_font_color;

		ax::Color contour;

		int font_size = 12;

		std::string img;
		bool single_img;

		/// Info needed for debug editor. Derived from axInfo.
		virtual std::vector<std::string> GetParamNameList() const;
		virtual std::string GetAttributeValue(const std::string& name);
		virtual void SetAttribute(const std::pair<std::string, std::string>& attribute);

		virtual std::vector<widget::ParamInfo> GetParametersInfo() const
		{
			return { widget::ParamInfo(widget::ParamType::COLOR, "normal"),
				widget::ParamInfo(widget::ParamType::COLOR, "hover"),
				widget::ParamInfo(widget::ParamType::COLOR, "clicking"),
				widget::ParamInfo(widget::ParamType::COLOR, "font_color"),

				widget::ParamInfo(widget::ParamType::COLOR, "selected"),
				widget::ParamInfo(widget::ParamType::COLOR, "selected_hover"),
				widget::ParamInfo(widget::ParamType::COLOR, "selected_clicking"),
				widget::ParamInfo(widget::ParamType::COLOR, "selected_font_color"),

				widget::ParamInfo(widget::ParamType::COLOR, "contour"),

				widget::ParamInfo(widget::ParamType::INTEGER, "font_size"),
				widget::ParamInfo(widget::ParamType::FILEPATH, "img"),
				widget::ParamInfo(widget::ParamType::BOOLEAN, "single_img") };
		}
	};

	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);

		virtual ax::Xml::Node Save(ax::Xml& xml, ax::Xml::Node& node);
		virtual std::vector<std::pair<std::string, std::string>> GetBuilderAttributes();

		virtual void SetBuilderAttributes(const std::vector<std::pair<std::string, std::string>>& attributes);

		virtual std::vector<ax::widget::ParamInfo> GetBuilderAttributesInfo() const;

		virtual void ReloadInfo();
		virtual void SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes);

		std::string GetBuilderName() const
		{
			return "Toggle";
		}
	};

	class Builder : public ax::widget::Builder {
	public:
		Builder();

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			const ax::Point& pos, const std::string& file_path);

		std::shared_ptr<ax::Window::Backbone> Create(ax::Xml::Node& node);
	};

	/*
	 * ax::Toggle::axToggle.
	 */
	Toggle(const ax::Rect& rect, const Events& events, const Info& info, std::string img_path = "",
		std::string label = "", ax::util::Flag flags = 0, std::string msg = "");

	ax::Window::Backbone* GetCopy();

	void SetMsg(const std::string& msg);

	void SetSelected(const bool& selected);

	bool IsSelected() const
	{
		return _selected;
	}

	std::string GetLabel() const
	{
		return _label;
	}

	void SetLabel(const std::string& label)
	{
		_label = label;
		win->Update();
	}

	std::string GetMsg() const
	{
		return _msg;
	}

	ax::util::Flag GetFlags() const
	{
		return _flags;
	}

	std::string GetImagePath() const
	{
		return _bgImg->GetImagePath();
	}

protected:
	enum ToggleState {
		axTOG_NORMAL,
		axTOG_HOVER,
		axTOG_CLICK,
		axTOG_SEL_NORMAL,
		axTOG_SEL_HOVER,
		axTOG_SEL_CLICK
	};

	int _nCurrentImg;

	ax::Toggle::Events _events;

	ax::Color _currentColor;
	std::shared_ptr<ax::Image> _bgImg;
	std::string _label;
	std::string _msg;
	std::unique_ptr<ax::Font> _font;
	ax::Toggle::Info* _info;

	bool _selected;
	ax::util::Flag _flags;
	ax::Color test;
	double _bgAlpha;

	// Events.
	virtual void OnPaint(ax::GC gc);
	virtual void OnMouseLeftDown(const ax::Point& pos);
	virtual void OnMouseLeftUp(const ax::Point& pos);
	virtual void OnMouseEnter(const ax::Point& pos);
	virtual void OnMouseLeave(const ax::Point& pos);
	virtual void OnMouseLeftDoubleClick(const ax::Point& pos);
};
}
/// @}
/// @}
#endif //__AX_TOGGLE__
