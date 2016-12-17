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

#include "App.hpp"
#include "Config.hpp"
#include "Window.hpp"
#include "WindowManager.hpp"
#include "WindowTree.hpp"

#include "GraphicInterface.hpp"
#include "Render.hpp"
#include "RenderMath.hpp"
#include "NodeVisitor.hpp"

#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

#ifdef AX_EOS_CORE
#include "axCoreEOS.h"
#endif

namespace ax {
/*
 * ax::Window::Dimension
 */
ax::Window::Dimension::Dimension(ax::Window* win, const ax::Rect& rect)
	: _win(win)
	, _rect(rect)
	, _shownRect(ax::Point(0, 0), rect.size)
	, _scrollDecay(0, 0)
	, _frameBufferObj(rect.size)
{
}

ax::Window::Dimension::Dimension(const ax::Rect& rect)
	: _rect(rect)
	, _shownRect(ax::Point(0, 0), rect.size)
	, _scrollDecay(0, 0)
	, _frameBufferObj(rect.size)
{
}

ax::Rect ax::Window::Dimension::GetAbsoluteRect() const
{
	ax::Point pos = _rect.position;
	Window* win = _win;

	/// @todo This can be faily slow.
	while (win->node.GetParent() != nullptr) {
		pos += win->node.GetParent()->dimension.GetRect().position;
		pos -= win->dimension._scrollDecay;
		win = win->node.GetParent();
	}

	return ax::Rect(pos, _rect.size);
}

void ax::Window::Dimension::SetRect(const ax::Rect& rect)
{
	_rect.position = rect.position;
	_rect.size = rect.size;
	_shownRect.size = rect.size;

	if (_win->property.HasProperty("BackBuffer")) {
		_frameBufferObj.Resize(rect.size);
	}

	_win->event.OnResize(_rect.size);
	_win->Update();
}

void ax::Window::Dimension::SetSize(const ax::Size& size)
{
	_rect.size = size;
	_shownRect.size = size;

	if (_win->property.HasProperty("BackBuffer")) {
		_frameBufferObj.Resize(size);
	}

	_win->event.OnResize(_rect.size);
	_win->Update();
}

void ax::Window::Dimension::SetPosition(const ax::Point& pos)
{
	_rect.position = pos;
	_win->Update();
}

void ax::Window::Dimension::SetShownRect(const ax::Rect& rect)
{
	_shownRect = rect;
	_win->Update();
}

void ax::Window::Dimension::SetSizeNoShowRect(const ax::Size& size)
{
	_rect.size = size;

	if (_win->property.HasProperty("BackBuffer")) {
		_frameBufferObj.Resize(size);
	}

	_win->Update();
}

void ax::Window::Dimension::SetScrollDecay(const ax::Point& decay)
{
	_scrollDecay = decay;
}

ax::Point ax::Window::Dimension::GetScrollDecay() const
{
	return _scrollDecay;
}

/*
 * Window event.
 */
ax::Window::Event::Event(ax::Window* win, ax::core::WindowManager* win_manager)
	: _win(win)
	, _windowManager(win_manager)
{
}

ax::Window::Event::~Event()
{
	//	std::cout << "Delete window event." << std::endl;
}

std::shared_ptr<ax::Window> ax::Window::Event::GetWindow()
{
	return _win->GetWindowPtr();
}

void Window::Event::GrabMouse()
{
	_windowManager->GrabMouse(_win);
}

void Window::Event::UnGrabMouse()
{
	_windowManager->UnGrabMouse(_win);
}

void Window::Event::GrabGlobalMouse()
{
	_windowManager->GrabGlobalMouse(_win);
}
bool Window::Event::IsGlobalMouseGrabbed() const
{
	return _windowManager->IsGlobalKeyGrabbed(_win);
}

void Window::Event::UnGrabGlobalMouse()
{
	_windowManager->UnGrabGlobalMouse(_win);
}

void Window::Event::GrabScroll()
{
	_windowManager->GrabScroll(_win);
}

void Window::Event::UnGrabScroll()
{
	_windowManager->UnGrabScroll(_win);
}

bool Window::Event::IsGrabbed() const
{
	return _windowManager->IsGrab(_win);
}

bool Window::Event::IsScrollGrabbed() const
{
	return _windowManager->IsScrollGrabbed(_win);
}

bool Window::Event::IsMouseHoverWindow() const
{
	return _windowManager->IsMouseHoverWindow(_win);
}

void Window::Event::GrabKey()
{
	_windowManager->GrabKey(_win);
}

void Window::Event::UnGrabKey()
{
	_windowManager->UnGrabKey(_win);
}

bool Window::Event::IsKeyGrab() const
{
	return _windowManager->IsKeyGrab(_win);
}

void Window::Event::GrabGlobalKey()
{
	_windowManager->AddGlobalGrabedWindow(_win);
}

bool Window::Event::IsGlobalKeyGrabbed() const
{
	return _windowManager->IsGlobalKeyGrabbed(_win);
}

void Window::Event::UnGrabGlobalKey()
{
	_windowManager->UnGrabGlobalKey(_win);
}

/*
 * Window node.
 */
std::vector<ax::Window::Node::BlockDrawingInfo> ax::Window::Node::_block_drawing_queue;

void ax::Window::Node::Add(std::shared_ptr<ax::Window> child)
{
// @todo Put this somewhere else.
#ifdef AX_EOS_CORE
	child->dimension.GetFrameBuffer()->AssignCustomFBDrawFunction([child](ax::GL::FrameBuffer& fb) {

		ax::App& app(ax::App::GetInstance());
		ax::CoreEOS* core = static_cast<ax::CoreEOS*>(app.GetCore());

		ax::Size global_size = ax::App::GetInstance().GetFrameSize();
		glViewport(0, 0, global_size.x, global_size.y);

		// Bind main frame buffer.
		glBindFramebuffer(GL_FRAMEBUFFER, core->GetMainFrameBufferID());

		ax::GC::shader_fb.Activate();
		glEnable(GL_TEXTURE_2D);

		fb.DrawingFrameBufferBlendFunction();

		ax::Point win_abs_pos = child->dimension.GetAbsoluteRect().position;

		// Projection matrix.
		glm::mat4 projMat = glm::ortho((float)0.0, (float)global_size.x, (float)global_size.y, (float)0.0);

		// View matrix.
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(win_abs_pos.x, win_abs_pos.y, 0.0f));

		glm::mat4 model(1.0f);
		glm::mat4 model_view_proj = projMat * view * model;

		ax::FloatPoint pos(0.0, 0.0);
		ax::FloatSize size(child->dimension.GetShownRect().size.Cast<float>());

		// Bind framebuffer texture.
		glBindTexture(GL_TEXTURE_2D, fb.GetFrameBufferTexture());

		float vertices[8]
			= { pos.x, pos.y, pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y, pos.x + size.x, pos.y };

		float tex_coords[8] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };

		GLuint prog_id = ax::GC::shader_fb.GetProgramId();
		GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&model_view_proj[0][0]);

