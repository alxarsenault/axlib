/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axFrameworks.
 *
 * axFrameworks is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axFrameworks License.
 *
 * axFrameworks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axFrameworks. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axFrameworks, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#pragma once

/// @defgroup Core
/// @{

#include "FrameBuffer.hpp"
#include "GC.hpp"
#include "Object.hpp"
#include "Util.hpp"

#include <array>

namespace ax {
class App;

namespace core {
	class WindowManager;
}

/*******************************************************************************
 * Window.
 ******************************************************************************/
class Window : public ax::event::Object, public std::enable_shared_from_this<ax::Window> {
public:
	//	typedef std::shared_ptr<ax::Window> Ptr;

	/***************************************************************************
	 * Window dimensions.
	 **************************************************************************/
	class Dimension {
	public:
		Dimension(ax::Window* win, const ax::Rect& rect);

		Dimension(const ax::Rect& rect);

		inline void SetWindow(ax::Window* win)
		{
			_win = win;
		}

		inline ax::Rect GetRect() const
		{
			return _rect;
		}

		inline ax::Size GetSize() const
		{
			return _rect.size;
		}

		inline ax::Rect GetShownRect() const
		{
			return _shownRect;
		}

		ax::Rect GetAbsoluteRect() const;

		inline ax::Rect GetDrawingRect() const
		{
			return ax::Rect(1, 1, _rect.size.w - 1, _rect.size.h - 1);
		}

		void SetRect(const ax::Rect& rect);

		void SetSize(const ax::Size& size);

		void SetPosition(const ax::Point& pos);

		void SetShownRect(const ax::Rect& rect);

		void SetSizeNoShowRect(const ax::Size& size);

		void SetScrollDecay(const ax::Point& decay);

		ax::Point GetScrollDecay() const;

		inline ax::GL::FrameBuffer* GetFrameBuffer()
		{
			return &_frameBufferObj;
		}

	protected:
		ax::Window* _win;
		ax::Rect _rect, _shownRect;
		ax::Point _scrollDecay;
		ax::GL::FrameBuffer _frameBufferObj;
	};

	/***************************************************************************
	 * Window events.
	 **************************************************************************/
	class Event {
	public:
		template <typename... Args> using Func_T = std::function<void(Args...)>;

		/***********************************************************************
		 * Event::Function.
		 **********************************************************************/
		template <typename... Args> class Function {
		public:
			inline Function();

			inline Function(const Func_T<Args...>& fct);

			~Function();

			/// Call the internal std::function.
			inline void operator()(Args... args);

			/// Return a copy of the internal std::function.
			inline Func_T<Args...> GetFunction() const;

			inline void operator=(const Function<Args...>& fct);

			bool operator==(const bool& v);

		private:
			/// Pointer of std::function<...> to reduce unused function size.
			Func_T<Args...>* _fct;
		};

		/***********************************************************************
		 * Event.
		 **********************************************************************/
		Event(ax::Window* win, ax::core::WindowManager* win_manager);

		~Event();

		inline void SetWindow(ax::Window* win)
		{
			_win = win;
		}

		std::shared_ptr<ax::Window> GetWindow();

		void GrabMouse();
		void UnGrabMouse();
		bool IsGrabbed() const;
		bool IsMouseHoverWindow() const;

		void GrabScroll();
		void UnGrabScroll();

		bool IsScrollGrabbed() const;

		void GrabKey();
		void UnGrabKey();
		bool IsKeyGrab() const;

		void GrabGlobalKey();
		bool IsGlobalKeyGrabbed() const;
		void UnGrabGlobalKey();

		void GrabGlobalMouse();
		bool IsGlobalMouseGrabbed() const;
		void UnGrabGlobalMouse();

		/// Keyboard events.
		Function<char> OnKeyDown;
		Function<char> OnCmdDown;
		Function<char> OnCmdUp;
		Function<char> OnBackSpaceDown;
		Function<char> OnEnterDown;
		Function<char> OnKeyDeleteDown;
		Function<char> OnLeftArrowDown;
		Function<char> OnRightArrowDown;
		Function<char> OnUpArrowDown;
		Function<char> OnDownArrowDown;

		Function<char> OnWasKeyGrabbed;
		Function<char> OnWasKeyUnGrabbed;

		/// Paint event.
		Function<ax::GC> OnPaint;
		Function<ax::GC> OnPaint3D;
		Function<int> OnBeforeDrawing;
		Function<ax::GC> OnPaintOverFrameBuffer;
		Function<ax::GC> OnPaintOverChildren;

