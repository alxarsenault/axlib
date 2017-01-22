#include "CocoaOpenGLView.h"

#import <cocoa/Cocoa.h>
#include "CocoaAppDelegate.h"
#include "axCoreMac.hpp"

namespace cocoa {
//	OpenGLView::OpenGLView() {
//		_app_delegate = (type::AppDelegate*)[[CocoaAppDelegate alloc] init];
//	}
	
	OpenGLView::OpenGLView(ax::core::CoreMac* core, const ax::Size& size) : _core(core) {
		_app_delegate = (type::AppDelegate*)[[CocoaAppDelegate alloc] initWithRect:
			NSMakeRect(0.0f, 0.0f, size.w, size.h) core:core cpp_view:this];
		
			_core->SetGlobalSize(size);
	}
	
	type::NSApplicationDelegate* OpenGLView::GetDelegate() {
		return (type::NSApplicationDelegate*)_app_delegate;
	}
	
	void OpenGLView::SetFrameSize(const ax::Size& size) {
		NSSize nSize = { static_cast<CGFloat>(size.w), static_cast<CGFloat>(size.h) };
	    [[(CocoaAppDelegate*)_app_delegate window] setContentSize:nSize];
		[(CocoaAppDelegate*)_app_delegate setFrame:NSMakeRect(0.f, 0.f, size.w, size.h)];
	}
	
	void OpenGLView::SetFocusAndCenter() {
		[(CocoaAppDelegate*)_app_delegate SetFocusAndCenter];
	}
	
	void OpenGLView::RefreshView() {
		[(CocoaAppDelegate*)_app_delegate RefreshView];
	}
	
	void OpenGLView::SetResizable(bool resizable)
	{
		if (resizable) {
			[(CocoaAppDelegate*)_app_delegate SetResizable];
		}
		else {
			[(CocoaAppDelegate*)_app_delegate SetNotResizable];
		}
	}
	
	void OpenGLView::SetTitleBar(bool titled)
	{
		if (titled) {
			[(CocoaAppDelegate*)_app_delegate SetTitleBar];
		}
		else {
			[(CocoaAppDelegate*)_app_delegate SetNoTitleBar];
		}
	}
	
	void OpenGLView::SetBorderLess()
	{
		[(CocoaAppDelegate*)_app_delegate SetBorderLess];
	}
	
	void OpenGLView::SetDefaultBorder()
	{
		[(CocoaAppDelegate*)_app_delegate SetDefaultBorder];
	}
	
	void OpenGLView::SetCursor(int cursor_id) {
		[(CocoaAppDelegate*)_app_delegate ChangeMouseCursor:cursor_id];
	}
}
