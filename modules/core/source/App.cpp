/*
 * Copyright (c) 2016 Alexandre Arsenault.
 * Copyright (c) 2015 Philippe Groarke.
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
#include "EventManager.hpp"
#include "WindowManager.hpp"
#include "WindowTree.hpp"
#include "ResourceStorage.hpp"
#include "NodeVisitor.hpp"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>

#include "Render.hpp"

#ifdef AX_EOS_CORE
#include "axCoreEOS.h"
#endif

std::shared_ptr<ax::App> ax::App::_instance;
std::once_flag ax::App::_onlyOne;
ax::Size ax::App::_frameSize = ax::Size(500, 500);

ax::App& ax::App::GetInstance()
{
	if (ax::App::_instance == nullptr) {
		// ax::Print("new ax::App::GetInstance");
		ax::App::_instance.reset(new ax::App());
	}
	return *ax::App::_instance;
}

ax::App* ax::App::Create(core::Core* core)
{
	if (ax::App::_instance == nullptr) {
		// ax::Print("new ax::App::GetInstance");
		ax::App::_instance.reset(new ax::App(core));
	}

	return ax::App::_instance.get();
}

void ax::App::CloseApplication()
{
	_instance->GetPopupManager()->GetWindowTree()->GetNodeVector().clear();
	_instance->GetWindowManager()->GetWindowTree()->GetNodeVector().clear();

	ax::App::_instance.reset();
}

// void ax::App::CallMainEntryFunction()
//{
//	if (_mainEntryFunction) {
//		_mainEntryFunction();
//	}
//}
//
// void ax::App::CallAfterGUILoadFunction()
//{
//	if (_afterGuiLoadFunction) {
//		_afterGuiLoadFunction();
//	}
//}

void ax::App::AddTopLevel(std::shared_ptr<ax::Window> win)
{
	GetWindowManager()->GetWindowTree()->AddTopLevel(win);

	ax::core::WindowManager* wm = GetWindowManager();

	// Connect all child to parent window manager.
	ax::NodeVisitor::VisitFromNode(win.get(), [wm](ax::Window* window) {
		if (window->GetWindowManager() == nullptr) {
			window->SetWindowManager(wm);
			window->event.OnAssignToWindowManager(0);
		}
	});

	win->dimension.GetFrameBuffer()->AssignCustomFBDrawFunction([win](ax::GL::FrameBuffer& fb) {

		ax::Size global_size = ax::App::GetInstance().GetFrameSize();

#ifdef AX_EOS_CORE
		ax::App& app(ax::App::GetInstance());
		ax::CoreEOS* core = static_cast<ax::CoreEOS*>(app.GetCore());
		//		core->DrawOnMainFBO();
		glViewport(0, 0, global_size.x, global_size.y);

		// Bind main frame buffer.
		glBindFramebuffer(GL_FRAMEBUFFER, core->GetMainFrameBufferID());
#endif

		glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
		ax::GC::shader_fb.Activate();
		glEnable(GL_TEXTURE_2D);

		ax::FPoint pos(0.0, 0.0);

		const ax::Size& ss(win->dimension.GetShownRect().size);
		const ax::FSize size(ss.Cast<float>());

		// Bind framebuffer texture.
		glBindTexture(GL_TEXTURE_2D, win->dimension.GetFrameBuffer()->GetFrameBufferTexture());

		float vertices[8]
			= { pos.x, pos.y, pos.x, pos.y + size.h, pos.x + size.w, pos.y + size.h, pos.x + size.w, pos.y };

		float tex_coords[8] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };

		ax::Point win_abs_pos = win->dimension.GetAbsoluteRect().position;

		// Projection matrix.
		glm::mat4 projMat = glm::ortho((float)0.0, (float)global_size.w, (float)global_size.h, (float)0.0);

		// View matrix.
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(win_abs_pos.x, win_abs_pos.y, 0.0f));

		glm::mat4 model(1.0f);

		glm::mat4 model_view_proj = projMat * view * model;

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

	//	return win;
}

void ax::App::AddPopupTopLevel(std::shared_ptr<ax::Window> win)
{
	GetPopupManager()->GetWindowTree()->AddTopLevel(win);
	ax::core::WindowManager* wm = GetPopupManager();

	// Connect all child to parent window manager.
	ax::NodeVisitor::VisitFromNode(win.get(), [wm](ax::Window* window) {
		if (window->GetWindowManager() != wm) {
			window->SetWindowManager(wm);
			window->event.OnAssignToWindowManager(0);
		}
	});
}

void ax::App::AddTopLevel(std::shared_ptr<ax::Window::Backbone> bone)
{
	ax::Window* win = bone->GetWindow();
	GetWindowManager()->GetWindowTree()->AddTopLevel(std::shared_ptr<ax::Window>(win));
	win->backbone = bone;

	ax::core::WindowManager* wm = GetWindowManager();

	// Connect all child to parent window manager.
	ax::NodeVisitor::VisitFromNode(win, [wm](ax::Window* window) {
		if (window->GetWindowManager() != wm) {
			window->SetWindowManager(wm);
			window->event.OnAssignToWindowManager(0);
		}
	});

	win->dimension.GetFrameBuffer()->AssignCustomFBDrawFunction([win](ax::GL::FrameBuffer& fb) {

		glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
		ax::GC::shader_fb.Activate();
		glEnable(GL_TEXTURE_2D);

		ax::FPoint pos(0.0, 0.0);

		const ax::Size& ss(win->dimension.GetShownRect().size);
		const ax::FSize size(ss.Cast<float>());

		// Bind framebuffer texture.
		glBindTexture(GL_TEXTURE_2D, win->dimension.GetFrameBuffer()->GetFrameBufferTexture());

		float vertices[8]
			= { pos.x, pos.y, pos.x, pos.y + size.h, pos.x + size.w, pos.y + size.h, pos.x + size.w, pos.y };

		float tex_coords[8] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };

		ax::Point win_abs_pos = win->dimension.GetAbsoluteRect().position;
		ax::Size global_size = ax::App::GetInstance().GetFrameSize();

		// Projection matrix.
		glm::mat4 projMat = glm::ortho((float)0.0, (float)global_size.w, (float)global_size.h, (float)0.0);

		// View matrix.
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(win_abs_pos.x, win_abs_pos.y, 0.0f));

		glm::mat4 model(1.0f);

		glm::mat4 model_view_proj = projMat * view * model;

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

	//	return win;
}

void ax::App::AddPopupTopLevel(std::shared_ptr<ax::Window::Backbone> bone)
{
	ax::Window* win = bone->GetWindow();
	GetPopupManager()->GetWindowTree()->AddTopLevel(std::shared_ptr<ax::Window>(win));
	win->backbone = bone;

	ax::core::WindowManager* wm = GetPopupManager();

	// Connect all child to parent window manager.
	ax::NodeVisitor::VisitFromNode(win, [wm](ax::Window* window) {
		if (window->GetWindowManager() != wm) {
			window->SetWindowManager(wm);
			window->event.OnAssignToWindowManager(0);
		}
	});
}

std::shared_ptr<ax::Window> ax::App::GetTopLevel()
{
	return GetWindowManager()->GetWindowTree()->GetTopLevel();
}

/* Private */

ax::App::App()
	: ax::core::Facade(_frameSize)
	//	, _evtManager(new ax::event::Manager([&] { PushEventOnSystemQueue(); }))
	, _resourceManager(new ax::util::ResourceStorage())
{
	//	ax::Print("new ax::App::_evtManager");
	//	ax::Print("new ax::App::_resourceManager");
}

ax::App::App(core::Core* core)
	: ax::core::Facade(_frameSize, core)
	//	, _evtManager(new ax::event::Manager([&] { PushEventOnSystemQueue(); }))
	, _resourceManager(new ax::util::ResourceStorage())
{
	//	ax::Print("new ax::App::_evtManager");
	//	ax::Print("new ax::App::_resourceManager");
}

ax::App::App(const ax::App& a)
	: ax::core::Facade(a._frameSize)
{
	_instance = a._instance;
	_frameSize = a._frameSize;
}

ax::App& ax::App::operator=(const ax::App& a)
{
	if (this != &a) {
		_instance = a._instance;
		_frameSize = a._frameSize;
	}
	return *this;
}
