/*******************************************************************************
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
 ******************************************************************************/
#include "axCoreX11.h"
#include "App.h"
#include "WindowManager.h"
#include "GC.h"
#include "EventManager.h"
#include "Timer.h"

#include <X11/keysym.h>

namespace ax {
	namespace Core {
		X11::X11()
		{
			_refresh = true;
		}

		void X11::Init(const ax::Size& frame_size)
		{
			InitManagers();
			
			_display = XOpenDisplay(NULL);
			
			if(_display == NULL) {
				ax::Error("Can't connect to X server.");
				return;
			}
			_screen = XDefaultScreen(_display);
	
			_rootWindow = DefaultRootWindow(_display);

			GLint att[] = { GLX_RGBA, 
				GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
			_visualInfo = glXChooseVisual(_display, 0, att);

		
			if(_visualInfo == NULL) {
				ax::Error("No visual info found.");
				return;
			}

			ax::Size s_size(GetScreenSize());

			_colormap = XCreateColormap(_display, _rootWindow, 
					_visualInfo->visual, AllocNone);

			XSetWindowAttributes swa;
			swa.colormap = _colormap;
 			swa.event_mask = StructureNotifyMask	|
					ExposureMask   		| 
					KeyPressMask 		| 
					ButtonPressMask 	|
             	 			ButtonReleaseMask   	|
             	 			PointerMotionMask   	|
             	 			EnterWindowMask     	|
             	 			LeaveWindowMask;	

			_win = XCreateWindow(_display, _rootWindow, 0, 0, s_size.x, s_size.y, 0, 
					_visualInfo->depth, InputOutput, 
					_visualInfo->visual, 
					CWColormap | CWEventMask, &swa);
					
			 XMapWindow(_display, _win);
			 XStoreName(_display, _win, "OpenAX");

			 _glxContext = glXCreateContext(_display, _visualInfo, NULL, GL_TRUE);

			 // Get a matching FB config
			  // static int visual_attribs[] =
			  //   {
			  //     GLX_X_RENDERABLE    , True,
			  //     GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
			  //     GLX_RENDER_TYPE     , GLX_RGBA_BIT,
			  //     GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
			  //     GLX_RED_SIZE        , 8,
			  //     GLX_GREEN_SIZE      , 8,
			  //     GLX_BLUE_SIZE       , 8,
			  //     GLX_ALPHA_SIZE      , 8,
			  //     GLX_DEPTH_SIZE      , 24,
			  //     GLX_STENCIL_SIZE    , 8,
			  //     GLX_DOUBLEBUFFER    , True,
			  //     //GLX_SAMPLE_BUFFERS  , 1,
			  //     //GLX_SAMPLES         , 4,
			  //     None
			  //   };

			  // int glx_major, glx_minor;
			 
			  // // FBConfigs were added in GLX version 1.3.
			  // if ( !glXQueryVersion( _display, &glx_major, &glx_minor ) || 
			  //      ( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
			  // {
			  //   printf("Invalid GLX version");
			  //   exit(1);
			  // }

			  // printf( "Getting matching framebuffer configs\n" );
			  // int fbcount;
			  // GLXFBConfig* fbc = glXChooseFBConfig(_display, DefaultScreen(_display), visual_attribs, &fbcount);
			  // if (!fbc)
			  // {
			  //   printf( "Failed to retrieve a framebuffer config\n" );
			  //   exit(1);
			  // }

			//Get a pointer to the GL 3.0 context creation
			// PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribs = 
			// 	(PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress((GLubyte*)"glXCreateContextAttribsARB");
			// 	int attribs[] = {
   //      GLX_CONTEXT_MAJOR_VERSION_ARB, 3,//we want a 3.0 context
   //      GLX_CONTEXT_MINOR_VERSION_ARB, 0,
   //      0 //zero indicates the end of the array
   //  };

			//  _glxContext = glXCreateContextAttribs(_display, *fbc, 0, true, &attribs[0]);
			 glXMakeCurrent(_display, _win, _glxContext);
			
			Cursor cursor = XCreateFontCursor(_display, XC_left_ptr);
    			XDefineCursor(_display, _win, cursor);	

    		GLenum err = glewInit();
    		// ax::Print("Glew err :", err);

			//XSetInputFocus(_display, _win, RevertToParent, CurrentTime);	
			if(!InitGL()) {
				ax::Error("ax::Core::X11 failed to init OpenGL.");
				return;
			}

			ResizeGLScene(ax::Size(s_size.x, s_size.y));	
		}  
	
		ax::Size X11::GetScreenSize()                                                                       
		{                                                                                                             
			return ax::Size(XDisplayWidth(_display, _screen),
					XDisplayHeight(_display, _screen));                                                                                             
		}                                                                                                             
 
		ax::Rect X11::GetScreenRect()                                                                       
		{                                                                                                             
			return ax::Rect(0, 0, 
					XDisplayWidth(_display, _screen),
					XDisplayHeight(_display, _screen));                                                                                             
		}
                                                                                                             
		std::string ax::Core::X11::GetAppDirectory()
		{
			return "error";
		}

		std::string ax::Core::X11::GetAppPath() 
		{
			return "error";
		}

		std::string ax::Core::X11::OpenFileDialog()
		{
			return "";
		}
		// Function to create a keyboard event
		XKeyEvent createKeyEvent(Display *display, x11::Window &win,
                          x11:: Window &winRoot, bool press,
                           int keycode, int modifiers)
		{
		   XKeyEvent event;

		   event.display     = display;
		   event.window      = win;
		   event.root        = winRoot;
		   event.subwindow   = None;
		   event.time        = CurrentTime;
		   event.x           = 1;
		   event.y           = 1;
		   event.x_root      = 1;
		   event.y_root      = 1;
		   event.same_screen = True;
		   event.keycode     = XKeysymToKeycode(display, keycode);
		   event.state       = modifiers;

		   if(press)
		      event.type = KeyPress;
		   else
		      event.type = KeyRelease;

		   return event;
		}
		void ax::Core::X11::PushEventOnSystemQueue()
		{
			//bool locked = _display_mutex.try_lock();
			std::lock_guard<std::mutex> lk(_display_mutex);

			//if(locked == false && _evt_ready) {
			//	_display_mutex.unlock();
			//}			

			x11::Window winFocus;
   			int revert;
   			XGetInputFocus(_display, &winFocus, &revert);
			XKeyEvent event = createKeyEvent(_display, winFocus, _rootWindow, true, 0xff50, 0);
   			XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
			
			//if(locked) { _display_mutex.unlock(); }

			//if(locked == false && _evt_ready) { 
			//	_evt_ready = false;
			//	_display_mutex.lock(); 
			//}
		}

		void ax::Core::X11::KillGLWindow()
		{
			XCloseDisplay(_display);
		}

		void ax::Core::X11::UpdateAll()
		{
			axCore::UpdateAll();
		}	

		void ax::Core::X11::ResizeFrame(const ax::Size& size) 
		{
			ResizeGLScene(size);
		}

		
		void ax::Core::X11::MainLoop()
		{
			// trace << "Mainloop begin." << std::endl;
			ax::App& app(ax::App::GetInstance());
			// trace << "Before main entry." << std::endl;	
			app.CallMainEntryFunction();
			// trace << "After main entry." << std::endl;
			XEvent e;
			bool loop_on = true;
			// ax::Print("Mainloop begin.");


			// trace << "Before while loop." << std::endl;
	
			WindowManager* manager = app.GetWindowManager();
	
			// Create drawing timer.
			_drawing_timer = new ax::Event::Timer(app.GetEventManager(),
				ax::Event::Function([&](ax::Event::Msg* msg)
				{
					_refresh = true;
				}));
	
			_drawing_timer->StartTimer(ax::Event::Timer::TimeMs(20));
			
			int x11_fd;
			fd_set in_fds;
			x11_fd = ConnectionNumber(_display);

			while(loop_on) {
				// Create a File Description Set containing x11_fd
				FD_ZERO(&in_fds);
				FD_SET(x11_fd, &in_fds);

				// Set our timer.  One second sounds good.
				//tv.tv_usec = 0;
				//tv.tv_sec = 1;

				// Wait for X Event or a Timer
				if (select(x11_fd+1, &in_fds, 0, 0, 0)) {
				}
				    //ax::Print("Event Received.");
				else
				    // Handle timer here
				    ax::Print("Timer Fired!");


				std::lock_guard<std::mutex> lk(_display_mutex);
				if(XPending(_display)) 
				{
					//_display_mutex.unlock();
					XNextEvent(_display, &e);
					
					switch(e.type) {
						case Expose:
							XWindowAttributes gwa;
							XGetWindowAttributes(_display, _win, &gwa);
							ResizeGLScene(ax::Size(gwa.width, gwa.height));
							ax::Print("Screen size :", gwa.width, gwa.height);	
							UpdateAll();
							break;

						case MotionNotify:
							manager->OnMouseMotion(
								ax::Point(e.xmotion.x, e.xmotion.y));
							break;
						case ButtonPress:
							switch(e.xbutton.button) {
								case 1: // Mouse left down.
								{
									ax::Point m_pos(e.xbutton.x, e.xbutton.y);
									manager->OnMouseLeftDown(m_pos);
								}
								break;

								case 3: // Mouse right down.
								break;
							}
						break;

						case ButtonRelease:
							switch(e.xbutton.button) {
								case 1: // Mouse left up.
								{
									ax::Point m_pos(e.xbutton.x, e.xbutton.y);
									manager->OnMouseLeftUp(m_pos);
								}
								break;
								/// @todo Implement mouse right up.
								case 3: // Mouse right up.
								break;
							}
						break;
						case KeyPress:
						{
							char buf[128] = {0};
							KeySym keysym;
							int len = XLookupString(&e.xkey, buf, sizeof buf, &keysym, NULL);
				
							if (keysym == 0xff50)
							{
								//ax::Print("fake evt.");
								while(app.GetEventManager()->GetEventQueueSize()) {  
									app.GetEventManager()->CallNext();
								}
							}
						}
						break;
						
						case ClientMessage:
							ax::Print("Client message.");
							//while(app.GetEventManager()->GetEventQueueSize()) {			
							//app.GetEventManager()->CallNext();
							//}
						break;
					}
					
					if(_refresh) {
						_refresh = false;
						app.Draw();

						//if(DrawGLScene()) {
							//ax::Print("Refesh.");
							glXSwapBuffers(_display, _win);
						//}
							// glFlush();
					}
				}
			}
		}

		Display* ax::Core::X11::CreateDisplay()
		{
			Display* dpy = XOpenDisplay(NULL);
	
			if(dpy == NULL) {
				ax::Error("Cannot open X11 display.");
				exit(1);
			}

			return dpy;
		}

		XVisualInfo* ax::Core::X11::GetGLXVisualInfo(Display* dpy)
		{
			XVisualInfo* v_info = nullptr;

			GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

			v_info = glXChooseVisual(dpy, 0, att);

			if(v_info == nullptr) {
				ax::Error("ax::Core::X11 No visual found.");
				v_info = nullptr;
			}

			return v_info;
		}

		x11::Window ax::Core::X11::CreateWindow(Display* dpy, 
				const ax::Rect& rect, 
				x11::Window& root_win, 
				Colormap& cmap, 
				XVisualInfo* v_info)
		{
			XSetWindowAttributes attributes;
			attributes.colormap = cmap;
			attributes.override_redirect = false;

			return XCreateWindow( dpy,
								  root_win, // Parent.
								  rect.position.x,
								  rect.position.y,
								  rect.size.x,
								  rect.size.y,
								  0,
								  v_info->depth,
								  InputOutput,
								  v_info->visual,
								  CWColormap | CWOverrideRedirect,
								  &attributes);
		}
	}
}
