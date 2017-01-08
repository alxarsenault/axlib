/*
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
 */

#include "CocoaInterface.h"
#include "Util.hpp"

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

namespace cocoa {
	void AddEventToDispatchQueue()
	{
		dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0ul);
		dispatch_async(queue, ^{
			// Perform async operation
			dispatch_sync(dispatch_get_main_queue(), ^{
				// Update UI
			});
		});
	}
	
	static ax::Point hide_mouse_position;
	
	void HideMouse()
	{
		[NSCursor hide];
		NSPoint mPos = [NSEvent mouseLocation];
		hide_mouse_position.x = mPos.x;
		hide_mouse_position.y = mPos.y;
	}
	
	void ShowMouse()
	{
		NSRect e = [[NSScreen mainScreen] frame];
		
		CGPoint pt = CGPointMake(hide_mouse_position.x, e.size.height - hide_mouse_position.y);
		
		CGDisplayErr err;
		if ((err = CGWarpMouseCursorPosition(pt)) != CGEventNoErr) {
			NSLog(@"CGWarpMouseCursorPosition returned: \"%d\"", err);
		}
		
		[NSCursor unhide];
	}
	
	// http://stackoverflow.com/questions/20790249/cocoa-file-selection-dialog-allowed-filetypes
	std::string OpenFileDialog()
	{
//		NSOpenPanel* openDlg = [NSOpenPanel openPanel];
//		[openDlg setCanChooseFiles:YES];
//		[openDlg setCanChooseDirectories:YES];
//		[openDlg setPrompt:@"Select"];
//		
//		//	NSArray* filesType = [NSImage imageTypes];
//		NSArray* fileTypes = [[NSArray alloc] initWithObjects:@"atproj", @"ATPROJ", nil];
//		[openDlg setAllowedFileTypes:fileTypes];
//		
//		std::string file_path;
//		
//		if ([openDlg runModalForDirectory:nil file:nil] == NSOKButton) {
//			// NSArray* files = [openDlg filenames];
//			for (NSString* filePath in [openDlg filenames]) {
//				file_path = std::string([filePath UTF8String]);
//			}
//		}
//		
//		return file_path;
		
//		std::string file_path;
//		NSOpenPanel* openDlg = [NSOpenPanel openPanel];
//		//NSString* str;
//		
//		[openDlg setCanChooseFiles:YES];
//		
//		//[openDlg setAllowedFileTypes:@[@"html", @"htm"]];
//		
//		[openDlg beginWithCompletionHandler:^(NSInteger result) {
//			if(result==NSFileHandlingPanelOKButton) {
//				for (NSURL *url in openDlg.URLs) {
//					//NSLog(@"%@", url);
//					//str = [url absoluteString];
//					std::string test([[url absoluteString] UTF8String]);
//					//file_path = test;
//				}
//			}
//		}];
//		
//		return file_path;
		
		NSSavePanel* opnDlg = [NSOpenPanel savePanel];
		
		int modal = (int)[opnDlg runModal];
		
		if (modal != NSModalResponseOK) {
			return "";
		}
		
		NSString* filename = [[opnDlg URL] path];
		return std::string([filename UTF8String]);
	}
	
	std::string SaveFileDialog()
	{
		NSSavePanel* saveDlg = [NSSavePanel savePanel];
		
		int modal = (int)[saveDlg runModal];
		
		if (modal != NSModalResponseOK) {
			return "";
		}
				
		NSString* filename = [[saveDlg URL] path];
		return std::string([filename UTF8String]);
	}
	
	ax::Size GetScreenSize()
	{
		NSRect screenRect;
		NSArray* screenArray = [NSScreen screens];
		unsigned long screenCount = [screenArray count];
		
		for (unsigned int index = 0; index < screenCount; index++) {
			NSScreen* screen = [screenArray objectAtIndex:index];
			screenRect = [screen visibleFrame];
		}
		
		return ax::Size(screenRect.size.width, screenRect.size.height);
	}
	
	std::string GetPasteboardContent()
	{
		NSPasteboard* myPasteboard = [NSPasteboard generalPasteboard];
		NSString* myString = [myPasteboard stringForType:NSPasteboardTypeString];
		return std::string([myString UTF8String]);
	}
	
	void SetPasteboardContent(const std::string& str)
	{
		NSPasteboard* pb = [NSPasteboard generalPasteboard];
		[pb declareTypes:[NSArray arrayWithObject:NSStringPboardType] owner:nil];
		[pb setString:[NSString stringWithUTF8String:str.c_str()] forType:NSStringPboardType];
	}
	
	std::string GetAppPath()
	{
		NSString* curDir = [[NSBundle mainBundle] executablePath];
		return std::string([curDir UTF8String]);
	}
	
	std::string GetAppDirectory()
	{
#ifdef DEBUG
		NSString* curDir = [[NSFileManager defaultManager] currentDirectoryPath];
		// NSString *curDir = [[NSBundle mainBundle] executablePath];
		return std::string([curDir UTF8String]);
#else // RELEASE.
		
		NSString* path = [[NSBundle mainBundle] executablePath];
		std::string app_path([path UTF8String]);
		app_path = app_path.substr(0, app_path.find_last_of("/"));
		app_path = app_path.substr(0, app_path.find_last_of("/"));
		return app_path + std::string("/Resources");
		
#endif // DEBUG.
	}
	
	void* CreateNSWindowFromApp(void* parent, void*& child, void*& appDelegate)
	{
	#ifdef _AX_VST_APP_
//		NSView* parentView = (__bridge NSView*)parent;
//	
//		if (appDelegate == nullptr) {
//			//        std::cout << "CREATE axVstAppDelegate WINDOW" << std::endl;
//			axSize size = axApp::GetInstance()->GetCore()->GetGlobalSize();
//			axVstAppDelegate* app = [[axVstAppDelegate alloc] initWithFrame:NSMakeRect(0, 0, size.x, size.y)];
//			appDelegate = (__bridge void*)app;
//			//[appDelegate retain];
//			[parentView addSubview:app];
//		}
//		else {
//			//        std::cout << "ATTACH WINDOW" << std::endl;
//			[parentView addSubview:(__bridge axVstAppDelegate*)appDelegate];
//		}
//	
//		return (__bridge void*)parentView;
	
	#else
		return nullptr;
	#endif // _AX_VST_APP_
	}
}
