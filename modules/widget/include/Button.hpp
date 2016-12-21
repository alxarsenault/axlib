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
 * @file    axButton.hpp
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axButton.
 * @date    19/07/2013
 */

/// @defgroup Widgets
/// @{

/// @defgroup Button
/// @{

#include "axlib.hpp"

namespace ax {

/*
 * ax::Buton.
 */
class Button : public ax::Window::Backbone {
public:
	typedef std::shared_ptr<Button> Ptr;

	/*
	 * ax::Button::Flags.
	 */
	class Flags {
	public:
		static const ax::util::Flag SINGLE_IMG;
		static const ax::util::Flag IMG_RESIZE;
		static const ax::util::Flag CAN_SELECTED;
	};

	/*
	 * ax::Button::Msg.
	 */
	class Msg : public ax::event::Msg {
	public:
		Msg();

		Msg(Button* sender, const std::string& msg);

		Button* GetSender() const;

		std::string GetMsg() const;

		ax::event::Msg* GetCopy();

	private:
		Button* _sender;
		std::string _msg;
	};

	/*
	 * axButton::Events.
	 */
	class Events {
	public:
		enum : ax::event::Id { BUTTON_CLICK };

		Events()
		{
		}

		Events(const ax::event::Function& fct)
		{
			button_click = fct;
		}

		ax::event::Function button_click;
	};

	/*
	 * axButton::Info.
	 */
	class Info : public ax::widget::Info {
	public:
		Info(const std::string& path);

		Info(const std::vector<std::pair<std::string, std::string>>& attributes);

		Info(const ax::Color& normal_color = ax::Color(0.9f), const ax::Color& hover_color = ax::Color(0.92f),
			const ax::Color& clicked_color = ax::Color(0.95f),
			const ax::Color& selected_color = ax::Color(0.9f),
			const ax::Color& contour_color = ax::Color(0.5f), const ax::Color& font_color = ax::Color(0.1f),
			const int& corner_radius = 0);

		/// Info needed for debug editor. Derived from axInfo.
		virtual std::vector<std::string> GetParamNameList() const;

		virtual std::string GetAttributeValue(const std::string& name);

		virtual void SetAttribute(const std::pair<std::string, std::string>& attribute);

		virtual std::vector<widget::ParamInfo> GetParametersInfo() const;

		ax::Color normal; /// Normal background color.
		ax::Color hover; /// Color when mouse is over.
		ax::Color clicking; /// Mouse clicking color.
		ax::Color selected; /// Color once the button has been clicked.
		ax::Color contour; /// Contour color.
		ax::Color font_color; /// Font color.
		int corner_radius = 0;
	};

	/*
	 * ax::Button::Component.
	 */
	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);

		//		virtual ax::Xml::Node Save(ax::Xml& xml, ax::Xml::Node& node);
		virtual std::vector<std::pair<std::string, std::string>> GetBuilderAttributes();

		std::string GetBuilderName() const
		{
			return "Button";
		}

		void SetBuilderAttributes(const std::vector<std::pair<std::string, std::string>>& attributes);

		virtual std::vector<ax::widget::ParamInfo> GetBuilderAttributesInfo() const;

		virtual void ReloadInfo();
		virtual void SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes);
	};

	class Builder : public ax::widget::Builder {
	public:
		Builder();

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			const ax::Point& pos, const std::string& file_path);

		virtual std::shared_ptr<ax::Window::Backbone> Create(ax::Attribute& node);

		virtual std::shared_ptr<ax::Window::Backbone> Create(ax::Xml::Node& node);
	};

	/*
	 * ax::Button::Button.
	 */
	Button(const ax::Rect& rect, const Button::Events& events, const Button::Info& info,
		std::string img_path = "", std::string label = "", ax::util::Flag flags = 0, std::string msg = "");

	Button(const ax::Point& pos, const Button::Events& events, std::string label = "",
		std::string img_path = "", const Button::Info& info = Button::Info(), ax::util::Flag flags = 0,
		std::string msg = "");

	inline static std::shared_ptr<ax::Window::Backbone> Create(const ax::Point& pos,
		const Button::Events& events, std::string label = "", std::string img_path = "",
		const Button::Info& info = Button::Info(), ax::util::Flag flags = 0, std::string msg = "")
	{
		return std::shared_ptr<ax::Window::Backbone>(
			new ax::Button(pos, events, label, img_path, info, flags, msg));
	}

	inline static std::shared_ptr<ax::Window::Backbone> Create(const ax::Rect& rect,
		const Button::Events& events, std::string label = "", std::string img_path = "",
		const Button::Info& info = Button::Info(), ax::util::Flag flags = 0, std::string msg = "")
	{
		return std::shared_ptr<ax::Window::Backbone>(
			new ax::Button(rect, events, info, img_path, label, flags, msg));
	}

	void SetMsg(const std::string& msg);

	void SetSelected(const bool& selected);

	void SetLabel(const std::string& label);

	const std::string& GetLabel() const
	{
		return _label;
	}

	const std::string& GetMsg() const
	{
		return _msg;
	}

	ax::util::Flag GetFlags() const
	{
		return _flags;
	}

	std::string GetImagePath() const
	{
		return _btnImg->GetImagePath();
	}

	virtual Backbone* GetCopy();

protected:
	Button::Events _events;
	std::unique_ptr<ax::Image> _btnImg;
	ax::util::Flag _flags;
	std::string _label, _msg;
	ax::Font _font;

	ax::Color _currentColor;
	bool _selected;
	int _nCurrentImg;

	enum axButtonState { axBTN_NORMAL, axBTN_HOVER, axBTN_DOWN, axBTN_SELECTED };

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
