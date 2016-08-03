//#include "NumberScroll.hpp"
//
//#include "Button.hpp"
//#include "TextBox.hpp"
//
//namespace ax {
///*
// * ax::NumberScroll::Msg.
// */
//NumberScroll::Msg::Msg(const double& value, ax::Utils::Control::Type type)
//	: _value(value)
//	, _type(type)
//{
//}
//
//double NumberScroll::Msg::GetValue() const
//{
//	return _value;
//}
//
//ax::Utils::Control::Type NumberScroll::Msg::GetType() const
//{
//	return _type;
//}
//
//ax::Event::Msg* NumberScroll::Msg::GetCopy()
//{
//	return new Msg(*this);
//}
//
//NumberScroll::Info::Info()
//{
//	
//}
//
//NumberScroll::NumberScroll(const ax::Rect& rect, const NumberScroll::Events& events, const ax::NumberScroll::Info& info, double value,
//	ax::Utils::Control::Type type, const ax::Utils::Range<double>& range, double increment)
//	: _value(value)
//	, _type(type)
//	, _range(range)
//	, _increment(increment)
//{
//	win = ax::Window::Create(rect);
//	win->event.OnPaint = ax::WBind<ax::GC>(this, &NumberScroll::OnPaint);
//	win->event.OnResize = ax::WBind<ax::Size>(this, &NumberScroll::OnResize);
//
//	if (events.value_change) {
//		win->AddConnection(Events::VALUE_CHANGE, events.value_change);
//	}
//
////	ax::TextBox::Info txtInfo;
////	txtInfo.normal = ax::Color(1.0);
////	txtInfo.hover = ax::Color(1.0);
////	txtInfo.selected = ax::Color(1.0);
////	txtInfo.highlight = ax::Color(0.4f, 0.4f, 0.6f, 0.2f);
////	txtInfo.contour = ax::Color(0.7);
////	txtInfo.cursor = ax::Color(1.0f, 0.0f, 0.0f);
////	txtInfo.selected_shadow = ax::Color(0.8f, 0.8f, 0.8f);
////	txtInfo.font_color = ax::Color(0.0);
//
//	ax::TextBox::Events txt_evts;
//	txt_evts.enter_click = GetOnTextEnter();
//
//	_value = ax::Utils::Clamp(_value, _range.left, _range.right);
//
//	std::string v_str;
//	switch (_type) {
//	case ax::Utils::Control::Type::INTEGER:
//		v_str = std::to_string((int)_value);
//		break;
//	default:
//		v_str = std::to_string(_value);
//	}
//
//	auto txt_box = ax::shared<ax::TextBox>(
//		ax::Rect(ax::Point(0, 0), ax::Size(rect.size.x - 19, rect.size.y)), txt_evts, info.txt_info, "", v_str);
//
//	win->node.Add(txt_box);
//	_txtbox = txt_box.get();
//
////	ax::Button::Info btn_info;
////	btn_info.normal = ax::Color(0.85);
////	btn_info.hover = ax::Color(0.86);
////	btn_info.clicking = ax::Color(0.83);
////	btn_info.selected = btn_info.normal;
////	btn_info.contour = ax::Color(0.7);
////	btn_info.font_color = ax::Color(0.0, 0.0);
//
//	auto btn_top = ax::shared<ax::Button>(
//		ax::Rect(ax::Point(rect.size.x - 20, 0), ax::Size(20, rect.size.y / 2 + 1)), GetOnButtonUp(),
//		info.btn_info, info.up_btn, "", ax::Button::Flags::SINGLE_IMG | ax::Button::Flags::IMG_RESIZE);
//	
//	win->node.Add(btn_top);
//	_btn_up = btn_top.get();
//
//	ax::Point btn_pos(btn_top->GetWindow()->dimension.GetRect().GetNextPosDown(0));
//	int size_y = rect.size.y - btn_pos.y + 1;
//	btn_pos.y--;
//
//	auto btn_bottom = ax::shared<ax::Button>(ax::Rect(btn_pos, ax::Size(20, size_y)), GetOnButtonDown(),
//		info.btn_info, info.down_btn, "", ax::Button::Flags::SINGLE_IMG | ax::Button::Flags::IMG_RESIZE);
//
//	win->node.Add(btn_bottom);
//	_btn_up = btn_bottom.get();
//}
//
//void NumberScroll::SetValue(double value)
//{
//	_value = ax::Utils::Clamp(value, _range.left, _range.right);
//
//	switch (_type) {
//	case ax::Utils::Control::Type::INTEGER:
//		_txtbox->SetLabel(std::to_string((int)_value));
//		break;
//
//	case ax::Utils::Control::Type::REAL:
//		_txtbox->SetLabel(std::to_string(_value));
//		break;
//
//	default:
//		_txtbox->SetLabel(std::to_string(_value));
//	}
//
//	win->PushEvent(Events::VALUE_CHANGE, new NumberScroll::Msg(_value, _type));
//}
//
//double NumberScroll::GetValue() const
//{
//	return std::stod(_txtbox->GetLabel());
//}
//
//void NumberScroll::OnButtonUp(const ax::Button::Msg& msg)
//{
//	_value += _increment;
//	SetValue(_value);
//}
//
//void NumberScroll::OnButtonDown(const ax::Button::Msg& msg)
//{
//	_value -= _increment;
//	SetValue(_value);
//}
//
//void NumberScroll::OnTextEnter(const ax::TextBox::Msg& msg)
//{
//	try {
//		double v = std::stod(msg.GetMsg());
//		SetValue(v);
//	}
//	catch (std::invalid_argument& e) {
//		SetValue(_value);
//	}
//}
//
//void NumberScroll::OnResize(const ax::Size& size)
//{
//	_txtbox->GetWindow()->dimension.SetSize(ax::Size(size.x - 20, size.y));
//	_btn_up->GetWindow()->dimension.SetSize(ax::Size(20, size.y / 2 + 1));
//
//	ax::Point btn_pos(_btn_up->GetWindow()->dimension.GetRect().GetNextPosDown(0));
//	int size_y = size.y - btn_pos.y + 1;
//	btn_pos.y--;
//
//	_btn_down->GetWindow()->dimension.SetSize(ax::Size(20, size_y));
//}
//
//void NumberScroll::OnPaint(ax::GC gc)
//{
//	const ax::Rect rect(win->dimension.GetDrawingRect());
//
//	gc.SetColor(ax::Color(0.94));
//	gc.DrawRectangle(rect);
//
//	gc.SetColor(ax::Color(0.94));
//	gc.DrawRectangleContour(rect);
//}
//}