/*******************************************************************************
 * Copyright (c) 2013 Alexandre Arsenault.
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
#include "axCoreAndroid.h"
#include "axApp.h"
#include "axWindowManager.h"
#include "axGC.h"
#include "axEventManager.h"

const std::string KeyboardHandler::KeyCode = "  1234567890-=  qwertyuiop[]  asdfghjkl;'   zxcvbnm,./";

// const char* KeyboardHandler::KeyCode[256] =
//{
//   	'', '', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
//	'-', '=', '',
//	'', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',
//	']', '\n', '', 'a', 's', 'd', 'f', 'g',
//	'h', 'j', 'k', 'l', ';', ''', '', "<shift>",
//	"\\", "z", "x", "c", "v", "b", "n", "m", ",", ".",
//	"/", "<shift>", "", "<alt>", " ", "<capslock>", "<f1>",
//	"<f2>", "<f3>", "<f4>", "<f5>", "<f6>", "<f7>", "<f8>", "<f9>",
//	"<f10>", "<numlock>", "<scrolllock>", "", "", "", "", "", "", "",
//	"", "", "", "\\", "f11", "f12", "", "", "", "", "", "",
//	"", "", "<control>", "", "<sysrq>"
//};

KeyboardHandler::KeyboardMsg::KeyboardMsg(KeyboardHandler* handler, const int& key)
	: _handler(handler)
	, _key(key)
{
}

ax::Event::Msg* KeyboardHandler::KeyboardMsg::GetCopy()
{
	return new KeyboardMsg(*this);
}

int KeyboardHandler::KeyboardMsg::GetKey() const
{
	return _key;
}

KeyboardHandler* KeyboardHandler::KeyboardMsg::GetHandler()
{
	return _handler;
}

KeyboardHandler::KeyboardHandler(ax::Event::Manager* manager)
	: ax::Event::Object(manager)
{
	AddConnection(KeyboardEvents::KEYBOARD_KEY_DOWN, GetOnKeyDown());
}

void KeyboardHandler::Init()
{
	_keyboard_evt_thread = std::thread(&keyboardEventCallback, (KeyboardHandler*)this);
}

void KeyboardHandler::keyboardEventCallback(KeyboardHandler* key_obj)
{
	ax::Print(ax::Console::Color::Blue, "Keyboard event.");

	int fd = open("/dev/input/event1", O_RDWR); // | O_NOCTTY | O_NDELAY);

	if (fd == -1) {
		ax::Error("Can't open keyboard file descriptor.");
		return;
	}

	struct input_event ie;

	int err = -1;

	while (1) {
		err = read(fd, &ie, sizeof(struct input_event));

		if (err < 0) {
			ax::Error("Read failed");
			return;
		}
		else if (err == 0) {
			ax::Print("No data.");
		}
		else {

			// ev.value: 0 if key release, 1 if key press, 2 if autorepeat keypress

			if (ie.type == EV_KEY && ie.value >= 0 && ie.value <= 2) {
				switch (ie.value) {
				case 0:
					break;

				case 1:
				case 2:
					//						ax::Print("Keypress :", ie.code);

					key_obj->PushEvent(KeyboardHandler::KeyboardEvents::KEYBOARD_KEY_DOWN,
						new KeyboardHandler::KeyboardMsg(key_obj, (int)ie.code));

					break;

					// case 2:
					//	break;
				}
			}
		}
	}

	close(fd);
}

void KeyboardHandler::OnKeyDown(KeyboardMsg& msg)
{
	ax::Print(msg.GetKey());
	int key = msg.GetKey();

	ax::App& app = ax::App::GetInstance();

	switch (key) {
	case KEY_UP:
		app.GetWindowManager()->OnUpArrowDown();
		app.GetPopupManager()->OnUpArrowDown();
		break;

	case KEY_LEFT:
		app.GetWindowManager()->OnLeftArrowDown();
		app.GetPopupManager()->OnLeftArrowDown();
		break;

	case KEY_RIGHT:
		app.GetWindowManager()->OnRightArrowDown();
		app.GetPopupManager()->OnRightArrowDown();
		break;

	case KEY_DOWN:
		app.GetWindowManager()->OnDownArrowDown();
		app.GetPopupManager()->OnDownArrowDown();
		break;

	case KEY_ENTER:
		app.GetWindowManager()->OnEnterDown();
		app.GetPopupManager()->OnEnterDown();
		break;

	case KEY_BACKSPACE:
		app.GetWindowManager()->OnBackSpaceDown();
		app.GetPopupManager()->OnBackSpaceDown();
		break;

	case KEY_SPACE:
		ax::Print("Space");
		app.GetWindowManager()->OnKeyDown(' ');
		app.GetPopupManager()->OnKeyDown(' ');
		break;

	case KEY_DELETE:
		app.GetWindowManager()->OnKeyDeleteDown();
		app.GetPopupManager()->OnKeyDeleteDown();
		break;

	default:
		if (key < (int)KeyboardHandler::KeyCode.size()) {
			char c = KeyboardHandler::KeyCode[key];

			if (c != ' ') {
				app.GetWindowManager()->OnKeyDown(c);
				app.GetPopupManager()->OnKeyDown(c);
			}
		}
		break;
	}

	//#define KEY_UP			103
	//#define KEY_PAGEUP		104
	//#define KEY_LEFT		105
	//#define KEY_RIGHT		106
	//#define KEY_END			107
	//#define KEY_DOWN		108
}

MouseHandler::MouseHandler(ax::Event::Manager* manager)
	: ax::Event::Object(manager)
	, _mouse_pos(0, 0)
{
	AddConnection(MouseObjEvents::MOUSE_LEFT_DOWN, GetOnMouseLeftDown());
	AddConnection(MouseObjEvents::MOUSE_LEFT_UP, GetOnMouseLeftUp());
	AddConnection(MouseObjEvents::MOUSE_MOTION, GetOnMouseMotion());
	AddConnection(MouseObjEvents::MOUSE_ABS_MOTION, GetOnMouseAbsMotion());
}

void MouseHandler::Init()
{
	_mouse_evt_thread = std::thread(&mouseEventCallback, (MouseHandler*)this);
}

void MouseHandler::mouseEventCallback(MouseHandler* mouse_obj)
{
	ax::Print(ax::Console::Color::Blue, "Mouse event test.");

	int fd = open("/dev/input/event0", O_RDWR); // | O_NOCTTY | O_NDELAY);

	if (fd == -1) {
		ax::Error("Can't open file descriptor.");
		return;
	}

	struct input_event ie;
	//        ax::Print("Event.");
	//        ax::Print("EV_SYN :", EV_SYN);
	//        ax::Print("EV_KEY :", EV_KEY);
	//        ax::Print("EV_REL :", EV_REL);
	//        ax::Print("EV_ABS :", EV_ABS);
	//        ax::Print("EV_MSC :", EV_MSC);
	//        ax::Print("EV_SW  :", EV_SW);

	int err = -1;
	bool _is_finger_down = false;
	bool _is_finger_down_send = false;
	while (1) {
		err = read(fd, &ie, sizeof(struct input_event));

		if (err < 0) {
			ax::Error("Read failed");
			return;
		}
		else if (err == 0) {
			ax::Print("No data.");
		}
		else {
			// ax::Print("TYPE : ", ie.type);
			switch (ie.type) {
			case EV_SYN:
				if (ie.code == SYN_REPORT) {
					// ax::Print("SYN REPORT");
				}
				else if (ie.code == SYN_MT_REPORT) {
					// ax::Print("SYN MT REPORT");
				}
				break;
			case EV_ABS:
				// ax::Print("Mouse move abs :", ie.value);
				if (ie.code == 0) {
					// ax::Print("Move x");
					mouse_obj->PushEvent(MouseHandler::MouseObjEvents::MOUSE_ABS_MOTION,
						new MouseHandler::MouseObjMsg(mouse_obj, ie.value, 0));
				}
				else if (ie.code == 1) {
					// ax::Print("Move y");
					mouse_obj->PushEvent(MouseHandler::MouseObjEvents::MOUSE_ABS_MOTION,
						new MouseHandler::MouseObjMsg(mouse_obj, 0, ie.value));
				}

				if (_is_finger_down) {
					if (_is_finger_down_send == false) {
						_is_finger_down_send = true;
					}
					else {
						mouse_obj->PushEvent(MouseHandler::MouseObjEvents::MOUSE_LEFT_DOWN,
							new MouseHandler::MouseObjMsg(mouse_obj, 0, 0));
						_is_finger_down = false;
						_is_finger_down_send = false;
					}
				}

				break;
			case EV_REL:
				// X Axis
				if (ie.code == 0) {
					mouse_obj->PushEvent(MouseHandler::MouseObjEvents::MOUSE_MOTION,
						new MouseHandler::MouseObjMsg(mouse_obj, ie.value, 0));
				}
				else if (ie.code == 1) {
					mouse_obj->PushEvent(MouseHandler::MouseObjEvents::MOUSE_MOTION,
						new MouseHandler::MouseObjMsg(mouse_obj, 0, ie.value));
				}
				break;

			case EV_KEY:
				// ax::Print("KEY CODE : ", ie.code);

				if (ie.code == BTN_TOUCH) {
					// ax::Print("TOUCH VALUE :", ie.value);

					if (ie.value == 1) {
						// ax::Print("Down");
						_is_finger_down = true;
						_is_finger_down_send = false;
						// mouse_obj->PushEvent(MouseHandler::MouseObjEvents::MOUSE_LEFT_DOWN,
						//		new MouseHandler::MouseObjMsg(mouse_obj, 0, 0));
					}
					else if (ie.value == 0) {
						_is_finger_down = false;
						mouse_obj->PushEvent(MouseHandler::MouseObjEvents::MOUSE_LEFT_UP,
							new MouseHandler::MouseObjMsg(mouse_obj, 0, 0));
					}
				}

				if (ie.code == BTN_LEFT) {
					if (ie.value == 1) {
						mouse_obj->PushEvent(MouseHandler::MouseObjEvents::MOUSE_LEFT_DOWN,
							new MouseHandler::MouseObjMsg(mouse_obj, 0, 0));
					}
					else if (ie.value == 0) {
						mouse_obj->PushEvent(MouseHandler::MouseObjEvents::MOUSE_LEFT_UP,
							new MouseHandler::MouseObjMsg(mouse_obj, 0, 0));
					}
				}

				break;
			}
		}
	}

	close(fd);
}

ax::Point MouseHandler::GetMousePos(const ax::Point& delta)
{
	_mouse_pos += delta;
	return _mouse_pos;
}

void MouseHandler::OnMouseAbsMotion(MouseObjMsg& msg)
{
	ax::App& app = ax::App::GetInstance();
	MouseHandler* handler = msg.GetHandler();
	ax::Point delta(msg.GetX(), msg.GetY());
	/// ax::Point pos = handler->GetMousePos(delta);

	if (delta.x != 0) {
		_mouse_pos.x = delta.x;
	}
	else {
		_mouse_pos.y = delta.y;
	}

	app.GetWindowManager()->OnMouseMotion(_mouse_pos);
	app.UpdateAll();
}

void MouseHandler::OnMouseMotion(MouseObjMsg& msg)
{
	ax::App& app = ax::App::GetInstance();
	MouseHandler* handler = msg.GetHandler();
	ax::Point delta(msg.GetX(), msg.GetY());
	ax::Point pos = handler->GetMousePos(delta);

	app.GetWindowManager()->OnMouseMotion(pos);
	app.UpdateAll();
}

void MouseHandler::OnMouseLeftDown(MouseObjMsg& msg)
{
	ax::App& app = ax::App::GetInstance();
	MouseHandler* handler = msg.GetHandler();
	ax::Point delta(msg.GetX(), msg.GetY());
	ax::Point pos = handler->GetMousePos(delta);

	app.GetWindowManager()->OnMouseLeftDown(pos);
	app.UpdateAll();
}

void MouseHandler::OnMouseLeftUp(MouseObjMsg& msg)
{
	ax::App& app = ax::App::GetInstance();
	MouseHandler* handler = msg.GetHandler();
	ax::Point delta(msg.GetX(), msg.GetY());
	ax::Point pos = handler->GetMousePos(delta);

	app.GetWindowManager()->OnMouseLeftUp(pos);
	app.UpdateAll();
}

MouseHandler::MouseObjMsg::MouseObjMsg(MouseHandler* handler, const int& x, const int& y)
	: _handler(handler)
	, _dx(x)
	, _dy(y)
{
}

ax::Event::Msg* MouseHandler::MouseObjMsg::GetCopy()
{
	return new MouseObjMsg(*this);
}

int MouseHandler::MouseObjMsg::GetX() const
{
	return _dx;
}

int MouseHandler::MouseObjMsg::GetY() const
{
	return _dy;
}

MouseHandler* MouseHandler::MouseObjMsg::GetHandler()
{
	return _handler;
}

ax::ProgramLoop::ProgramLoop()
	: _run_loop(false)
{
	if (pipe(_fd) == -1) {
		std::cerr << "Program loop can't create pipe." << std::endl;
		std::cerr << strerror(errno) << std::endl;
		exit(1);
	}
}

void ax::ProgramLoop::Unblock()
{
	// Send a message to unblock program loop.
	int msg = AX_MSG_MAIN_THREAD_UNBLOCK;
	write(_fd[1], (const void*)&msg, sizeof(msg));
}

void ax::ProgramLoop::SetLoopHandler(std::function<void()> handler)
{
	_main_loop_handler = handler;
}

void ax::ProgramLoop::Start()
{
	// No loop handler has been setup.
	if (!_main_loop_handler) {
		std::cerr << "No loop handler has been set." << std::endl;
		std::cerr << "Program loop won't start." << std::endl;
		return;
	}

	_run_loop = true;

	while (_run_loop) {
		int msg = 0;
		ssize_t nbytes = read(_fd[0], &msg, sizeof(msg));

		// End of file has been reach, getting out of the loop.
		if (nbytes == 0) {
			std::cerr << "End of file." << std::endl;
			_run_loop = false;
		}
		else if (nbytes == -1) { // Error while reading msg.

			// Interrupt error, keep looping.
			if (errno == EINTR) {
				continue;
			}

			// Get out of the main loop.
			std::cerr << "Error reading file descriptor." << std::endl;
			std::cerr << strerror(errno) << std::endl;
			_run_loop = false;
			break;
		}

		// Call the loop handler function.
		if (msg == AX_MSG_MAIN_THREAD_UNBLOCK) {
			_main_loop_handler();

			// Get out of the main loop.
		}
		else if (msg == AX_MSG_MAIN_THREAD_EXIT) {
			_run_loop = false;
		}
	}
}

axCoreAndroid::axCoreAndroid()
{
}

void axCoreAndroid::MainLoop()
{
	std::cout << "MainLoop" << std::endl;

	ax::App& app = ax::App::GetInstance();
	app.Init(ax::Size(_screen_size.x, _screen_size.y));

	_main_loop.SetLoopHandler([&]() {
		ax::App& app = ax::App::GetInstance();

		while (app.GetEventManager()->GetEventQueueSize()) {
			app.GetEventManager()->CallNext();
		}

		// app.UpdateAll();

		if (app.Draw()) {
			// ax::GC gc;
			// ax::Point  mouse_pos = _mouseHandler->GetMousePos(ax::Point(0, 0));

			// if(_cursor_id == 87) {
			//	gc.DrawImage(_mouse_resize, mouse_pos - ax::Point(12, 0));
			//}
			// else if(_cursor_id == 89) {
			//	gc.DrawImage(_mouse_vertical, mouse_pos - ax::Point(0, 12));
			//}
			// else {
			//	gc.DrawImage(_mouse_img, mouse_pos);
			//}

			eglSwapBuffers(_display, _surface);
		}

	});

	app.CallMainEntryFunction();

	//_mouse_img = new ax::Image("resources/Normal.png");
	//_mouse_resize = new ax::Image("resources/HResize.png");
	//_mouse_vertical = new ax::Image("resources/VerticalMouse.png");

	_mouseHandler = new MouseHandler(app.GetEventManager().get());
	_mouseHandler->Init();

	_keyboardHandler = new KeyboardHandler(app.GetEventManager().get());
	_keyboardHandler->Init();

	// Mainloop.
	_main_loop.Start();
}

void axCoreAndroid::Init(const ax::Size& frame_size)
{
	std::cout << "Init axCoreAndroid." << std::endl;
	InitManagers();

	CreateEGLContext();

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "Error after context : " << err << std::endl;
	}
	InitGL();

	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "Error after init : " << err << std::endl;
	}
	ResizeFrame(frame_size);

	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "Error after resize : " << err << std::endl;
	}
}

void axCoreAndroid::CreateEGLContext()
{
	bcm_host_init();
	int32_t success = 0;
	EGLBoolean result;
	EGLint num_config;

	static const EGLint attribute_list[] = { EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8, EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		// OPENGL ES 2
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE };

	// OPENGL ES 2.
	static const EGLint context_attribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

	EGLConfig config;

	// get an EGL display connection
	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	assert(_display != EGL_NO_DISPLAY);

	// initialize the EGL display connection
	result = eglInitialize(_display, NULL, NULL);
	assert(EGL_FALSE != result);

	//---------------------------------
	// OPENGL ES 2
	EGLConfig* configs;
	EGLint num_configs;

	eglGetConfigs(_display, NULL, 0, &num_configs);
	printf("EGL has %d configs\n", num_configs);

	configs = calloc(num_configs, sizeof *configs);
	eglGetConfigs(_display, configs, num_configs, &num_configs);

	// get an appropriate EGL configuration - just use the first available
	result = eglChooseConfig(_display, attribute_list, &config, 1, &num_configs);
	assert(EGL_FALSE != result);

	// Choose the OpenGL ES API
	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(EGL_FALSE != result);

	_context = eglCreateContext(_display, config, EGL_NO_CONTEXT, context_attribs);

	assert(_context != EGL_NO_CONTEXT);
	printf("Got an EGL context\n");
	//-------------------------------------------------------
	//
	// get an appropriate EGL frame buffer configuration
	// result = eglChooseConfig(_display, attribute_list, &config, 1, &num_config);
	// assert(EGL_FALSE != result);

	// create an EGL rendering context
	//_context = eglCreateContext(_display, config, EGL_NO_CONTEXT, NULL);
	// assert(_context != EGL_NO_CONTEXT);

	// create an EGL window surface
	success = graphics_get_display_size(0 /* LCD */, &_screen_size.x, &_screen_size.y);
	ax::Print("Screen size :", _screen_size.x, _screen_size.y);
	assert(success >= 0);

	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.width = _screen_size.x;
	dst_rect.height = _screen_size.y;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width = _screen_size.x << 16;
	src_rect.height = _screen_size.y << 16;

	dispman_display = vc_dispmanx_display_open(0 /* LCD */);
	dispman_update = vc_dispmanx_update_start(0);

	//----------------------------------------
	VC_DISPMANX_ALPHA_T dispman_alpha;

	dispman_alpha.flags = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS;
	dispman_alpha.opacity = 0xFF;
	dispman_alpha.mask = NULL;
	//---------------------------------------

	dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0 /*layer*/, &dst_rect,
		0 /*src*/, &src_rect, DISPMANX_PROTECTION_NONE,
		0, //&dispman_alpha /*alpha*/,
		0 /*clamp*/, (DISPMANX_TRANSFORM_T)0 /*transform*/);

	_nativewindow.element = dispman_element;
	_nativewindow.width = _screen_size.x;
	_nativewindow.height = _screen_size.y;
	vc_dispmanx_update_submit_sync(dispman_update);

	_surface = eglCreateWindowSurface(_display, config, &_nativewindow, NULL);
	assert(_surface != EGL_NO_SURFACE);

	// connect the context to the surface
	result = eglMakeCurrent(_display, _surface, _surface, _context);
	assert(EGL_FALSE != result);
}

ax::Size axCoreAndroid::GetScreenSize()
{
	return _size;
}

std::string axCoreAndroid::GetAppDirectory()
{
	return "";
}

std::string axCoreAndroid::GetAppPath()
{
	return "";
}

ax::Rect axCoreAndroid::GetScreenRect()
{
	return ax::Rect(0, 0, _size.x, _size.y);
}

void axCoreAndroid::KillGLWindow()
{
	eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroySurface(_display, _surface);
	eglDestroyContext(_display, _context);
	eglTerminate(_display);
}

bool axCoreAndroid::CreateGLWindow(const char* title, int width, int height, int bits)
{
	return true;
}

void axCoreAndroid::UpdateAll()
{
	axCore::UpdateAll();
}

void axCoreAndroid::ResizeFrame(const ax::Size& size)
{
	ResizeGLScene(size);
}

std::string axCoreAndroid::OpenFileDialog()
{
	return "";
}

void axCoreAndroid::PushEventOnSystemQueue()
{
	_main_loop.Unblock();
}

void axCoreAndroid::HideMouse()
{
	//    axCocoaHideMouse();
}

void axCoreAndroid::ShowMouse()
{
	//    axCocoaShowMouse();
}
