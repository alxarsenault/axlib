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

#ifndef __AX_DROP_MENU_H__
#define __AX_DROP_MENU_H__

/*
 * @file    Dropmenu.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   DropMenu.
 * @date    30/01/2016
 */

/// @defgroup Widgets
/// @{

/// @defgroup DropMenu
/// @{

#include "axlib.hpp"
#include "Toggle.hpp"

namespace ax {

/*
 * ax::DropMenu.
 */
class DropMenu : public ax::Window::Backbone {
public:
	/*
	 * ax::DropMenu::Flags.
	 */
	class Flags {
	public:
		static const ax::util::Flag TEXT_ALIGN_CENTER;
		static const ax::util::Flag TEXT_ALIGN_RIGHT;
	};

	/*
	 * ax::DropMenu::Msg.
	 */
	class Msg : public ax::event::Msg {
	public:
		Msg();

		Msg(DropMenu* sender, const std::string& item, int index);

		DropMenu* GetSender() const;

		std::string GetItem() const;

		int GetIndex() const;

		ax::event::Msg* GetCopy();

	private:
		DropMenu* _sender;
		std::string _item;
		int _index;
	};

	/*
	 * ax::DropMenu::Events.
	 */
	class Events {
	public:
		enum : ax::event::Id { ITEM_CLICK };

		Events()
		{
		}

		Events(const ax::event::Function& fct)
		{
			item_click = fct;
		}

		ax::event::Function item_click;
	};

	/*
	 * ax::DropMenu::Info.
	 */
	class Info : public ax::widget::Info {
	public:
		Info();

		ax::Color normal;
		ax::Color hover;
		ax::Color font_color;

		ax::Color selected;
		ax::Color selected_hover;
		ax::Color selected_font_color;

		ax::Color contour;
		ax::Color separation;

		ax::Color up_down_arrow;
		ax::Color right_arrow;

		int item_height = 20;
		int font_size = 12;

		std::string font_path;
	};

	/*
	 * ax::DropMenu::DropMenu.
	 */

	/// Rect.size.y is used as maximum height.
	DropMenu(const ax::Rect& rect, const DropMenu::Events& events, const DropMenu::Info& info,
		const std::vector<std::string>& items, ax::util::Flag flags = 0);

	const std::vector<std::string>& GetItems() const;

	int GetSelectedItemIndex() const;

	std::string GetSelectedItem() const;

	void SetSelectedItem(const int& index);

protected:
	DropMenu::Events _events;
	ax::util::Flag _flags;
	std::vector<std::string> _items;
	std::unique_ptr<ax::Font> _font;
	std::unique_ptr<ax::Image> _up_img;
	std::unique_ptr<ax::Image> _down_img;
	std::unique_ptr<ax::Image> _right_img;
	int _selected_item;
	int _mouse_hover_item;

	bool _over_flow_down;
	bool _over_flow_up;
	bool _over_flow;
	int _n_shown_item;
	int _top_item_index;

	std::vector<int> _separator_index;
	std::vector<int> _right_arrow_index;

	int MousePosToIndex(const ax::Point& pos);

	void OnPaint(ax::GC gc);
	void OnMouseLeftDown(const ax::Point& pos);
	void OnMouseLeftUp(const ax::Point& pos);
	void OnMouseMotion(const ax::Point& pos);
	void OnMouseEnter(const ax::Point& pos);
	void OnMouseLeave(const ax::Point& pos);
};
}

/// @}
/// @}
#endif //__AX_DROP_MENU_H__