		// Vertex coordinate.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// Texture coordinate.
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		// glDisableVertexAttribArray(5);

		glDisable(GL_TEXTURE_2D);
	});
#endif

	child->node._parent = _win;
	_children.push_back(child);

	// If parent is already connected to window manager.
	if (_win->GetWindowManager() != nullptr) {
		ax::core::WindowManager* wm = _win->GetWindowManager();

		// Connect all child to parent window manager.
		ax::NodeVisitor::VisitFromChild(_win, [wm](ax::Window* win) {
			if (win->GetWindowManager() != wm) {
				win->SetWindowManager(wm);
				win->event.OnAssignToWindowManager(0);
			}
		});
	}
}

void ax::Window::Node::Add(std::shared_ptr<Backbone> backbone)
{
	ax::Window* child = backbone->GetWindow();
	child->backbone = backbone;
	child->node._parent = _win;

	_children.push_back(std::shared_ptr<ax::Window>(child));

	// If parent is already connected to window manager.
	if (_win->GetWindowManager() != nullptr) {
		ax::core::WindowManager* wm = _win->GetWindowManager();

		// Connect all child to parent window manager.
		ax::NodeVisitor::VisitFromChild(_win, [wm](ax::Window* win) {
			if (win->GetWindowManager() != wm) {
				win->SetWindowManager(wm);
				win->event.OnAssignToWindowManager(0);
			}
		});
	}

#ifdef AX_EOS_CORE
	child->dimension.GetFrameBuffer()->AssignCustomFBDrawFunction([child](ax::GL::FrameBuffer& fb) {

		ax::App& app(ax::App::GetInstance());
		ax::CoreEOS* core = static_cast<ax::CoreEOS*>(app.GetCore());

		ax::Size global_size = ax::App::GetInstance().GetFrameSize();
		glViewport(0, 0, global_size.x, global_size.y);

		// Bind main frame buffer.
		glBindFramebuffer(GL_FRAMEBUFFER, core->GetMainFrameBufferID());

		ax::GC::shader_fb.Activate();
		glEnable(GL_TEXTURE_2D);

		fb.DrawingFrameBufferBlendFunction();

		ax::Point win_abs_pos = child->dimension.GetAbsoluteRect().position;

		// Projection matrix.
		glm::mat4 projMat = glm::ortho((float)0.0, (float)global_size.x, (float)global_size.y, (float)0.0);

		// View matrix.
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(win_abs_pos.x, win_abs_pos.y, 0.0f));

		glm::mat4 model(1.0f);
		glm::mat4 model_view_proj = projMat * view * model;

		ax::FloatPoint pos(0.0, 0.0);
		ax::FloatSize size(child->dimension.GetShownRect().size.Cast<float>());

		// Bind framebuffer texture.
		glBindTexture(GL_TEXTURE_2D, fb.GetFrameBufferTexture());

		float vertices[8]
			= { pos.x, pos.y, pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y, pos.x + size.x, pos.y };

		float tex_coords[8] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };

		GLuint prog_id = ax::GC::shader_fb.GetProgramId();
		GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&model_view_proj[0][0]);

		// Vertex coordinate.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// Texture coordinate.
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glDisableVertexAttribArray(0);
		// glDisableVertexAttribArray(5);
		glDisableVertexAttribArray(1);

		glDisable(GL_TEXTURE_2D);
	});