		/// Size event.
		Function<ax::Size> OnResize;

		/// Mouse events.
		Function<ax::Point> OnMouseMotion;

		/// Mouse left button.
		Function<ax::Point> OnMouseLeftDown;
		Function<ax::Point> OnMouseLeftDoubleClick;
		Function<ax::Point> OnMouseLeftUp;
		Function<ax::Point> OnMouseLeftDragging;

		/// Mouse right button.
		Function<ax::Point> OnMouseRightDown;
		Function<ax::Point> OnMouseRightDoubleClick;
		Function<ax::Point> OnMouseRightUp;
		Function<ax::Point> OnMouseRightDragging;

		Function<ax::Point> OnMouseEnter;
		Function<ax::Point> OnMouseLeave;

		Function<ax::Point> OnMouseEnterChild;
		Function<ax::Point> OnMouseLeaveChild;

		// Track pad.
		Function<ax::Point> OnScrollWheel;

		struct GlobalClick {
			enum ClickType { LEFT_CLICK_DOWN, LEFT_CLICK_UP, RIGHT_CLICK_DOWN, RIGHT_CLICK_UP };

			int type;
			ax::Point pos;
		};

		Function<GlobalClick> OnGlobalClick;

		Function<int> OnAssignToWindowManager;

		inline void SetWindowManager(ax::core::WindowManager* wm)
		{
			_windowManager = wm;
		}

		inline ax::core::WindowManager* GetWindowManager()
		{
			return _windowManager;
		}

	protected:
		ax::Window* _win = nullptr;
		ax::core::WindowManager* _windowManager;
	};

	enum StateOption { Hidden, NeedUpdate, NUMBER_OF_STATES };

	/***************************************************************************
	 * Window states.
	 **************************************************************************/
	template <std::size_t N> class State : public std::array<bool, N> {
	public:
		inline State(ax::Window* win);

		inline void SetWindow(ax::Window* win);

		inline void Apply(StateOption state, bool value);

		inline bool Get(const StateOption& state);

	private:
		ax::Window* _win;
	};

	typedef State<NUMBER_OF_STATES> WindowState;

	/***************************************************************************
	 * Backbone.
	 **************************************************************************/
	class Backbone : public std::enable_shared_from_this<Backbone> {
	public:
		inline Backbone();

		virtual ~Backbone()
		{
		}

		inline void AssignWindow(std::shared_ptr<ax::Window> window);

		inline ax::Window* GetWindow();
		inline const ax::Window* GetWindow() const;

		virtual Backbone* GetCopy()
		{
			return nullptr;
		}

	protected:
		ax::Window* win;
	};

	/***************************************************************************
	 * Node.
	 **************************************************************************/
	class Node {
	public:
		inline Node(ax::Window* win);

		inline std::vector<std::shared_ptr<ax::Window>>& GetChildren();

		inline void SetParent(ax::Window* parent);

		inline ax::Window* GetParent();

		inline void SetWindow(ax::Window* win);

		inline ax::Window* GetWindow();

		void Reparent(Window* parent, const ax::Point& position);

		//		Ptr Add(Ptr child);
		void Add(std::shared_ptr<ax::Window> win);

		void Add(std::shared_ptr<Backbone> child);

		void Draw();

	private:
		ax::Window* _win = nullptr;
		ax::Window* _parent = nullptr;

		/// This is the owner of the window.
		std::vector<std::shared_ptr<ax::Window>> _children;

		struct BlockDrawingInfo {
			ax::Rect abs_rect;
			ax::Rect shown_rect;
		};

		void BlockDrawing(ax::Window* win);
		void UnBlockDrawing(ax::Window* win);
		static std::vector<BlockDrawingInfo> _block_drawing_queue;
	};

	/***************************************************************************
	 * Window.
	 **************************************************************************/
	inline static ax::Window* Create(const ax::Rect& rect)
	{
		return (new Window(rect));
	}

	virtual ~Window();

	std::shared_ptr<ax::Window> RemoveWindow();

	bool IsShown();
	void Show();
	void Hide();
	void Update();

	std::shared_ptr<ax::Window> GetWindowPtr();

	virtual void RenderWindow();

	ax::Rect GetWindowPixelData(unsigned char*& data) const;

	void GetWindowPixelData(unsigned char*& data, const ax::Rect& rect) const;

	inline ax::core::WindowManager* GetWindowManager()
	{
		return _windowManager;
	}

	inline void SetWindowManager(ax::core::WindowManager* wm)
	{
		_windowManager = wm;
		event.SetWindowManager(wm);
	}

