#pragma once

#include "CocoaType.h"
#include "Util.hpp"

namespace ax {
	namespace core {
		class CoreMac;
	}
}

namespace cocoa {
	namespace type {
		struct AppDelegate;
	}
	
	class OpenGLView {
	public:
		OpenGLView(ax::core::CoreMac* core, const ax::Size& size);
		
		void OnInit();
		void OnDraw();
		
		type::NSApplicationDelegate* GetDelegate();
		
		ax::core::CoreMac* GetCore();
		
		void SetFrameSize(const ax::Size& size);
		
		void SetFocusAndCenter();
		
		void RefreshView();
		void SetResizable(bool resizable);
		void SetTitleBar(bool titled);
		
		void SetCursor(int cursor_id);
		
	private:
		type::AppDelegate* _app_delegate;
		ax::core::CoreMac* _core = nullptr;
	};
}