#endif

	//	return *_children.end();
}

void ax::Window::Node::Reparent(Window* parent, const ax::Point& position)
{
	ax::util::console::Error("ax::Window::Node::Reparent not implemented yet");
}

void ax::Window::Node::BlockDrawing(ax::Window* win)
{
	if (win->property.HasProperty("BlockDrawing")) {
		ax::Window::Dimension& dim = win->dimension;
		ax::Rect shown_rect(dim.GetShownRect());
		shown_rect.position = dim.GetScrollDecay();

		ax::Rect abs_rect = dim.GetAbsoluteRect();

		ax::Window* tmp = win;
		while (tmp != nullptr) {
			ax::Rect tmp_abs_rect(tmp->dimension.GetAbsoluteRect());

			// Find biggest left side position.
			if (tmp_abs_rect.position.x > abs_rect.position.x) {
				abs_rect.position.x = tmp_abs_rect.position.x;
			}

			//			// Find right side.
			//			if(tmp_abs_rect.position.x > abs_rect.position.x) {
			//				abs_rect.position.x = tmp_abs_rect.position.x;
			//			}

			tmp = tmp->node.GetParent();
		}

		// Find smallest size in parent.
		//		ax::Window* tmp = win;
		//		while(tmp != nullptr) {
		//			ax::Rect tmp_abs_rect(tmp->dimension.GetAbsoluteRect());
		//			if(tmp_abs_rect.position.x + tmp->dimension.GetShownRect().size.x < abs_rect.position.x +
		// shown_rect.size.x) {
		//				shown_rect.size.x = tmp->dimension.GetShownRect().size.x;
		//				abs_rect.position.x = tmp_abs_rect.position.x;
		//			}
		//			tmp = tmp->node.GetParent();
		//		}

		ax::GL::BlockDrawing(abs_rect, shown_rect, ax::App::GetInstance().GetFrameSize());

		BlockDrawingInfo binfo;
		binfo.abs_rect = abs_rect;
		binfo.shown_rect = shown_rect;
		_block_drawing_queue.push_back(binfo);
	}
}

