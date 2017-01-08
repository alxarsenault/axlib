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
 * @file    axNumberBox.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axNumberBox.
 * @date    19/07/2013
 */

/// @defgroup Widgets
/// @{

/// @defgroup NumberBox
/// @{

#include "axlib.hpp"

namespace ax {
/*
 * ax::NumberBox.
 */
class NumberBox : public ax::Window::Backbone {
public:
	/// Shared pointer.
	typedef std::shared_ptr<ax::NumberBox> Ptr;

	/*
	 * ax::NumberBox::Flags.
	 */
	class Flags {
	public:
		static const ax::util::Flag SINGLE_IMG;
		static const ax::util::Flag NO_IMG_RESIZE;
		static const ax::util::Flag LABEL;
		static const ax::util::Flag SLIDER;
		static const ax::util::Flag NO_MOUSE;
	};

	/*
	 * ax::NumberBox::Msg.
	 */
	class Msg : public ax::event::Msg {
	public:
		Msg(const double& value);

		double GetValue() const;

		ax::event::Msg* GetCopy();

	private:
		double _value;
	};

	/*
	 * ax::NumberBox::Events.
	 */
	class Events {
	public:
		enum : ax::event::Id { VALUE_CHANGE };

		Events()
		{
		}

		Events(ax::event::Function& fct)
		{
			value_change = fct;
		}

		ax::event::Function value_change;
	};

	/*
	 * ax::NumberBox::Info.
	 */
	class Info : public ax::widget::Info {
	public:
		Info(const std::string& path);

		Info(const std::vector<std::pair<std::string, std::string>>& attributes);

		Info(const ax::Color& normal_color = ax::Color(0.9), const ax::Color& hover_color = ax::Color(0.95),
			const ax::Color& clicked_color = ax::Color(0.92),
			const ax::Color& selected_color = ax::Color(0.9), const ax::Color& contour_color = ax::Color(0.5),
			const ax::Color& fontColor = ax::Color(0.1), const std::string& img = "",
			const bool& singleImg = false);

		// Info needed for debug editor. Derived from axInfo.
		virtual std::vector<std::string> GetParamNameList() const;
		virtual std::string GetAttributeValue(const std::string& name);
		virtual void SetAttribute(const std::pair<std::string, std::string>& attribute);

		std::string GetBuilderName() const
		{
			return "NumberBox";
		}

		virtual std::vector<widget::ParamInfo> GetParametersInfo() const
		{
			return { widget::ParamInfo(widget::ParamType::COLOR, "normal"),
				widget::ParamInfo(widget::ParamType::COLOR, "hover"),
				widget::ParamInfo(widget::ParamType::COLOR, "clicking"),
				widget::ParamInfo(widget::ParamType::COLOR, "selected"),
				widget::ParamInfo(widget::ParamType::COLOR, "contour"),
				widget::ParamInfo(widget::ParamType::COLOR, "font_color"),

				widget::ParamInfo(widget::ParamType::TEXT, "img"),
				widget::ParamInfo(widget::ParamType::BOOLEAN, "single_img") };
		}

		ax::Color normal;
		ax::Color hover;
		ax::Color clicking;
		ax::Color selected;
		ax::Color contour;
		ax::Color font_color;

		std::string img;
		bool single_img;
	};
	
	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);
		
		virtual void SaveFromWidgetNode(ax::Xml& xml, ax::Xml::Node& widget_node);
		
		std::string GetBuilderName() const
		{
			return "NumberBox";
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
	 * ax::NumberBox::axNumberBox.
	 */
	NumberBox(const ax::Rect& rect, const ax::NumberBox::Events& events, const ax::NumberBox::Info& info,
		ax::util::Flag flags = 0, double value = 0.0,
		ax::util::Range2D<double> range = ax::util::Range2D<double>(0.0, 1.0),
		ax::util::Control::Type type = ax::util::Control::Type::REAL,
		ax::util::Control::Unit m_unit = ax::util::Control::axCTRL_NO_UNIT,
		ax::util::Control::Interpolation interpolation = ax::util::Control::axCTRL_LINEAR,
		std::string label = "");

	NumberBox(const ax::Point& pos, const ax::NumberBox::Events& events = ax::NumberBox::Events(),
		const ax::NumberBox::Info& info = ax::NumberBox::Info(), ax::util::Flag flags = 0, double value = 0.0,
		ax::util::Range2D<double> range = ax::util::Range2D<double>(0.0, 1.0),
		ax::util::Control::Type type = ax::util::Control::Type::REAL,
		ax::util::Control::Unit m_unit = ax::util::Control::axCTRL_NO_UNIT,
		ax::util::Control::Interpolation interpolation = ax::util::Control::axCTRL_LINEAR,
		std::string label = "");

	inline static std::shared_ptr<ax::Window::Backbone> Create(const ax::Point& pos,
		const ax::NumberBox::Events& events = ax::NumberBox::Events(),
		const ax::NumberBox::Info& info = ax::NumberBox::Info(), ax::util::Flag flags = 0, double value = 0.0,
		ax::util::Range2D<double> range = ax::util::Range2D<double>(0.0, 1.0),
		ax::util::Control::Type type = ax::util::Control::Type::REAL,
		ax::util::Control::Unit m_unit = ax::util::Control::axCTRL_NO_UNIT,
		ax::util::Control::Interpolation interpolation = ax::util::Control::axCTRL_LINEAR,
		std::string label = "")
	{
		return ax::NumberBox::Ptr(
			new ax::NumberBox(pos, events, info, flags, value, range, type, m_unit, interpolation, label));
	}

	ax::Window::Backbone* GetCopy();

	double GetValue();

	void SetValue(const double& value)
	{
		_value = value;
		win->Update();
	}
	
	ax::util::Flag GetFlags() const
	{
		return _flags;
	}
	
	ax::util::Range2D<double> GetRange() const
	{
		return _range;
	}
	
	void SetRange(const ax::util::Range2D<double>& range);
	
	ax::util::Control::Type GetControlType() const {
		return _type;
	}
	
	void SetControlType(ax::util::Control::Type type);

private:
	ax::NumberBox::Events _events;
	ax::util::Flag _flags;
	ax::Image* _bgImg;
	ax::Font* _font;

	ax::util::Control::Type _type;
	ax::util::Range2D<double> _range;
	//	ax::util::Control::Interpolation _interpolation;

	ax::Color _currentColor;
	int _nCurrentImg;
	double _value;
	double _zeroToOneValue;
	std::string _label;

	int _clickPosY;

	enum NumberBoxState { axNUM_BOX_NORMAL, axNUM_BOX_HOVER, axNUM_BOX_DOWN };

	// Events.
	virtual void OnPaint(ax::GC gc);

	virtual void OnMouseLeftDown(const ax::Point& pos);
	virtual void OnMouseLeftUp(const ax::Point& pos);
	virtual void OnMouseLeftDragging(const ax::Point& pos);
	virtual void OnMouseEnter(const ax::Point& pos);
	virtual void OnMouseLeave(const ax::Point& pos);
};
}

/// @}
/// @}
