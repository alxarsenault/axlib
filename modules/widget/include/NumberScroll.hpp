//#ifndef __AX_NUMBER_SCROLL_H__
//#define __AX_NUMBER_SCROLL_H__
//
//#include "axlib.hpp"
//#include "Button.hpp"
//#include "TextBox.hpp"
//
//namespace ax {
//class NumberScroll : public ax::Window::Backbone {
//public:
//	class Msg : public ax::Event::Msg {
//	public:
//		Msg(const double& value, ax::Utils::Control::Type type);
//		
//		double GetValue() const;
//		
//		ax::Utils::Control::Type GetType() const;
//		
//		ax::Event::Msg* GetCopy();
//		
//	private:
//		double _value;
//		ax::Utils::Control::Type _type;
//	};
//	
//	/*
//	 * ax::ScrollNumber::Events.
//	 */
//	class Events {
//	public:
//		enum : ax::Event::Id { VALUE_CHANGE };
//		
//		Events()
//		{
//		}
//		
//		Events(const ax::Event::Function& fct)
//		{
//			value_change = fct;
//		}
//		
//		ax::Event::Function value_change;
//	};
//	
//	class Info : public ax::widget::Info {
//	public:
//		Info();
//		
//		//		/// Info needed for debug editor. Derived from axInfo.
//		//		virtual ax::StringVector GetParamNameList() const;
//		//
//		//		virtual std::string GetAttributeValue(const std::string& name);
//		//
//		//		virtual void SetAttribute(const ax::StringPair& attribute);
//		//
//		//		virtual std::vector<widget::ParamInfo> GetParametersInfo() const;
//		
//		std::string up_btn;
//		std::string down_btn;
//		ax::Button::Info btn_info;
//		ax::TextBox::Info txt_info;
//	};
//
//	NumberScroll(const ax::Rect& rect, const NumberScroll::Events& events, const ax::NumberScroll::Info& info, double value,
//		ax::Utils::Control::Type type = ax::Utils::Control::Type::REAL,
//		const ax::Utils::Range<double>& range = ax::Utils::Range<double>(0.0, 1.0), double increment = 0.1);
//
//	
//
//	void SetValue(double value);
//	
//	double GetValue() const;
//
//private:
//	double _value;
//	ax::Utils::Control::Type _type;
//	ax::Utils::Range<double> _range;
//	double _increment;
//	
//	
//	ax::Button* _btn_up;
//	ax::Button* _btn_down;
//	ax::TextBox* _txtbox;
//
//	axEVENT_DECLARATION(ax::Button::Msg, OnButtonUp);
//	axEVENT_DECLARATION(ax::Button::Msg, OnButtonDown);
//	axEVENT_DECLARATION(ax::TextBox::Msg, OnTextEnter);
//
//	void OnResize(const ax::Size& size);
//	void OnPaint(ax::GC gc);
//};
//}
//
//#endif // __AX_NUMBER_SCROLL_H__
