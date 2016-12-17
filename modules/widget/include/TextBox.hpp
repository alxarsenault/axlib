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

#ifndef __AX_TEXT_BOX__
#define __AX_TEXT_BOX__

/*
 * @file    axTextBox.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axButton.
 * @date    24/01/2015
 */

/// @defgroup Widgets
/// @{

#include "axlib.hpp"

namespace ax {
/*
 * axTextBox.
 */
class TextBox : public ax::Window::Backbone {
public:
	/*
	 * axTextBox::Flags.
	 */
	class Flags {
	public:
		static const ax::util::Flag FLASHING_CURSOR;
		static const ax::util::Flag CONTOUR_HIGHLIGHT;
		static const ax::util::Flag CONTOUR_NO_FADE;
		static const ax::util::Flag HIDDEN_TEXT;
	};

	/*
	 * axTextBox::Msg.
	 */
	class Msg : public ax::event::Msg {
	public:
		Msg();

		Msg(TextBox* sender, const std::string& msg);

		TextBox* GetSender() const;

		std::string GetMsg() const;

		ax::event::Msg* GetCopy();

	private:
		TextBox* _sender;
		std::string _msg;
	};

	/*
	 * axTextBox::Events.
	 */
	class Events {
	public:
		enum : ax::event::Id { BUTTON_CLICK, ENTER_CLICK };

		Events()
		{
		}
		Events(ax::event::Function& fct)
		{
			button_click = fct;
		}

		ax::event::Function button_click;
		ax::event::Function enter_click;
	};

	/*
	 * axTextBox::Info.
	 */
	class Info : public ax::widget::Info {
	public:
		Info();

		Info(const std::string& path);

		Info(const std::vector<std::pair<std::string, std::string>>& attributes);

		Info(const ax::Color& normal, const ax::Color& hover, const ax::Color& highlight,
			const ax::Color& selected, const ax::Color& selected_shadow, const ax::Color& cursor,
			const ax::Color& contour, const ax::Color& font_color);

		/// Info needed for debug editor. Derived from axInfo.
		virtual std::vector<std::string> GetParamNameList() const;
		virtual std::string GetAttributeValue(const std::string& name);
		virtual void SetAttribute(const std::pair<std::string, std::string>& attribute);

		ax::Color normal;
		ax::Color hover;
		ax::Color highlight; // This needs to be transparent (alpha < 1.0).
		ax::Color selected;
		ax::Color selected_shadow;
		ax::Color cursor;
		ax::Color contour;
		ax::Color font_color;
	};

	/*
	 * axTextBox::axTextBox.
	 */
	TextBox(const ax::Rect& rect, const TextBox::Events& events, const TextBox::Info& info,
		std::string img_path = "", std::string label = "", ax::util::Flag flags = 0);

	void SetLabel(const std::string& label);

	std::string GetLabel() const;

	void SetMaximumChar(const unsigned int& max_number_of_char);

protected:
	TextBox::Events _events;
	std::string _label;
	ax::Image* _btnImg;
	ax::util::Flag _flags;
	ax::Font* _font;

	ax::Color _currentColor;
	int _nCurrentImg, _cursorIndex, _cursorBarXPosition, _lastCharXPosition;
	unsigned int _maxNumChar;
	bool _isHightlight, _findClickCursorIndex, _cursorFlashActive;
	ax::Point _clickPosition;

	enum axTextBoxState { axBTN_NORMAL, axBTN_HOVER, axBTN_DOWN, axBTN_SELECTED };

	ax::event::Timer* _flashingCursor;

	void OnPaint(ax::GC gc);
	void OnMouseLeftDown(const ax::Point& pos);
	void OnMouseLeftDragging(const ax::Point& pos);
	void OnMouseLeftUp(const ax::Point& pos);
	void OnMouseEnter(const ax::Point& pos);
	void OnMouseLeave(const ax::Point& pos);
	void OnMouseLeftDoubleClick(const ax::Point& pos);

	void OnKeyDown(const char& key);
	void OnBackSpaceDown(const char& key);

	void OnEnterDown(const char& key);
	void OnLeftArrowDown(const char& key);
	void OnRightArrowDown(const char& key);
	void OnWasKeyUnGrabbed(const char& key);
	void OnWasKeyGrabbed(const char& key);
	void OnKeyDeleteDown(const char& key);

	void DrawContourRectangle(ax::GC gc);

	axEVENT_ACCESSOR(ax::event::Timer::Msg, OnFlashingCursorTimer);
	void OnFlashingCursorTimer(const ax::event::Timer::Msg& msg);
};
}

/// @}
#endif // __AX_TEXT_BOX__
