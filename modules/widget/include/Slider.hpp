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

#ifndef __AX_SLIDER_H__
#define __AX_SLIDER_H__

/// @defgroup Widgets
/// @{

/// @defgroup Slider
/// @{
//
#include "axlib.hpp"

namespace ax {
/*
 * ax::Slider.
*/
class Slider : public ax::Window::Backbone {
public:
	/*
	 * ax::Slider::Flags.
	 */
	class Flags {
	public:
		static const ax::util::Flag VERTICAL;
		static const ax::util::Flag CLICK_ANYWHERE;
		static const ax::util::Flag RELEASE_ON_LEAVE;
		static const ax::util::Flag LEFT_CLICK_ENTER;
		static const ax::util::Flag RIGHT_ALIGN;
		static const ax::util::Flag MIDDLE_ALIGN;
		static const ax::util::Flag BACK_SLIDER;
		static const ax::util::Flag NO_SLIDER_LINE;
	};

	/*
	 * axSliderMsg
	 */
	class Msg : public ax::event::Msg {
	public:
		Msg(Slider* slider, const double& value)
			: _value(value)
			, _slider(slider)
		
		{
		}

		double GetValue() const
		{
			return _value;
		}

		Slider* GetSender() const
		{
			return _slider;
		}

		ax::event::Msg* GetCopy()
		{
			return new ax::Slider::Msg(*this);
		}

	private:
		double _value;
		ax::Slider* _slider;
	};

	/*
	 * axSliderEvents.
	 */
	struct Events {
		enum : ax::event::Id { VALUE_CHANGE };

		Events()
		{
		}

		Events(const ax::event::Function& fct)
		{
			slider_value_change = fct;
		}

		ax::event::Function slider_value_change;
	};

	/*
	 * axSliderInfo.
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
		
		virtual std::vector<widget::ParamInfo> GetParametersInfo() const;

		ax::Color bgColorNormal;
		ax::Color bgColorHover;
		ax::Color bgColorClicked;
		
		ax::Color sliderColorNormal;
		ax::Color sliderColorHover;
		ax::Color sliderColorClicked;
		ax::Color sliderContourColor;
		
		ax::Color contourColor;
		ax::Color backSliderColor;
		ax::Color backSliderContourColor;
		
		std::string img_path;
		ax::Size btn_size;
		unsigned int slider_width;
		int contour_round_radius = 0;
	};

	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);

		virtual ax::Xml::Node Save(ax::Xml& xml, ax::Xml::Node& node);
		virtual std::vector<std::pair<std::string, std::string>> GetBuilderAttributes();
		virtual std::vector<ax::widget::ParamInfo> GetBuilderAttributesInfo() const;
		virtual void SetBuilderAttributes(const std::vector<std::pair<std::string, std::string>>& attributes);
		virtual void SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes);
		virtual void ReloadInfo();
		
		inline std::string GetBuilderName() const
		{
			return "Slider";
		}
	};

	class Builder : public ax::widget::Builder {
	public:
		Builder();

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			const ax::Point& pos, const std::string& file_path);

		std::shared_ptr<ax::Window::Backbone> Create(ax::Xml::Node& node);
	};

	Slider(const ax::Rect& rect, const Events& events, const Info& info, ax::util::Flag flags = 0);

	ax::Window::Backbone* GetCopy();

//	void SetBackgroundAlpha(const float& alpha)
//	{
//		_bg_alpha = alpha;
//	}

	void ResizeSlider(const ax::Size& size)
	{
		widget::Component* widget = static_cast<widget::Component*>(win->component.Get("Widget").get());
		ax::Slider::Info* info = static_cast<ax::Slider::Info*>(widget->GetInfo());
		
		win->dimension.SetSize(size);
		_sliderYPos = int((size.w - info->slider_width) * 0.5);
		_btnYPos = int((size.w - info->btn_size.w) * 0.5);
	}

	double GetValue() const
	{
		return _sliderValue;
	}

	void SetValue(const double& value);

	ax::util::Flag GetFlags() const
	{
		return _flags;
	}

protected:
	Events _events;
//	Info _info;
	//	ax::util::Flag _flag;
	ax::Color _currentBgColor, _currentSliderColor;

	std::shared_ptr<ax::Image> _btnImg;
	ax::util::Flag _flags;

	int _nCurrentImg, _sliderPosition, _btnYPos, _sliderYPos, _delta_click;
//	float _bg_alpha;
	double _sliderValue;

	enum axButtonState { axBTN_NORMAL, axBTN_HOVER, axBTN_DOWN };

	void blockSliderPosition(const ax::Point& pos);
	void updateSliderValue();

	void DrawVerticalSlider(ax::GC* gc, const ax::Rect& rect0);
	void DrawLineBehindSlider_Vertical(ax::GC* gc, const ax::Rect& rect0);

	void OnPaint(ax::GC gc);
	void OnMouseEnter(const ax::Point& pos);
	void OnMouseLeftDown(const ax::Point& pos);
	void OnMouseLeftUp(const ax::Point& pos);
	void OnMouseMotion(const ax::Point& pos);
	void OnMouseLeftDragging(const ax::Point& pos);
	void OnMouseLeave(const ax::Point& pos);

	void OnResize(const ax::Size& size);
};
}

/// @}
/// @}
#endif // __AX_SLIDER_H__