	template <typename T> T* GetBackbone()
	{
		if (!backbone) {
			return nullptr;
		}

		return static_cast<T*>(backbone.get());
	}

protected:
	Window(const ax::Rect& rect);

	ax::core::WindowManager* _windowManager;

public:
	/// Window dimensions.
	Dimension dimension;

	/// Window events.
	Event event;

	/// Window properties :
	/// Popup, RealPopup, BlockDrawing, Selectable, EditingWidget,
	/// Editable, BackBuffer, AcceptWidget
	ax::Property property;

	/// Window components.
	ax::util::ComponentMap component;

	/// Window resources.
	ax::util::ResourceStorage resource;

	/// Window fix state options.
	WindowState state;

	/// Window tree node element.
	Node node;

	std::shared_ptr<Backbone> backbone;
};

/// Function type for builtin ax::Window events.
template <typename... Args> using WFunc = ax::Window::Event::Function<Args...>;

/// Function to bind class member function to WFunc type.
/// The binded function has to have one argument.
template <typename T, typename Class, typename Member, typename Object>
inline ax::WFunc<T> WBind(Object&& obj, Member Class::*mem_ptr)
{
	return ax::WFunc<T>(std::bind(mem_ptr, std::forward<Object>(obj), std::placeholders::_1));
}

/*******************************************************************************
 * Window::Event::Function.
 ******************************************************************************/
template <typename... Args>
inline Window::Event::Function<Args...>::Function()
	: _fct(nullptr)
{
}

template <typename... Args>
inline Window::Event::Function<Args...>::Function(const Window::Event::Func_T<Args...>& fct)
{
	//	ax::Print("Window::Event::Function");
	_fct = new Func_T<Args...>(fct);
}

template <typename... Args> Window::Event::Function<Args...>::~Function()
{
	if (_fct != nullptr) {
		delete _fct;
	}
}

/// Call the internal std::function.
template <typename... Args> inline void Window::Event::Function<Args...>::operator()(Args... args)
{
	if (_fct != nullptr && *_fct) {
		_fct->operator()(args...);
	}
}

/// Return a copy of the internal std::function.
template <typename... Args>
inline Window::Event::Func_T<Args...> Window::Event::Function<Args...>::GetFunction() const
{
	if (_fct != nullptr) {
		return *_fct;
	}

	// Return an empty function.
	return Func_T<Args...>();
}

template <typename... Args>
inline void Window::Event::Function<Args...>::operator=(const Function<Args...>& fct)
{
	if (_fct != nullptr) {
		delete _fct;
	}

	//	ax::Print("Window::Event::Function operator=");
	_fct = new Window::Event::Func_T<Args...>(fct.GetFunction());
}

template <typename... Args> bool Window::Event::Function<Args...>::operator==(const bool& v)
{
	return v == (_fct != nullptr);
}

/*******************************************************************************
 * Window::State.
 ******************************************************************************/
template <std::size_t N>
inline Window::State<N>::State(ax::Window* win)
	: _win(win)
{
}

template <std::size_t N> inline void Window::State<N>::SetWindow(ax::Window* win)
{
	_win = win;
}

template <std::size_t N> inline void Window::State<N>::Apply(Window::StateOption state, bool value)
{
	this->operator[](state) = value;
	_win->Update();
}

template <std::size_t N> inline bool Window::State<N>::Get(const Window::StateOption& state)
{
	return this->operator[](state);
}

/*******************************************************************************
 * Window::Backbone.
 ******************************************************************************/
inline Window::Backbone::Backbone()
{
}

inline void Window::Backbone::AssignWindow(std::shared_ptr<ax::Window> window)
{
	win = window.get();
}

inline ax::Window* Window::Backbone::GetWindow()
{
	return win;
}

inline const ax::Window* Window::Backbone::GetWindow() const
{
	return win;
}

// inline Window::Ptr Window::Backbone::GetWindow()
//{
//	return win;
//}

/*******************************************************************************
 * Window::Node.
 ******************************************************************************/
inline Window::Node::Node(ax::Window* win)
	: _win(win)
	, _parent(nullptr)
{
}

inline std::vector<std::shared_ptr<ax::Window>>& Window::Node::GetChildren()
{
	return _children;
}

inline void Window::Node::SetParent(ax::Window* parent)
{
	_parent = parent;
}

inline ax::Window* Window::Node::GetParent()
{
	return _parent;
}

inline void Window::Node::SetWindow(ax::Window* win)
{
	_win = win;
}

inline ax::Window* Window::Node::GetWindow()
{
	return _win;
}
}

/// @}
