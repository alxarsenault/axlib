/*
 * Copyright (c) 2015 Alexandre Arsenault.
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

#ifndef _AX_CORE_X11_H_
#define _AX_CORE_X11_H_

#ifdef axCoreX11

#include "Core.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <GL/glx.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <thread>

namespace x11 {
	typedef Window Window;
}

namespace ax {
	
	namespace Event {
		class Timer;
	}	

	namespace Core {
		class X11 : public axCore
		{
		public:
			X11();
			
			virtual void MainLoop();
			
			virtual void Init(const ax::Size& frame_size);

			virtual std::string GetAppDirectory();
			
			virtual std::string GetAppPath();
			
			virtual ax::Rect GetScreenRect();
			
			virtual ax::Size GetScreenSize();
			
			virtual std::string OpenFileDialog();
			
			virtual void PushEventOnSystemQueue();

			virtual void KillGLWindow();

			virtual bool CreateGLWindow(const char* title, int width, int height, 
					int bits = 16)
			{
				return true;
			}
			
			virtual void UpdateAll();
			
			virtual void ResizeFrame(const ax::Size& size);
			
			// Test --------------------
			std::thread _evt_thread;
			std::mutex _evt_mutex;
  			std::condition_variable _evt_cond;
			std::mutex _display_mutex;
			std::atomic<bool> _evt_ready;
			//--------------------------
		private:
			//std::mutex _display_mutex;
			Display* _display;
			x11::Window _win, _rootWindow;
			XVisualInfo* _visualInfo;
			int _screen, _nScreen, _depth;
			Colormap _colormap;
			GLXContext _glxContext;
			ax::Rect _winRect;
			std::atomic<bool> _refresh;	
	

			std::fstream trace;

			ax::Event::Timer* _drawing_timer;
			
			Display* CreateDisplay();
			XVisualInfo* GetGLXVisualInfo(Display* dpy);
			x11::Window CreateWindow(Display* dpy, const ax::Rect& rect, x11::Window& root_win, 
					Colormap& cmap, XVisualInfo* v_info);	
		};
	}
}
#endif // axCoreX11
#endif // _AX_CORE_X11_H_
