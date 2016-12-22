#import <cocoa/Cocoa.h>
#include "CocoaApplication.h"

namespace cocoa {
	Application::Application() {
		_ns_pool = (type::NSAutoreleasePool*)[[NSAutoreleasePool alloc] init];
		_ns_app = (type::NSApplication*)[NSApplication sharedApplication];
	}
	
	void Application::setDelegate(type::NSApplicationDelegate* delegate) {
		[(NSApplication*) _ns_app setDelegate:(id<NSApplicationDelegate>)delegate];
	}
	
	void Application::run() {
		[(NSApplication*) _ns_app run];
	}
}
