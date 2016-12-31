#pragma once

#include <string>
#include "Util.hpp"

namespace cocoa {
	void AddEventToDispatchQueue();
	
	void HideMouse();
	void ShowMouse();
	
	std::string OpenFileDialog();
	std::string SaveFileDialog();
	
	ax::Size GetScreenSize();
	
	std::string GetPasteboardContent();
	
	std::string GetAppPath();
	std::string GetAppDirectory();
	
	void* CreateNSWindowFromApp(void* parent, void*& child, void*& appDelegate);
	//{
	//
	//#ifdef _AX_VST_APP_
	//	NSView* parentView = (__bridge NSView*)parent;
	//
	//	if (appDelegate == nullptr) {
	//		//        std::cout << "CREATE axVstAppDelegate WINDOW" << std::endl;
	//		axSize size = axApp::GetInstance()->GetCore()->GetGlobalSize();
	//		axVstAppDelegate* app = [[axVstAppDelegate alloc] initWithFrame:NSMakeRect(0, 0, size.x, size.y)];
	//		appDelegate = (__bridge void*)app;
	//		//[appDelegate retain];
	//		[parentView addSubview:app];
	//	}
	//	else {
	//		//        std::cout << "ATTACH WINDOW" << std::endl;
	//		[parentView addSubview:(__bridge axVstAppDelegate*)appDelegate];
	//	}
	//
	//	return (__bridge void*)parentView;
	//
	//#else
	//	return nullptr;
	//#endif // _AX_VST_APP_
	//}
}
