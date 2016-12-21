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

#include "TextBox.hpp"

namespace ax {
/*
 * TextBox::Flags.
 */
const ax::util::Flag TextBox::Flags::FLASHING_CURSOR = ax::util::FlagValue::FLAG_1;
const ax::util::Flag TextBox::Flags::CONTOUR_HIGHLIGHT = ax::util::FlagValue::FLAG_2;
const ax::util::Flag TextBox::Flags::CONTOUR_NO_FADE = ax::util::FlagValue::FLAG_3;
const ax::util::Flag TextBox::Flags::HIDDEN_TEXT = ax::util::FlagValue::FLAG_4;

/*
 * TextBox::Msg.
 */
TextBox::Msg::Msg()
{
	_sender = nullptr;
}

TextBox::Msg::Msg(TextBox* sender, const std::string& msg)
{
	_sender = sender;
	_msg = msg;
}

TextBox* TextBox::Msg::GetSender() const
{
	return _sender;
}

std::string TextBox::Msg::GetMsg() const
{
	return _msg;
}

ax::event::Msg* TextBox::Msg::GetCopy()
{
	return new TextBox::Msg(*this);
}

/*
 * TextBox::Info.
 */
TextBox::Info::Info()
	: ax::widget::Info()
{
}

TextBox::Info::Info(const ax::Color& normalColor, const ax::Color& hoverColor,
	const ax::Color& highlightColor, const ax::Color& selectedColor, const ax::Color& selected_shadowColor,
	const ax::Color& cursorColor, const ax::Color& contourColor, const ax::Color& font_colorColor)
	: ax::widget::Info()
	, normal(normalColor)
	, hover(hoverColor)
	, highlight(highlightColor)
	, selected(selectedColor)
	, selected_shadow(selected_shadowColor)
	, cursor(cursorColor)
	, contour(contourColor)
	, font_color(font_colorColor)
{
}

TextBox::Info::Info(const std::string& path)
	: ax::widget::Info(path)
{
}

TextBox::Info::Info(const std::vector<std::pair<std::string, std::string>>& attributes)
{
	SetAttributes(attributes);
}

std::vector<std::string> TextBox::Info::GetParamNameList() const
{
	return std::vector<std::string>{ "normal", "hover", "highlight", "selected", "selected_shadow", "cursor",
		"contour", "font_color" };
}

std::string TextBox::Info::GetAttributeValue(const std::string& name)
{
	if (name == "normal") {
		return normal.ToString();
	}
	else if (name == "hover") {
		return hover.ToString();
	}
	else if (name == "highlight") {
		return highlight.ToString();
	}
	else if (name == "selected") {
		return selected.ToString();
	}
	else if (name == "selected_shadow") {
		return selected_shadow.ToString();
	}
	else if (name == "cursor") {
		return cursor.ToString();
	}
	else if (name == "contour") {
		return contour.ToString();
	}
	else if (name == "font_color") {
		return font_color.ToString();
	}

	return "";
}

void TextBox::Info::SetAttribute(const std::pair<std::string, std::string>& attribute)
{
	if (attribute.first == "normal") {
		normal = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "hover") {
		hover = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "highlight") {
		highlight = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "selected") {
		selected = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "selected_shadow") {
		selected_shadow = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "cursor") {
		cursor = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "contour") {
		contour = ax::Color::FromString(attribute.second);
	}
	else if (attribute.first == "font_color") {
		font_color = ax::Color::FromString(attribute.second);
	}
}

/*
 * TextBox::Info.
 */

// TextBox::Events _events;
//	std::string _label;
//	ax::Image* _btnImg;
//	ax::util::Flag _flags;
//	ax::Font* _font;
//
//	ax::Color _currentColor;
//	int _nCurrentImg, _cursorIndex, _cursorBarXPosition, _lastCharXPosition;
//	unsigned int _maxNumChar;
//	bool _isHightlight, _findClickCursorIndex, _cursorFlashActive;
//	ax::Point _clickPosition;
//
//	enum axTextBoxState { axBTN_NORMAL, axBTN_HOVER, axBTN_DOWN, axBTN_SELECTED };
//
//	ax::event::Timer* _flashingCursor;
TextBox::TextBox(const ax::Rect& rect, const TextBox::Events& events, const TextBox::Info& info,
	std::string img_path, std::string label, ax::util::Flag flags)
	: _events(events)
	, _label(label)
	, _flags(flags)
	, _font(nullptr)
	, _cursorBarXPosition(5)
	, _lastCharXPosition(5)
	, _maxNumChar(10000000)
	, _isHightlight(false)
	, _findClickCursorIndex(false)
	, _cursorFlashActive(true)
	, _nCurrentImg(axBTN_NORMAL)
	, _flashingCursor(nullptr)
{
	win = ax::Window::Create(rect);

	// Builtin event connection.
	win->event.OnPaint = ax::WBind<ax::GC>(this, &TextBox::OnPaint);
	win->event.OnMouseLeftDown = ax::WBind<ax::Point>(this, &TextBox::OnMouseLeftDown);
	win->event.OnMouseLeftDragging = ax::WBind<ax::Point>(this, &TextBox::OnMouseLeftDragging);
	win->event.OnMouseLeftUp = ax::WBind<ax::Point>(this, &TextBox::OnMouseLeftUp);
	win->event.OnMouseEnter = ax::WBind<ax::Point>(this, &TextBox::OnMouseEnter);
	win->event.OnMouseLeave = ax::WBind<ax::Point>(this, &TextBox::OnMouseLeave);
	win->event.OnMouseLeftDoubleClick = ax::WBind<ax::Point>(this, &TextBox::OnMouseLeftDoubleClick);

	win->event.OnKeyDown = ax::WBind<char>(this, &TextBox::OnKeyDown);
	win->event.OnBackSpaceDown = ax::WBind<char>(this, &TextBox::OnBackSpaceDown);
	win->event.OnEnterDown = ax::WBind<char>(this, &TextBox::OnEnterDown);
	win->event.OnLeftArrowDown = ax::WBind<char>(this, &TextBox::OnLeftArrowDown);
	win->event.OnRightArrowDown = ax::WBind<char>(this, &TextBox::OnRightArrowDown);
	win->event.OnKeyDeleteDown = ax::WBind<char>(this, &TextBox::OnKeyDeleteDown);
	win->event.OnWasKeyGrabbed = ax::WBind<char>(this, &TextBox::OnWasKeyGrabbed);
	win->event.OnWasKeyUnGrabbed = ax::WBind<char>(this, &TextBox::OnWasKeyUnGrabbed);

	win->event.OnPaintOverFrameBuffer = ax::WBind<ax::GC>(this, &TextBox::DrawContourRectangle);

	win->component.Add("Widget", widget::Component::Ptr(new widget::Component(win, new TextBox::Info(info))));
	_currentColor = info.normal;

	_btnImg = new ax::Image(img_path);

	if (_events.button_click) {
		win->AddConnection(Events::BUTTON_CLICK, _events.button_click);
	}

	if (_events.enter_click) {
		win->AddConnection(Events::ENTER_CLICK, _events.enter_click);
	}

	if (ax::util::HasFlag(Flags::FLASHING_CURSOR, _flags)) {
		_flashingCursor = new ax::event::Timer(ax::App::GetInstance().GetEventManager());
		_flashingCursor->AddConnection(0, GetOnFlashingCursorTimer());
	}

	_cursorIndex = (int)_label.size();

	_font = new ax::Font(0);
}

void TextBox::SetLabel(const std::string& label)
{
	_label = label;
	_lastCharXPosition = 0;
	_cursorIndex = 0;
	win->Update();
}

void TextBox::SetMaximumChar(const unsigned int& max_number_of_char)
{
	_maxNumChar = max_number_of_char;
	if (_maxNumChar > 0 && _label.size() > _maxNumChar) {
		_label.resize(_maxNumChar);
		win->Update();
	}
}

std::string TextBox::GetLabel() const
{
	return _label;
}

void TextBox::OnMouseLeftDown(const ax::Point& pos)
{
	_findClickCursorIndex = true;
	_clickPosition = pos - win->dimension.GetAbsoluteRect().position;

	if (_isHightlight) {
		_isHightlight = false;
	}

	win->event.GrabMouse();
	win->event.GrabKey();
	win->Update();
}

void TextBox::OnFlashingCursorTimer(const ax::event::Timer::Msg& msg)
{
	_cursorFlashActive = !_cursorFlashActive;
	win->Update();
}

void TextBox::OnMouseLeftUp(const ax::Point& pos)
{
	if (win->event.IsGrabbed()) {
		win->event.UnGrabMouse();
	}
}

void TextBox::OnMouseEnter(const ax::Point& pos)
{
}

void TextBox::OnMouseLeave(const ax::Point& pos)
{
}

void TextBox::OnMouseLeftDragging(const ax::Point& pos)
{
	_clickPosition = pos - win->dimension.GetAbsoluteRect().position;
	win->Update();
}

void TextBox::OnMouseLeftDoubleClick(const ax::Point& pos)
{
	_isHightlight = true;
	win->Update();
}

void TextBox::OnWasKeyUnGrabbed(const char& key)
{
	if (ax::util::HasFlag(Flags::FLASHING_CURSOR, _flags)) {
		_flashingCursor->StopTimer();
	}

	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	TextBox::Info& info = *static_cast<TextBox::Info*>(widget->GetInfo());
	_currentColor = info.normal;

	win->Update();
}

void TextBox::OnWasKeyGrabbed(const char& key)
{
	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	TextBox::Info& info = *static_cast<TextBox::Info*>(widget->GetInfo());
	_currentColor = info.selected;

	if (ax::util::HasFlag(Flags::FLASHING_CURSOR, _flags)) {
		_flashingCursor->StartTimer(ax::event::Timer::TimeMs(500));
	}

	win->Update();
}

void TextBox::OnKeyDown(const char& key)
{
	// If all text is highlighted.
	if (_isHightlight) {
		_label.resize(0);
		_label.insert(0, &key, 1);
		_cursorIndex = 1;
		_isHightlight = false;
		win->Update();
	}
	// Insert char in _label.
	else {
		// Can't add another char label size if bigger than _maxNumChar.
		if (_label.size() != _maxNumChar) {
			if (_lastCharXPosition < win->dimension.GetRect().size.w - 10) {
				_label.insert(_cursorIndex, &key, 1);
				++_cursorIndex;
				win->Update();
			}
		}
	}
}

void TextBox::OnBackSpaceDown(const char& key)
{
	if (_isHightlight) {
		_label.resize(0);
		_cursorIndex = 0;
		_isHightlight = false;
		win->Update();
	}
	else if (_label.size() && _cursorIndex) {
		_label.erase(_cursorIndex - 1, 1);
		--_cursorIndex;

		if (_cursorIndex < 0) {
			_cursorIndex = 0;
		}
		win->Update();
	}
}

void TextBox::OnKeyDeleteDown(const char& key)
{
	if (_isHightlight) {
		_label.resize(0);
		_cursorIndex = 0;
		_isHightlight = false;
		win->Update();
	}
	else if (_label.size() && _cursorIndex < _label.size()) {
		_label.erase(_cursorIndex, 1);
		--_cursorIndex;

		if (_cursorIndex < 0) {
			_cursorIndex = 0;
		}
		win->Update();
	}
}

void TextBox::OnLeftArrowDown(const char& key)
{
	--_cursorIndex;

	if (_cursorIndex < 0) {
		_cursorIndex = 0;
	}

	if (_isHightlight) {
		_isHightlight = false;
	}

	win->Update();
}

void TextBox::OnRightArrowDown(const char& key)
{
	++_cursorIndex;

	if (_cursorIndex > _label.size()) {
		_cursorIndex = (int)_label.size();
	}

	if (_isHightlight) {
		_isHightlight = false;
	}

	win->Update();
}

void TextBox::OnEnterDown(const char& key)
{
	win->PushEvent(Events::ENTER_CLICK, new TextBox::Msg(this, _label));
	win->event.UnGrabKey();
	win->Update();
}

void TextBox::DrawContourRectangle(ax::GC gc)
{
	if (ax::util::HasFlag(Flags::CONTOUR_HIGHLIGHT, _flags)) {
		if (win->event.IsKeyGrab()) {
			ax::Rect rect(win->dimension.GetRect());

			widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
			TextBox::Info& info = *static_cast<TextBox::Info*>(widget->GetInfo());

			if (ax::util::HasFlag(Flags::CONTOUR_NO_FADE, _flags)) // Shadow fade.
			{
				gc.SetColor(info.selected_shadow);
				gc.DrawRectangle(ax::Rect(ax::Point(-5, -5), ax::Size(rect.size + ax::Size(9, 9))));
			}
			else {
				ax::Color col(info.selected_shadow);
				gc.SetColor(col);

				int nRect = 5;
				for (int i = 0; i < nRect; i++) {
					gc.DrawRectangleContour(
						ax::Rect(ax::Point(-i, -i), ax::Size(rect.size + ax::Size(2 * i, 2 * i))));

					double alpha = info.selected_shadow.GetAlpha();
					double mu = double(i) / double(nRect);

					col.SetAlpha(alpha - alpha * mu);
					gc.SetColor(col);
				}
			}
		}
	}
}

void TextBox::OnPaint(ax::GC gc)
{
	const ax::Rect rect(win->dimension.GetDrawingRect());

	gc.SetColor(_currentColor);
	gc.DrawRectangle(rect);

	ax::Point next_pos(5, (rect.size.h - _font->GetFontSize()) / 2 - 1);
	widget::Component::Ptr widget = win->component.Get<widget::Component>("Widget");
	TextBox::Info& info = *static_cast<TextBox::Info*>(widget->GetInfo());

	if (!_label.empty()) {

		if (ax::util::HasFlag(Flags::HIDDEN_TEXT, _flags)) {
			// Start drawing label.
			int x_pos = 10;
			for (int i = 0; i < _label.size(); i++) {
				gc.SetColor(info.font_color);
				gc.DrawPoint(ax::Point(x_pos, 14), 6);

				x_pos += 9;
				_cursorBarXPosition = x_pos;
			}
		}
		else {
			_cursorBarXPosition = 5;

			gc.SetColor(info.font_color);

			// Start drawing label.
			for (int i = 0; i < _label.size(); i++) {
				int x_past_pos = next_pos.x;
				next_pos = gc.DrawChar(*_font, _label[i], next_pos);

				//				if (_isHightlight) // hightlight on.
				//				{
				//					gc.SetColor(info.highlight);
				//					gc.DrawRectangle(ax::Rect(x_past_pos, 5,
				//						next_pos.x - x_past_pos, rect.size.y - 10));
				//				}

				if (_findClickCursorIndex) {
					if (_clickPosition.x >= x_past_pos && _clickPosition.x < next_pos.x) {
						_cursorIndex = i;
						_cursorBarXPosition = x_past_pos;
					}
					else if (i == _label.size() - 1 && _clickPosition.x > next_pos.x) {
						_cursorIndex = i + 1;
						_cursorBarXPosition = next_pos.x;
					}
				}
				else if (_cursorIndex - 1 == i) {
					_cursorBarXPosition = next_pos.x;
				}
			}

			if (_findClickCursorIndex) {
				_findClickCursorIndex = false;
			}

			_lastCharXPosition = next_pos.x;
		}
	}
	else {
		_cursorBarXPosition = 5;
	}

	if (_isHightlight) // hightlight on.
	{
		gc.SetColor(info.highlight);
		gc.DrawRectangle(ax::Rect(3, 3, _lastCharXPosition - 2, rect.size.h - 5));
	}

	if (win->event.IsKeyGrab() && _cursorFlashActive) {
		gc.SetColor(info.cursor);
		gc.DrawLine(ax::Point(_cursorBarXPosition, 3), ax::Point(_cursorBarXPosition, rect.size.h - 2));
	}

	gc.SetColor(info.contour);
	gc.DrawRectangleContour(rect);
	//	gc.DrawRoundedRectangleContour(rect0, 5);
}
}