void ax::Window::Node::UnBlockDrawing(ax::Window* win)
{
	if (win->property.HasProperty("BlockDrawing")) {

		_block_drawing_queue.pop_back();

		if (_block_drawing_queue.size()) {
			ax::GL::BlockDrawing(_block_drawing_queue.back().abs_rect, _block_drawing_queue.back().shown_rect,
				ax::App::GetInstance().GetFrameSize());
		}
		else {
			ax::GL::UnBlockDrawing();
		}
	}
}

// void DrawWindow(ax::Window* win)
//{
//	//	ax::GL::Math::Matrix4 mview;
//	//	mview.Identity().Load();
//	//
//	//	ax::Window::Dimension& dim = win->dimension;
//	////	mview.Translate(dim.GetAbsoluteRect().position -
//	/// dim.GetScrollDecay()).Process();
//	//	mview.Translate(dim.GetAbsoluteRect().position).Process();
//
//	win->RenderWindow();
//}

void DrawOverChildren(ax::Window* win)
{
	if (win->event.OnPaintOverChildren == true) {
		ax::Point win_abs_pos = win->dimension.GetAbsoluteRect().position;
		ax::Size global_size = ax::App::GetInstance().GetFrameSize();
		glm::mat4 projMat = glm::ortho((float)0.0, (float)global_size.w, (float)global_size.h, (float)0.0);

		// View matrix.
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(win_abs_pos.x, win_abs_pos.y, 0.0f));
		glm::mat4 model_view_proj = projMat * view;
		ax::GC::mvp_matrix = model_view_proj;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		win->dimension.GetFrameBuffer()->DrawingOnFrameBufferBlendFunction();
		win->event.OnPaintOverChildren(ax::GC());
	}
}

void Window::Node::Draw()
{
	// Don't draw if not shown.
	if (!_win->IsShown()) {
		return;
	}

	// Prevent from drawing beside framebuffer.
	BlockDrawing(_win);

	_win->RenderWindow();

	// Draw all children recursively.
	for (std::shared_ptr<ax::Window> it : _children) {

		if (it == nullptr) {
			continue;
		}

		// Don't draw if not shown.
		if (!it->IsShown()) {
			continue;
		}

		it->event.OnBeforeDrawing(0);

		// Block the drawging rectangle if window IsBlockDrawing activated.
		BlockDrawing(it.get());

		// Render window.
		it->RenderWindow();

		// Draw all child nodes (recursive call).
		it->node.Draw();

		// Unblock rectangle.
		UnBlockDrawing(it.get());

		// Draw over children and framebuffer.
		DrawOverChildren(it.get());
	}

	UnBlockDrawing(_win);

	// Draw over children and framebuffer.
	DrawOverChildren(_win);
}

/// @todo Change window manager.
Window::Window(const ax::Rect& rect)
	: ax::event::Object(ax::App::GetInstance().GetEventManager())
	//	, _windowManager(ax::App::GetInstance().GetWindowManager())
	, _windowManager(nullptr)
	, dimension(this, rect) // Members
	//	, event(this, ax::App::GetInstance().GetWindowManager())
	, event(this, nullptr)
	, state(this)
	, node(this)
{
	state[Hidden] = false;
	state[NeedUpdate] = true;

	property.AddProperty("BackBuffer");
	property.AddProperty("Selectable");
}

Window::~Window()
{
	//	ax::Print("ax::Window destructor ", GetId());
}

std::shared_ptr<ax::Window> Window::RemoveWindow()
{
	ax::Window* parent = node.GetParent();

	// Vector of children window shared pointer.
	std::vector<std::shared_ptr<ax::Window>>* children;

	if (parent == nullptr) {
		// This window is on top level or has no parent.
		children = &_windowManager->GetWindowTree()->GetNodeVector();
	}
	else {
		children = &parent->node.GetChildren();
		;
	}

	int index = -1;

	for (int i = 0; i < children->size(); i++) {
		if ((*children)[i]->GetId() == GetId()) {
			index = i;
			break;
		}
	}

	// If window is not found in parent somehow.
	if (index == -1) {
		ax::util::console::Error("Window not found on remove : Should never happen.");
		return nullptr;
	}

	event.UnGrabMouse();
	event.UnGrabKey();
	event.UnGrabScroll();

	event.UnGrabGlobalKey();
	event.UnGrabGlobalMouse();

	_windowManager->RemoveIfPastWindow(this);

	_windowManager = nullptr;

	std::shared_ptr<ax::Window> w = (*children)[index];

	// Remove from parent vector.
	children->erase(children->begin() + index);

	return w;
}

