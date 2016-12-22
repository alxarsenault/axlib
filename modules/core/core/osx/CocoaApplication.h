#pragma once

#include "CocoaType.h"

namespace cocoa {
	class Application {
	public:
		Application();
		
		void setDelegate(type::NSApplicationDelegate* delegate);
		
		void run();
		
	private:
		type::NSAutoreleasePool* _ns_pool;
		type::NSApplication* _ns_app;
	};
}
