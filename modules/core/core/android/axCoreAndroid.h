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
#ifndef _AX_CORE_ANDROID_H_
#define _AX_CORE_ANDROID_H_

#ifdef ANDROID 

#include "axCore.h"
#include "axImage.h"

#include "bcm_host.h"
#include "GLES/gl.h" 
#include "EGL/egl.h" 
#include "EGL/eglext.h" 
#include <unistd.h> 
#include <fcntl.h>  
#include <linux/input.h> 

#include <thread>

#define AX_MSG_MAIN_THREAD_EXIT 8900
#define AX_MSG_MAIN_THREAD_UNBLOCK 8901

class KeyboardHandler : public ax::Event::Object
{
public:
	KeyboardHandler(ax::Event::Manager* manager);

	void Init();

	
	enum KeyboardEvents
	{
		KEYBOARD_KEY_DOWN
	};

	class KeyboardMsg : public ax::Event::Msg
	{
	public:
		KeyboardMsg(KeyboardHandler* handler, const int& key);
		
		virtual ax::Event::Msg* GetCopy();
	
		int GetKey() const;
		
		KeyboardHandler* GetHandler();

	private:
		KeyboardHandler* _handler;
		int _key;
	};

	static const std::string KeyCode;
private:
	std::thread _keyboard_evt_thread;

	axEVENT_ACCESSOR(KeyboardMsg, OnKeyDown);   
	void OnKeyDown(KeyboardMsg& msg);

	static void keyboardEventCallback(KeyboardHandler* key_obj);
};

class MouseHandler : public ax::Event::Object
{
public:
	enum MouseObjEvents
	{
		MOUSE_LEFT_DOWN,
		MOUSE_LEFT_UP,
		MOUSE_RIGHT_DOWN,
		MOUSE_RIGHT_UP,
		MOUSE_MOTION,
		MOUSE_ABS_MOTION
	};

	class MouseObjMsg : public ax::Event::Msg
	{
	public:
		MouseObjMsg(MouseHandler* handler, const int& x, const int& y);
		virtual ax::Event::Msg* GetCopy();
	
		int GetX() const;
		int GetY() const;
		MouseHandler* GetHandler();
	private:
		MouseHandler* _handler;
		int _dx, _dy;
	};


	MouseHandler(ax::Event::Manager* manager);

	void Init();

	ax::Point GetMousePos(const ax::Point& delta);


private:
	ax::Point _mouse_pos;
	std::thread _mouse_evt_thread;

	axEVENT_ACCESSOR(MouseObjMsg, OnMouseAbsMotion);  
	axEVENT_ACCESSOR(MouseObjMsg, OnMouseMotion);
	axEVENT_ACCESSOR(MouseObjMsg, OnMouseLeftDown);
	axEVENT_ACCESSOR(MouseObjMsg, OnMouseLeftUp);
	
	void OnMouseAbsMotion(MouseObjMsg& msg);
	void OnMouseMotion(MouseObjMsg& msg); 
	void OnMouseLeftDown(MouseObjMsg& msg);
	void OnMouseLeftUp(MouseObjMsg& msg);

	static void mouseEventCallback(MouseHandler* mouse_obj);
};

namespace ax {
class ProgramLoop
{
public:
	ProgramLoop();
	
	/// Unblock program loop and call the loop handler.
	void Unblock();
					
	void SetLoopHandler(std::function<void()> handler);
									
	/// Start the program loop.
	void Start();
															
private:
	int _fd[2];
	std::function<void()> _main_loop_handler;
	bool _run_loop;
};
}


class axCoreAndroid : public axCore
{
public:
    axCoreAndroid();
    
    virtual void MainLoop();
    
    virtual void Init(const ax::Size& frame_size);

    virtual std::string GetAppDirectory();
    
    virtual std::string GetAppPath();
    
    virtual ax::Rect GetScreenRect();
    
    virtual ax::Size GetScreenSize();
    
    virtual std::string OpenFileDialog();
    
    virtual void PushEventOnSystemQueue();

    virtual void KillGLWindow();
    
    virtual bool CreateGLWindow(const char* title, int width, int height, int bits);
    
    virtual void UpdateAll();
    
    virtual void ResizeFrame(const ax::Size& size);
    
    virtual void HideMouse();
    
    virtual void ShowMouse();

private:
	EGLDisplay _display;
	EGLSurface _surface;                                                                                        
	EGLContext _context;
	ax::Utils::Point2D<uint32_t> _screen_size;

	EGL_DISPMANX_WINDOW_T _nativewindow;
	DISPMANX_ELEMENT_HANDLE_T dispman_element;                                                                
	DISPMANX_DISPLAY_HANDLE_T dispman_display;                                                                
	DISPMANX_UPDATE_HANDLE_T dispman_update;                                                                  
	VC_RECT_T dst_rect;                                                                                       
	VC_RECT_T src_rect; 


	MouseHandler* _mouseHandler;
	KeyboardHandler* _keyboardHandler;
	//ax::Image* _mouse_img;
	//ax::Image* _mouse_resize;
	//ax::Image* _mouse_vertical;

	ax::ProgramLoop _main_loop;

	void CreateEGLContext();		
};

#endif // __APPLE__

#endif // _AX_CORE_ANDROID_H_