std::shared_ptr<ax::Window> Window::GetWindowPtr()
{
	if (node.GetParent() != nullptr) {
		std::shared_ptr<ax::Window> win;
		for (auto& n : node.GetParent()->node.GetChildren()) {
			if (n->GetId() == GetId()) {
				win = n;
				return win;
			}
		}
	}

	return nullptr;
}

bool Window::IsShown()
{
	Window* win = this;

	while (win != nullptr) {
		if (win->state[Hidden] == true) {
			return false;
		}

		win = win->node.GetParent();
	}
	return true;
}

void Window::Show()
{
	state.Apply(Hidden, false);
}

void Window::Hide()
{
	state.Apply(Hidden, true);
}

void Window::Update()
{
	state[NeedUpdate] = true;
	ax::App::GetInstance().UpdateAll();
}

void Window::RenderWindow()
{
#if _axBackBufferWindow_ == 1
	if (property.HasProperty("BackBuffer")) {
		if (state[NeedUpdate]) {

			// Draw on framebuffer.
			dimension.GetFrameBuffer()->DrawOnFrameBuffer(
				[this]() {
					event.OnPaint(ax::GC());
					event.OnPaint3D(ax::GC());
				},
				dimension.GetRect().size, ax::App::GetInstance().GetFrameSize());

			state[NeedUpdate] = false;
		}

		// Draw the framebuffer.
		ax::Point win_abs_pos = dimension.GetAbsoluteRect().position;
		ax::Size global_size = ax::App::GetInstance().GetFrameSize();

		// Projection matrix.
		glm::mat4 projMat = glm::ortho((float)0.0, (float)global_size.w, (float)global_size.h, (float)0.0);

		// View matrix.
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(win_abs_pos.x, win_abs_pos.y, 0.0f));

		glm::mat4 model(1.0f);

		glm::mat4 model_view_proj = projMat * view * model;

		dimension.GetFrameBuffer()->DrawFrameBuffer(dimension.GetShownRect().size, ax::Point(0, 0),
			ax::Rect(0, 0, 100, 100), (void*)&model_view_proj[0][0]);

		ax::GC::mvp_matrix = model_view_proj;
		event.OnPaintOverFrameBuffer(ax::GC());

		GLenum err = GL_NO_ERROR;
		while ((err = glGetError()) != GL_NO_ERROR) {
			// Process/log the error.

			util::console::Error("GL :", err);
		}
	}
	else {
		event.OnPaint(ax::GC());
		event.OnPaint3D(ax::GC());
	}

#else
	OnPaint();
#endif //_axBackBufferWindow_
}

ax::Rect Window::GetWindowPixelData(unsigned char*& data) const
{
	ax::Rect rect(dimension.GetAbsoluteRect());

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/// @todo MOVE TO axGL lib.
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	data = new unsigned char[rect.size.w * rect.size.h * 4];
	ax::Size globalSize(ax::App::GetInstance().GetFrameSize());

	glReadPixels(rect.position.x, globalSize.h - rect.position.y - rect.size.h, rect.size.w, rect.size.h,
		GL_RGBA, // Format.
		GL_UNSIGNED_BYTE, // Type.
		(void*)data);

	return rect;
}

void Window::GetWindowPixelData(unsigned char*& data, const ax::Rect& rect) const
{
	ax::Point pos(dimension.GetAbsoluteRect().position + rect.position);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/// @todo MOVE TO axGL lib.
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	data = new unsigned char[rect.size.w * rect.size.h * 4];
	ax::Size globalSize(ax::App::GetInstance().GetFrameSize());

	glReadPixels(pos.x, globalSize.h - pos.y - rect.size.h, rect.size.w, rect.size.h,
		GL_RGBA, // Format.
		GL_UNSIGNED_BYTE, // Type.
		(void*)data);
}
} // namespace ax
