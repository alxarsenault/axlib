///*
// * Copyright (c) 2013 Alexandre Arsenault.
// *
// * This file is part of axFrameworks.
// *
// * axFrameworks is free or commercial software: you can redistribute it and/or
// * modify it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 or any later version of the
// * License or use a commercial axFrameworks License.
// *
// * axFrameworks is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with axFrameworks. If not, see <http://www.gnu.org/licenses/>.
// *
// * To release a closed-source product which uses axFrameworks, commercial
// * licenses are available, email alx.arsenault@gmail.com for more information.
// */
//#include "axCocoaInterfaceMac.h"
//#import <Cocoa/Cocoa.h>
//#import <Foundation/Foundation.h>
//
////#import <AppKit/AppKit.h>
//
//#include <iostream>
//
//#ifdef _AX_VST_APP_
//#include "axVstAppDelegate.h"
//#else
//#import "AppDelegate.h"
//#endif // _AX_VST_APP_
//
//#include "axlib.hpp"
//
////#include "NSOpenGLView+axPopupWindowCocoaView.h"
//
//// AppDelegate * delegate = [[AppDelegate alloc] init];
////[[NSApplication sharedApplication] setDelegate:delegate];
////[NSApp run];
//// void MainEntryPointCocoa(int argc, const char * argv[])
////{
//////    NSApplicationMain(argc, argv);
////
////    axAppDelegate* delegate = [[axAppDelegate alloc] initWithFrame: NSMakeRect(0, 0, 300, 300)];
////
////    //[[NSApplication sharedApplication] setDelegate:delegate];
////    [NSApp run];
////}
//
//void axCallNSApplicationMain()
//{
//	[NSApplication sharedApplication];
//	[NSBundle loadNibNamed:@"MainMenu" owner:NSApp];
//	[NSApp run];
//}
//
//std::string axOpenFileDialog()
//{
//	NSOpenPanel* openDlg = [NSOpenPanel openPanel];
//	[openDlg setCanChooseFiles:YES];
//	[openDlg setCanChooseDirectories:YES];
//	[openDlg setPrompt:@"Select"];
//
//	//	NSArray* filesType = [NSImage imageTypes];
//	NSArray* fileTypes = [[NSArray alloc] initWithObjects:@"atproj", @"ATPROJ", nil];
//	[openDlg setAllowedFileTypes:fileTypes];
//
//	std::string file_path;
//
//	if ([openDlg runModalForDirectory:nil file:nil] == NSOKButton) {
//		// NSArray* files = [openDlg filenames];
//		for (NSString* filePath in [openDlg filenames]) {
//			file_path = std::string([filePath UTF8String]);
//		}
//	}
//
//	return file_path;
//}
//
//std::string axSaveFileDialog()
//{
//	NSSavePanel* saveDlg = [NSSavePanel savePanel];
//
//	int modal = (int)[saveDlg runModal];
//
//	if (modal != NSOKButton) {
//		return "";
//	}
//
//	NSString* filename = [saveDlg filename];
//	return std::string([filename UTF8String]);
//}
//
//void TestFunctionInterface()
//{
////    axAppDelegate* appDelegate = (axAppDelegate*)[[NSApplication sharedApplication] delegate];
////    [appDelegate MemberTestFunc];
//
////    std::cout << "TestFunctionInterface" << std::endl;
//
//#ifdef _AX_VST_APP_
//	axApp* app = axApp::CreateApp();
//	axVstCoreMac* vstCoreMac = static_cast<axVstCoreMac*>(app->GetCore());
//	axVstAppDelegate* delegate = (__bridge axVstAppDelegate*)vstCoreMac->GetCurrentAppDelegate();
//
//	//    std::vector<axVstCoreData>* data = vstCoreMac->GetManagerVector();
//	//    for(auto& n : *data)
//	//    {
//	//        if(n.appDelegate != nullptr)
//	//        {
//	//            axAppDelegate* d = (__bridge axAppDelegate*)n.appDelegate;
//	//            [d MemberTestFunc];
//	//        }
//	//    }
//
//	[delegate MemberTestFunc];
//
//#else
//
//	[GlobalAppDelegate MemberTestFunc];
////[global_popup_view MemberTestFunc];
//#endif // _AX_VST_APP_
//}
//
//void axCocoaSetFocusAndCenter()
//{
//	//[GlobalAppDelegate SetFocusAndCenter];
//}
//
//void axCocoaSetResizable(bool resizable)
//{
//	if (resizable) {
//		[GlobalAppDelegate SetResizable];
//	}
//	else {
//		[GlobalAppDelegate SetNotResizable];
//	}
//}
//
//void axCocoaSetTitleBar(bool title_bar)
//{
//	if (title_bar) {
//		[GlobalAppDelegate SetTitleBar];
//	}
//	else {
//		[GlobalAppDelegate SetNoTitleBar];
//	}
//}
//
//void axCocoaChangeMouseCursor(int cursor_id)
//{
//	//	ax::Print("Mouse cursor cocoa interface.");
//	[GlobalAppDelegate ChangeMouseCursor:cursor_id];
//}
//
//std::string CocoaGetAppPath()
//{
//	NSString* curDir = [[NSBundle mainBundle] executablePath];
//	return std::string([curDir UTF8String]);
//}
//
//std::string CocoaGetAppDirectory()
//{
//#ifdef DEBUG
//	NSString* curDir = [[NSFileManager defaultManager] currentDirectoryPath];
//	// NSString *curDir = [[NSBundle mainBundle] executablePath];
//	return std::string([curDir UTF8String]);
//#else // RELEASE.
//
//	NSString* path = [[NSBundle mainBundle] executablePath];
//	std::string app_path([path UTF8String]);
//	app_path = app_path.substr(0, app_path.find_last_of("/"));
//	app_path = app_path.substr(0, app_path.find_last_of("/"));
//	return app_path + std::string("/Resources");
//
//#endif // DEBUG.
//}
//
//void AddEventToDispatchQueue()
//{
//	dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0ul);
//	dispatch_async(queue, ^{
//		// Perform async operation
//		dispatch_sync(dispatch_get_main_queue(), ^{
//						  // Update UI
//					  });
//	});
//}
//
//void axCocoaResizeFrame(const ax::Size& size)
//{
//#ifdef _AX_VST_APP_
//#else
//	axAppDelegate* appDelegate = (axAppDelegate*)[[NSApplication sharedApplication] delegate];
//
//	NSSize nSize = { static_cast<CGFloat>(size.w), static_cast<CGFloat>(size.h) };
//	[appDelegate SetFrameSize:nSize];
//	[[appDelegate window] center];
//#endif
//}
//
//static ax::Point hide_mouse_position;
//
//void axCocoaHideMouse()
//{
//	[NSCursor hide];
//	NSPoint mPos = [NSEvent mouseLocation];
//	hide_mouse_position.x = mPos.x;
//	hide_mouse_position.y = mPos.y;
//}
//
//void axCocoaShowMouse()
//{
//	//    ax::Print("Show mouse.");
//	NSRect e = [[NSScreen mainScreen] frame];
//
//	CGPoint pt = CGPointMake(hide_mouse_position.x, e.size.height - hide_mouse_position.y);
//	CGDisplayErr err;
//	if ((err = CGWarpMouseCursorPosition(pt)) != CGEventNoErr) {
//		NSLog(@"CGWarpMouseCursorPosition returned: \"%d\"", err);
//	}
//
//	[NSCursor unhide];
//}
//
////------------------------------------------------------------------------------
//// Use for vst interface from host given parent.
//// void* CreateNSWindow(void* ptr, void*& child)
////{
////    std::cout << "CreateNSWindow(void* ptr, void*& child) in TestWindow.mm" << std::endl;
//
////#ifdef _AX_VST_APP_
////    NSView* parentView = (__bridge NSView*)ptr;
////
////    if(GlobalAppDelegate == nullptr)
////    {
//////        std::cout << "CreateNSWindow GlobalAppDelegate in TestWindow.mm" << std::endl;
////        axVstAppDelegate* app = [[axVstAppDelegate alloc] initWithFrame: NSMakeRect(0, 0, 200, 200)];
////        GlobalAppDelegate = app;
////        [parentView addSubview: app];
////
////        return (__bridge void*)app;
////    }
////    else
////    {
//////        std::cout << "CreateNSWindow GlobalAppDelegate ELSE in TestWindow.mm" << std::endl;
////        //axAppDelegate* app = [[axAppDelegate alloc] initWithFrame: NSMakeRect(0, 0, 200, 200)];
////        [parentView addSubview: GlobalAppDelegate];
////
////    }
////
////    //    return (__bridge void*)parentView;
////    return (__bridge void*)GlobalAppDelegate;
////
////#else
////    return nullptr;
////#endif
////}
//
//void* CreateNSWindowFromApp(void* parent, void*& child, void*& appDelegate)
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
//
//void axReInitApp(void* appDelegate)
//{
//#ifdef _AX_VST_APP_
//	axVstAppDelegate* app = (__bridge axVstAppDelegate*)appDelegate;
//	[app ReInit];
//#endif
//}
//
//ax::Size axCocoaGetScreenSize()
//{
//	NSRect screenRect;
//	NSArray* screenArray = [NSScreen screens];
//	unsigned long screenCount = [screenArray count];
//
//	for (unsigned int index = 0; index < screenCount; index++) {
//		NSScreen* screen = [screenArray objectAtIndex:index];
//		screenRect = [screen visibleFrame];
//	}
//
//	return ax::Size(screenRect.size.width, screenRect.size.height);
//}
//
//void CreateNewPopupWindow()
//{
//	//    initWithFrame:(NSRect)frame
//
//	// axPopupWindowCocoaView* ggg = [[axPopupWindowCocoaView alloc] initWithFrame: NSMakeRect(0, 0, 300,
//	// 300)];
//
//	// axPopupWindowCocoaView* ggg = [[axPopupWindowCocoaView alloc] initWithNibName: @"axPopupWindow"];
//
//	// Working.
//	NSWindowController* ctrlWindow = [[NSWindowController alloc] initWithWindowNibName:@"axPopupWindow"];
//	[ctrlWindow showWindow:ctrlWindow];
//}
//
//void SetCurrentOpenGLContext()
//{
//	// axPopupWindowCocoaView* global_popup_view
//	// axPopupWindowCocoaView* delegate = (__bridge axPopupWindowCocoaView*)
//	// global_popup_view;
//
//	//        std::cout << "(void)ReInit currentIndex : " << vstCoreMac->GetCurrentManagerIndex() <<
//	//        std::endl;
//
//	//[[delegate openGLContext] makeCurrentContext];
//	//[delegate setNeedsDisplay:YES];
//	//[[delegate window] update];
//}
//
//std::string axCocoaGetPasteboardContent()
//{
//	NSPasteboard* myPasteboard = [NSPasteboard generalPasteboard];
//	NSString* myString = [myPasteboard stringForType:NSPasteboardTypeString];
//	return std::string([myString UTF8String]);
//}
