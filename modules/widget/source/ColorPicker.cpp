//
//  ColorPicker.cpp
//  ProjectExample
//
//  Created by Alexandre Arsenault on 2016-04-06.
//  Copyright © 2016 Alexandre Arsenault. All rights reserved.
//

#include "ColorPicker.hpp"

namespace ax {
ColorPicker::Info::Info()
{
}

ColorPicker::ColorPicker(const ax::Point& position, const ax::ColorPicker::Events& events,
	const ax::ColorPicker::Info& info, const ax::Color& color)
	: _color(color)
	, _font(0)
{
	const ax::Size size(205, 272);
	win = ax::Window::Create(ax::Rect(position, size));
	win->event.OnPaint = ax::WBind<ax::GC>(this, &ColorPicker::OnPaint);


	if(events.select) {
		win->AddConnection(Events::SELECT, events.select);
	}
	
	if(events.cancel) {
		win->AddConnection(Events::CANCEL, events.cancel);
	}

	const ax::Size sld_size(140, 20);
	ax::Point pos(22, 120);

	ax::event::Function sld_fcts[4]
		= { GetOnRedSlider(), GetOnGreenSlider(), GetOnBlueSlider(), GetOnAlphaSlider() };

	for (int i = 0; i <= ALPHA; i++) {
		auto sld = ax::shared<ax::Slider>(
			ax::Rect(pos, sld_size), sld_fcts[i], info.sld_info, ax::Slider::Flags::CLICK_ANYWHERE);
		win->node.Add(sld);
		pos = sld->GetWindow()->dimension.GetRect().GetNextPosDown(10);
		sld->SetValue(GetColor(i));
		_sliders[i] = sld.get();
	}

	//	ax::TextBox::Info txtInfo;
	//	txtInfo.normal = ax::Color(0.97);
	//	txtInfo.hover = txtInfo.normal;
	//	txtInfo.selected = txtInfo.normal;
	//	txtInfo.highlight = ax::Color(0.4f, 0.4f, 0.6f, 0.2f);
	//	txtInfo.contour = ax::Color(0.88);
	//	txtInfo.cursor = ax::Color(1.0f, 0.0f, 0.0f);
	//	txtInfo.selected_shadow = ax::Color(0.8f, 0.8f, 0.8f);
	//	txtInfo.font_color = ax::Color(0.0);

	ax::event::Function txt_fcts[4] = { GetOnRedTxt(), GetOnGreenTxt(), GetOnBlueTxt(), GetOnAlphaTxt() };

	ax::TextBox::Events txt_evts;

	for (int i = 0; i <= ALPHA; i++) {
		txt_evts.enter_click = txt_fcts[i];

		const ax::Point txt_pos(
			_sliders[i]->GetWindow()->dimension.GetRect().GetNextPosRight(5) - ax::Point(0, 3));

		auto txt_box(ax::shared<ax::TextBox>(ax::Rect(txt_pos, ax::Size(30, 25)), txt_evts, info.txt_info, "",
			std::to_string(int(GetColor(i) * 255.0))));

		win->node.Add(txt_box);
		_txt_boxes[i] = txt_box.get();
	}

	//	ax::Button::Info btn_info;
	//	btn_info.normal = ax::Color(0.97);
	//	btn_info.hover = ax::Color(0.99);
	//	btn_info.clicking = ax::Color(0.96);
	//	btn_info.selected = btn_info.normal;
	//	btn_info.contour = ax::Color(0.88);
	//	btn_info.font_color = ax::Color(0.0);
	//	btn_info.corner_radius = 0;

	ax::Point btn_pos(10, size.h - 32);
	const ax::Size btn_size(88, 25);
	auto ok_btn
		= ax::shared<ax::Button>(ax::Rect(btn_pos, btn_size), GetOnSelect(), info.btn_info, "", "Select");
	win->node.Add(ok_btn);

	btn_pos.x = size.w - btn_size.w - 10;
	auto cancel_btn
		= ax::shared<ax::Button>(ax::Rect(btn_pos, btn_size), GetOnCancel(), info.btn_info, "", "Cancel");
	win->node.Add(cancel_btn);
}

void ColorPicker::OnRedSlider(const ax::Slider::Msg& msg)
{
	double v = msg.GetValue();
	_color.SetRed(v);
	_txt_boxes[0]->SetLabel(std::to_string(int(v * 255.0)));
	win->Update();
}

void ColorPicker::OnGreenSlider(const ax::Slider::Msg& msg)
{
	double v = msg.GetValue();
	_color.SetGreen(v);
	_txt_boxes[1]->SetLabel(std::to_string(int(v * 255.0)));
	win->Update();
}

void ColorPicker::OnBlueSlider(const ax::Slider::Msg& msg)
{
	double v = msg.GetValue();
	_color.SetBlue(v);
	_txt_boxes[2]->SetLabel(std::to_string(int(v * 255.0)));
	win->Update();
}

void ColorPicker::OnAlphaSlider(const ax::Slider::Msg& msg)
{
	double v = msg.GetValue();
	_color.SetAlpha(v);
	_txt_boxes[3]->SetLabel(std::to_string(int(v * 255.0)));
	win->Update();
}

void ColorPicker::SetColor(ColorIndex index, double v)
{
	switch (index) {
	case RED:
		_color.SetRed(v);
		break;
	case GREEN:
		_color.SetGreen(v);
		break;
	case BLUE:
		_color.SetBlue(v);
		break;
	case ALPHA:
		_color.SetAlpha(v);
		break;
	}
}

double ColorPicker::GetColor(int index)
{
	switch (index) {
	case RED:
		return _color.GetRed();
	case GREEN:
		return _color.GetGreen();
	case BLUE:
		return _color.GetBlue();
	case ALPHA:
		return _color.GetAlpha();
	}

	return 0.0;
}

void ColorPicker::TextBoxEvent(ColorIndex index, const std::string& txt)
{
	double v = GetColor(index);
	try {
		v = std::stod(txt);
		v = ax::util::Clamp(v, 0.0, 255.0);
		_txt_boxes[index]->SetLabel(std::to_string(int(v)));

		v /= 255.0;

		SetColor(index, v);
		_sliders[index]->SetValue(v);
		win->Update();
	}
	catch (std::invalid_argument& e) {
		_txt_boxes[index]->SetLabel(std::to_string(int(v * 255.0)));
		win->Update();
	}
}

void ColorPicker::OnRedTxt(const ax::TextBox::Msg& msg)
{
	TextBoxEvent(RED, msg.GetMsg());
}

void ColorPicker::OnGreenTxt(const ax::TextBox::Msg& msg)
{
	TextBoxEvent(GREEN, msg.GetMsg());
}

void ColorPicker::OnBlueTxt(const ax::TextBox::Msg& msg)
{
	TextBoxEvent(BLUE, msg.GetMsg());
}

void ColorPicker::OnAlphaTxt(const ax::TextBox::Msg& msg)
{
	TextBoxEvent(ALPHA, msg.GetMsg());
}

void ColorPicker::OnSelect(const ax::Button::Msg& msg)
{
	win->PushEvent(Events::SELECT, new Msg(_color));
}

void ColorPicker::OnCancel(const ax::Button::Msg& msg)
{
	win->PushEvent(Events::CANCEL, new Msg(_color));
}

void ColorPicker::OnPaint(ax::GC gc)
{
	const ax::Rect rect(win->dimension.GetDrawingRect());
	gc.SetColor(ax::Color(0.97));
	gc.DrawRectangle(rect);

	const ax::Rect color_rect(8, 8, rect.size.w - 14, 100);

	// Draw color rectangle background.
	int line_index = 0;
	for (int y = color_rect.position.y; y < color_rect.position.y + color_rect.size.h; y += 5) {
		for (int x = color_rect.position.x; x < color_rect.position.x + color_rect.size.w - 5; x += 10) {
			int xx = x;
			int sx = 5;

			if (xx + 10 > color_rect.position.x + color_rect.size.w) {
				sx = (xx + 10) - (color_rect.position.x + color_rect.size.w);
			}

			if (line_index % 2) {
				gc.SetColor(ax::Color(0.8));
				gc.DrawRectangle(ax::Rect(xx, y, 5, 5));
				gc.SetColor(ax::Color(0.9));
				gc.DrawRectangle(ax::Rect(xx + 5, y, sx, 5));
			}
			else {
				gc.SetColor(ax::Color(0.9));
				gc.DrawRectangle(ax::Rect(xx, y, 5, 5));
				gc.SetColor(ax::Color(0.8));
				gc.DrawRectangle(ax::Rect(xx + 5, y, sx, 5));
			}
		}

		line_index++;
	}

	// Draw color rectangle.
	gc.SetColor(_color);
	gc.DrawRectangle(color_rect);
	gc.SetColor(ax::Color(0.6));
	gc.DrawRectangleContour(color_rect);

	ax::Point red_pos(color_rect.GetNextPosDown(13));
	gc.SetColor(ax::Color(0.0));

	// Draw color labels.
	gc.DrawString(_font, "R", red_pos);
	gc.DrawString(_font, "G", red_pos + ax::Point(0, 30));
	gc.DrawString(_font, "B", red_pos + ax::Point(0, 60));
	gc.DrawString(_font, "A", red_pos + ax::Point(0, 90));

	gc.SetColor(ax::Color(0.6));
	gc.DrawRectangleContour(rect);
}
}
