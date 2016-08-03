///*
// * Copyright (c) 2016 Alexandre Arsenault.
// *
// * This file is part of OpenAX.
// *
// * OpenAX is free or commercial software: you can redistribute it and/or
// * modify it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 or any later version of the
// * license or use a commercial OpenAX License.
// *
// * OpenAX is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with OpenAX. If not, see <http://www.gnu.org/licenses/>.
// *
// * To release a closed-source product which uses OpenAX, commercial
// * licenses are available, email ax.frameworks@gmail.com for more information.
// */
//
//#include "DropMenu.hpp"
//
//#define ITEM_NONE_SELECTED -1
//#define ITEM_SCROLL_UP -2
//#define ITEM_SCROLL_DOWN -3
///*
// * ax::DropMenu::Flags.
// */
//const ax::Flag ax::DropMenu::Flags::TEXT_ALIGN_CENTER = ax::FlagValue::FLAG_1;
//const ax::Flag ax::DropMenu::Flags::TEXT_ALIGN_RIGHT = ax::FlagValue::FLAG_2;
//
///*
// * ax::DropMenu::Msg.
// */
//ax::DropMenu::Msg::Msg()
//{
//	_sender = nullptr;
//}
//
//ax::DropMenu::Msg::Msg(ax::DropMenu* sender, const std::string& item, int index)
//	: _sender(sender)
//	, _item(item)
//	, _index(index)
//{
//}
//
//ax::DropMenu* ax::DropMenu::Msg::GetSender() const
//{
//	return _sender;
//}
//
//std::string ax::DropMenu::Msg::GetItem() const
//{
//	return _item;
//}
//
//int ax::DropMenu::Msg::GetIndex() const
//{
//	return _index;
//}
//
//ax::Event::Msg* ax::DropMenu::Msg::GetCopy()
//{
////	ax::Print("ax::DropMenu::Msg::GetCopy()");
//	return new ax::DropMenu::Msg(*this);
//}
//
///*
// * ax::DropMenu::Info.
// */
//ax::DropMenu::Info::Info()
//	: ax::widget::Info()
//	, normal(0.5)
//	, hover(0.6)
//	, font_color(0.0)
//	, selected(0.7)
//	, selected_hover(0.8)
//	, selected_font_color(0.0)
//	, contour(0.0)
//	, separation(0.0)
//	, up_down_arrow(0.0)
//	, right_arrow(0.0)
//
//{
//}
//
///*
// * ax::DropMenu::DropMenu.
// */
//ax::DropMenu::DropMenu(const ax::Rect& rect, const ax::DropMenu::Events& events,
//	const ax::DropMenu::Info& info, const std::vector<std::string>& items,
//	ax::Flag flags)
//	: _events(events)
//	, _flags(flags)
//	, _selected_item(-1)
//	, _mouse_hover_item(-1)
//
//{
//	for (int i = 0; i < items.size(); i++) {
//		if (items[i].empty()) {
//			_separator_index.push_back((int)_items.size());
//		}
//		else if (items[i] == ">") {
//			// Arrow at index 0 is ignore.
//			_right_arrow_index.push_back((int)_items.size() - 1);
//		}
//		else {
//			_items.push_back(items[i]);
//		}
//	}
//
//	ax::Rect new_rect(rect);
//
//	if (_items.size()) {
//		int total_height = (int)_items.size() * info.item_height;
//
//		// Too many items for menu max height.
//		if (total_height > rect.size.y) {
//			int n_item = rect.size.y / info.item_height;
//			_n_shown_item = n_item - 1;
//			_over_flow = true;
//			_over_flow_up = false;
//			_over_flow_down = true;
//			_top_item_index = 0;
//
//			new_rect.size.y = n_item * info.item_height;
//		}
//		else {
//			_over_flow = false;
//			_over_flow_up = false;
//			_over_flow_down = false;
//			_n_shown_item = (int)_items.size();
//			_top_item_index = 0;
//
//			new_rect.size.y = (int)_items.size() * info.item_height;
//		}
//	}
//
//	win = ax::Window::Create(new_rect);
//
//	// Builtin event connection.
//	win->event.OnPaint = ax::WBind<ax::GC>(this, &DropMenu::OnPaint);
//
//	win->event.OnMouseLeftDown
//		= ax::WBind<ax::Point>(this, &DropMenu::OnMouseLeftDown);
//	win->event.OnMouseLeftUp
//		= ax::WBind<ax::Point>(this, &DropMenu::OnMouseLeftUp);
//	win->event.OnMouseEnter
//		= ax::WBind<ax::Point>(this, &DropMenu::OnMouseEnter);
//	win->event.OnMouseLeave
//		= ax::WBind<ax::Point>(this, &DropMenu::OnMouseLeave);
//	win->event.OnMouseMotion
//		= ax::WBind<ax::Point>(this, &DropMenu::OnMouseMotion);
//
//	if (_events.item_click) {
//		win->AddConnection(DropMenu::Events::ITEM_CLICK, _events.item_click);
//	}
//
////	ax::Print("new ax::DropMenu::win->component");
//	win->component.Add("Widget", widget::Component::Ptr(new widget::Component(
//									 win, new ax::DropMenu::Info(info))));
//
//	if (info.font_path.empty()) {
//		_font = ax::unique<ax::Font>(0);
//		_font->SetFontSize(info.font_size);
//	}
//	else {
//		_font = ax::unique<ax::Font>(info.font_path);
//
//		if (!_font->IsFontReady()) {
//			_font = ax::unique<ax::Font>(0);
//		}
//
//		_font->SetFontSize(info.font_size);
//	}
//
//	_up_img = ax::unique<ax::Image>("resources/drop_up.png");
//	_down_img = ax::unique<ax::Image>("resources/drop_down.png");
//	_right_img = ax::unique<ax::Image>("resources/drop_right.png");
//}
//
//const std::vector<std::string>& ax::DropMenu::GetItems() const
//{
//	return _items;
//}
//
//int ax::DropMenu::GetSelectedItemIndex() const
//{
//	return _selected_item;
//}
//
//std::string ax::DropMenu::GetSelectedItem() const
//{
//	if (_selected_item < 0) {
//		return "";
//	}
//
//	return _items[_selected_item];
//}
//
//void ax::DropMenu::SetSelectedItem(const int& index)
//{
//	if (index >= (int)_items.size()) {
//		ax::Error("ax::DropMenu::SetSelectedItem -> Index out of bound.");
//		return;
//	}
//
//	_selected_item = index;
//	win->Update();
//}
//
//int ax::DropMenu::MousePosToIndex(const ax::Point& pos)
//{
//	widget::Component::Ptr widget
//		= win->component.Get<widget::Component>("Widget");
//	ax::DropMenu::Info* info
//		= static_cast<ax::DropMenu::Info*>(widget->GetInfo());
//
//	if (pos.y < 0) {
//		return ITEM_NONE_SELECTED;
//	}
//
//	if (pos.y > win->dimension.GetRect().size.y) {
//		return ITEM_NONE_SELECTED;
//	}
//
//	int index = pos.y / info->item_height;
//
//	if (_over_flow) {
//		if (_over_flow_down && _over_flow_up) {
//			// Mouse over scroll up.
//			if (index == 0) {
//				return ITEM_SCROLL_UP;
//			}
//
//			// Mouse over scroll down.
//			if (index == _n_shown_item + 1) {
//				return ITEM_SCROLL_DOWN;
//			}
//
//			return _top_item_index + index - 1;
//		}
//		else if (_over_flow_down) {
//			// Mouse over scroll down.
//			if (index == _n_shown_item) {
//				return ITEM_SCROLL_DOWN;
//			}
//			return _top_item_index + index;
//		}
//		else if (_over_flow_up) {
//			// Mouse over scroll up.
//			if (index == 0) {
//				return ITEM_SCROLL_UP;
//			}
//			return _top_item_index + index - 1;
//		}
//		else {
//			ax::Error("ax::DropMenu::MousePosToIndex -> Should never happen.");
//		}
//	}
//
//	// No overflow.
//	return index;
//}
//
//void ax::DropMenu::OnMouseLeftDown(const ax::Point& pos)
//{
//	const ax::Point mpos(pos - win->dimension.GetAbsoluteRect().position);
//
//	int i = MousePosToIndex(mpos);
//
//	if (i == ITEM_NONE_SELECTED) {
//		return;
//	}
//
//	if (_over_flow && (i < ITEM_NONE_SELECTED)) {
//		if (_over_flow_down && _over_flow_up && (i == ITEM_SCROLL_UP)) {
//			if (_top_item_index == 1) {
//				_top_item_index = 0;
//				_over_flow_up = false;
//				_n_shown_item++;
//				_mouse_hover_item = 0;
//				win->Update();
//				return;
//			}
//
//			_top_item_index--;
//			win->Update();
//			return;
//		}
//		else if (_over_flow_down && _over_flow_up && (i == ITEM_SCROLL_DOWN)) {
//			if ((_top_item_index + 1) + _n_shown_item == (int)_items.size()) {
//				_over_flow_down = false;
//				_n_shown_item++;
//				_mouse_hover_item = (int)_items.size() - 1;
//				win->Update();
//				return;
//			}
//
//			_top_item_index++;
//			win->Update();
//			return;
//		}
//		else if (_over_flow_down && (i == ITEM_SCROLL_DOWN)) {
//			if (_top_item_index == 0) {
//				_top_item_index++;
//				_over_flow_up = true;
//				_n_shown_item--;
//				win->Update();
//				return;
//			}
//
//			ax::Error("ax::DropMenu::OnMouseLeftDown -> Should not happen (down)");
//			_top_item_index++;
//			win->Update();
//			return;
//		}
//		else if (_over_flow_up && (i == ITEM_SCROLL_UP)) {
//			_over_flow_down = true;
//			_n_shown_item--;
//			win->Update();
//			return;
//		}
//
//		ax::Error("ax::DropMenu::OnMouseLeftDown -> Should never happen.");
//		return;
//	}
//
////	if (i != _selected_item) {
//		_selected_item = i;
////		ax::Print("new ax::DropMenu::win->PushEvent");
//		win->PushEvent(
//			Events::ITEM_CLICK, new ax::DropMenu::Msg(this, _items[i], i));
//		win->Update();
////	}
//}
//
//void ax::DropMenu::OnMouseLeftUp(const ax::Point& pos)
//{
//}
//
//void ax::DropMenu::OnMouseMotion(const ax::Point& pos)
//{
//	const ax::Point mpos(pos - win->dimension.GetAbsoluteRect().position);
//	_mouse_hover_item = MousePosToIndex(mpos);
//	win->Update();
//}
//
//void ax::DropMenu::OnMouseEnter(const ax::Point& pos)
//{
//}
//
//void ax::DropMenu::OnMouseLeave(const ax::Point& pos)
//{
//	_mouse_hover_item = ITEM_NONE_SELECTED;
//	win->Update();
//}
//
//void ax::DropMenu::OnPaint(ax::GC gc)
//{
//	const ax::Rect rect(win->dimension.GetDrawingRect());
//
//	widget::Component::Ptr widget
//		= win->component.Get<widget::Component>("Widget");
//	ax::DropMenu::Info* info
//		= static_cast<ax::DropMenu::Info*>(widget->GetInfo());
//
//	gc.SetColor(ax::Color(255, 0, 0));
//	gc.DrawRectangle(rect);
//
//	ax::Point txt_delta(5, 3);
//
//	struct MenuDraw {
//		ax::Color bg_color;
//		ax::Color txt_color;
//		std::string txt;
//	};
//
//	std::vector<MenuDraw> draw_info(_items.size());
//
//	for (int i = 0; i < _items.size(); i++) {
//		draw_info[i].txt = _items[i];
//
//		if (i == _selected_item && i == _mouse_hover_item) {
//			draw_info[i].bg_color = info->selected_hover;
//			draw_info[i].txt_color = info->selected_font_color;
//		}
//		else if (i == _selected_item) {
//			draw_info[i].bg_color = info->selected;
//			draw_info[i].txt_color = info->selected_font_color;
//		}
//		else if (i == _mouse_hover_item) {
//			draw_info[i].bg_color = info->hover;
//			draw_info[i].txt_color = info->font_color;
//		}
//		else {
//			draw_info[i].bg_color = info->normal;
//			draw_info[i].txt_color = info->font_color;
//		}
//	}
//
//	std::function<void(ax::Font&, const std::string&, const ax::Rect&)>
//		draw_string;
//
//	if (ax::IsFlag(Flags::TEXT_ALIGN_CENTER, _flags)) {
//		draw_string = [&](
//			ax::Font& font, const std::string& text, const ax::Rect& s_rect) {
//			gc.DrawStringAlignedCenter(font, text, s_rect);
//		};
//	}
//	else if (ax::IsFlag(Flags::TEXT_ALIGN_RIGHT, _flags)) {
//		draw_string = [&](
//			ax::Font& font, const std::string& text, const ax::Rect& s_rect) {
//			gc.DrawStringAlignedRight(font, text, s_rect);
//		};
//	}
//	else {
//		draw_string = [&](
//			ax::Font& font, const std::string& text, const ax::Rect& s_rect) {
//			gc.DrawStringAlignedLeft(font, text, s_rect);
//		};
//	}
//
//	int index_offset = 0;
//
//	if (_over_flow) {
//		if (_over_flow_up && _over_flow_down) {
//			index_offset = 1;
//			// Up.
//			ax::Rect up_rect(0, 0, rect.size.x, info->item_height);
//			if (_mouse_hover_item == ITEM_SCROLL_UP) {
//				gc.SetColor(info->hover);
//			}
//			else {
//				gc.SetColor(info->normal);
//			}
//
//			gc.DrawRectangle(up_rect);
//
//			ax::Size u_img_s = _up_img->GetSize();
//			ax::Point img_pos(
//				up_rect.position.x + (up_rect.size.x - u_img_s.x) * 0.5,
//				up_rect.position.y + (up_rect.size.y - u_img_s.y) * 0.5);
//
//			gc.DrawImageColor(_up_img.get(), img_pos, info->up_down_arrow);
//
//			// Down.
//			int y = (_n_shown_item + 1) * info->item_height;
//			ax::Rect down_rect(0, y, rect.size.x, info->item_height);
//			if (_mouse_hover_item == ITEM_SCROLL_DOWN) {
//				gc.SetColor(info->hover);
//			}
//			else {
//				gc.SetColor(info->normal);
//			}
//			gc.DrawRectangle(down_rect);
//
//			ax::Size d_img_s = _down_img->GetSize();
//			ax::Point d_img_pos(
//				down_rect.position.x + (down_rect.size.x - d_img_s.x) * 0.5,
//				down_rect.position.y + (down_rect.size.y - d_img_s.y) * 0.5);
//
//			gc.DrawImageColor(_down_img.get(), d_img_pos, info->up_down_arrow);
//		}
//		else if (_over_flow_up) {
//			index_offset = 1;
//			ax::Rect up_rect(0, 0, rect.size.x, info->item_height);
//			if (_mouse_hover_item == ITEM_SCROLL_UP) {
//				gc.SetColor(info->hover);
//			}
//			else {
//				gc.SetColor(info->normal);
//			}
//			gc.DrawRectangle(up_rect);
//
//			ax::Size u_img_s = _up_img->GetSize();
//			ax::Point u_img_pos(
//				up_rect.position.x + (up_rect.size.x - u_img_s.x) * 0.5,
//				up_rect.position.y + (up_rect.size.y - u_img_s.y) * 0.5);
//
//			gc.DrawImageColor(_up_img.get(), u_img_pos, info->up_down_arrow);
//		}
//		else if (_over_flow_down) {
//			int y = _n_shown_item * info->item_height;
//			ax::Rect down_rect(0, y, rect.size.x, info->item_height);
//			if (_mouse_hover_item == ITEM_SCROLL_DOWN) {
//				gc.SetColor(info->hover);
//			}
//			else {
//				gc.SetColor(info->normal);
//			}
//			gc.DrawRectangle(down_rect);
//
//			ax::Size d_img_s = _down_img->GetSize();
//			ax::Point d_img_pos(
//				down_rect.position.x + (down_rect.size.x - d_img_s.x) * 0.5,
//				down_rect.position.y + (down_rect.size.y - d_img_s.y) * 0.5);
//
//			gc.DrawImageColor(_down_img.get(), d_img_pos, info->up_down_arrow);
//		}
//		else {
//			ax::Error("ax::DropMenu::OnPaint -> Should not happen (draw)");
//		}
//
//		//		for (int i = 0; i < _n_shown_item; i++) {
//		//			int index = i + _top_item_index;
//		//			int y = (i + index_offset) * info->item_height;
//		//			ax::Rect item_rect = ax::Rect(0, y, rect.size.x,
//		// info->item_height);
//		//			gc.SetColor(draw_info[index].bg_color);
//		//			gc.DrawRectangle(item_rect);
//		//			gc.SetColor(draw_info[index].txt_color);
//		//			draw_string(*_font.get(), draw_info[index].txt, item_rect);
//		//
//		//			// Draw right arrow.
//		//			for (auto& n : _right_arrow_index) {
//		//				if (index == n) {
//		//					ax::Size img_s = _right_img->GetSize();
//		//					ax::Point img_pos(
//		//						item_rect.position.x + (item_rect.size.x -
//		// img_s.x),
//		//						item_rect.position.y
//		//							+ (item_rect.size.y - img_s.y) * 0.5);
//		//
//		//					gc.DrawImageColor(_right_img.get(), img_pos,
//		// ax::Color(0.5));
//		//					break;
//		//				}
//		//			}
//		//
//		//			// Draw separation.
//		//			for (auto& n : _separator_index) {
//		//				if (index == n) {
//		//					gc.SetColor(info->separation);
//		//					gc.DrawLine(ax::Point(0, y), ax::Point(rect.size.x,
//		// y));
//		//					break;
//		//				}
//		//			}
//		//		}
//	}
//	// No overflow.
//	//	else {
//	//		for (int i = 0; i < draw_info.size(); i++) {
//	//			int y = i * info->item_height;
//	//			ax::Rect item_rect = ax::Rect(0, y, rect.size.x,
//	// info->item_height);
//	//			gc.SetColor(draw_info[i].bg_color);
//	//			gc.DrawRectangle(item_rect);
//	//			gc.SetColor(draw_info[i].txt_color);
//	//			draw_string(*_font.get(), draw_info[i].txt, item_rect);
//	//
//	//			// Draw right arrow.
//	//			for (auto& n : _right_arrow_index) {
//	//				if (i == n) {
//	//					ax::Size img_s = _right_img->GetSize();
//	//					ax::Point img_pos(
//	//						item_rect.position.x + (item_rect.size.x - img_s.x),
//	//						item_rect.position.y
//	//							+ (item_rect.size.y - img_s.y) * 0.5);
//	//
//	////					gc.DrawImage(_right_img.get(), img_pos);
//	//					gc.DrawImageColor(_right_img.get(), img_pos,
//	//ax::Color(1.0f,
//	// 0.0f, 0.0f));
//	//					break;
//	//				}
//	//			}
//	//
//	//			// Draw separation.
//	//			for (auto& n : _separator_index) {
//	//				if (i == n) {
//	//					gc.SetColor(info->separation);
//	//					gc.DrawLine(ax::Point(0, y), ax::Point(rect.size.x, y));
//	//					break;
//	//				}
//	//			}
//	//		}
//	//	}
//
//	for (int i = 0; i < _n_shown_item; i++) {
//		int index = i + _top_item_index;
//		int y = (i + index_offset) * info->item_height;
//		ax::Rect item_rect = ax::Rect(0, y, rect.size.x, info->item_height);
//		gc.SetColor(draw_info[index].bg_color);
//		gc.DrawRectangle(item_rect);
//		gc.SetColor(draw_info[index].txt_color);
//		draw_string(*_font.get(), draw_info[index].txt, item_rect);
//
//		// Draw right arrow.
//		for (auto& n : _right_arrow_index) {
//			if (index == n) {
//				ax::Size img_s = _right_img->GetSize();
//				ax::Point img_pos(
//					item_rect.position.x + (item_rect.size.x - img_s.x),
//					item_rect.position.y + (item_rect.size.y - img_s.y) * 0.5);
//
//				gc.DrawImageColor(_right_img.get(), img_pos, info->right_arrow);
//				break;
//			}
//		}
//
//		// Draw separation.
//		for (auto& n : _separator_index) {
//			if (index == n) {
//				gc.SetColor(info->separation);
//				gc.DrawLine(ax::Point(0, y), ax::Point(rect.size.x, y));
//				break;
//			}
//		}
//	}
//
//	gc.SetColor(info->contour);
//	gc.DrawRectangleContour(rect);
//}
