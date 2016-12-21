#ifndef __AX_NUMBER_SCROLL_H__
#define __AX_NUMBER_SCROLL_H__

#include "axlib.hpp"
#include "Button.hpp"
#include "TextBox.hpp"

namespace ax {
class NumberScroll : public ax::Window::Backbone {
public:
	class Msg : public ax::event::Msg {
	public:
		Msg(const double& value, ax::util::Control::Type type);

		double GetValue() const;

		ax::util::Control::Type GetType() const;

		ax::event::Msg* GetCopy();

	private:
		double _value;
		ax::util::Control::Type _type;
	};

	/*
	 * ax::ScrollNumber::Events.
	 */
	class Events {
	public:
		enum : ax::event::Id { VALUE_CHANGE };

		Events()
		{
		}

		Events(const ax::event::Function& fct)
		{
			value_change = fct;
		}

		ax::event::Function value_change;
	};

	class Info : public ax::widget::Info {
	public:
		Info();

		//		/// Info needed for debug editor. Derived from axInfo.
		//		virtual ax::StringVector GetParamNameList() const;
		//
		//		virtual std::string GetAttributeValue(const std::string& name);
		//
		//		virtual void SetAttribute(const std::pair<std::string, std::string>& attribute);
		//
		//		virtual std::vector<widget::ParamInfo> GetParametersInfo() const;

		std::string up_btn;
		std::string down_btn;
		ax::Button::Info btn_info;
		ax::TextBox::Info txt_info;
	};

	NumberScroll(const ax::Rect& rect, const NumberScroll::Events& events, const ax::NumberScroll::Info& info,
		double value, ax::util::Control::Type type = ax::util::Control::Type::REAL,
		const ax::util::Range2D<double>& range = ax::util::Range2D<double>(0.0, 1.0), double increment = 0.1);

	void SetValue(double value);

	double GetValue() const;

private:
	double _value;
	ax::util::Control::Type _type;
	ax::util::Range2D<double> _range;
	double _increment;

	ax::Button* _btn_up;
	ax::Button* _btn_down;
	ax::TextBox* _txtbox;

	axEVENT_DECLARATION(ax::Button::Msg, OnButtonUp);
	axEVENT_DECLARATION(ax::Button::Msg, OnButtonDown);
	axEVENT_DECLARATION(ax::TextBox::Msg, OnTextEnter);

	void OnResize(const ax::Size& size);
	void OnPaint(ax::GC gc);
};
}

#endif // __AX_NUMBER_SCROLL_H__
