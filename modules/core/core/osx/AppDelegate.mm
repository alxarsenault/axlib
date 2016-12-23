///*
// * Copyright (c) 2015 Alexandre Arsenault.
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
//#import "AppDelegate.h"
//
//#include "EventManager.hpp"
//#include "axlib.hpp"
//#include "WindowManager.hpp"
//#include "axCocoaInterfaceMac.h"
//#include <OpenGL/OpenGL.h>
//#include <OpenGL/glu.h>
//#include <iostream>
//
//axAppDelegate* GlobalAppDelegate = nullptr;
//
//@implementation axAppDelegate
//
//- (id)initWithFrame:(NSRect)frame
//{
//	[self installRunLoopObserver];
//
//	self = [super initWithFrame:frame];
//
//	// Helps optimize Open GL context initialization for the best available
//	// resolution, important for Retina screens for example.
//	if (self) {
//
//		[self wantsBestResolutionOpenGLSurface];
//
//		//		NSTimer *timer = [NSTimer timerWithTimeInterval:1.0 / 30.0 target:self
//		// selector:@selector(renderTimer:) userInfo:nil repeats:YES];
//		//		[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
//	}
//
//	return self;
//}
//
//- (BOOL)application:(NSApplication*)app openFile:(NSString*)filename
//{
//	std::ofstream ff("/Users/alexarse/debug.txt");
//
//	ff << "Before filepath" << std::endl;
//	std::string file_path([filename UTF8String]);
//	//	ax::Print("AX APP OPEN FILE PATH :", file_path);
//
//	ff << file_path << std::endl;
//
//	ax::App::GetInstance().SetAppOpenFilePath(file_path);
//	ff << "After filepath" << std::endl;
//
//	ff.close();
//	return TRUE;
//}
//
//- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender
//{
//	return NSTerminateNow;
//}
//
//- (void)applicationWillTerminate:(NSNotification*)aNotification
//{
//	ax::util::console::Print("APPLICATION WILL TERMINATE");
//	_axApp->CloseApplication();
//}
//
//- (void)renderTimer:(NSTimer*)timer
//{
//	if (![[NSApplication sharedApplication] isHidden]) {
//		//		ax::Print("Timer");
//		//		[self setNeedsDisplay:YES];
//		[GlobalAppDelegate setNeedsDisplay:YES];
//	}
//}
//
//- (void)viewDidMoveToWindow
//{
//	[self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:YES];
//	[[self window] makeFirstResponder:self];
//	[[self window] setAcceptsMouseMovedEvents:YES];
//}
//
//- (BOOL)canBecomeMainWindow
//{
//	return YES;
//}
//
//- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
//{
////	ax::App::GetInstance().CallAfterGUILoadFunction();
//	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	[[self window] center];
//}
//
//- (void)prepareOpenGL
//{
//	GlobalAppDelegate = self;
//
//	// Synchronize buffer swaps with vertical refresh rate
//	GLint swapInt = 1;
//	[[self window] setAcceptsMouseMovedEvents:YES];
//	[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
//
//	_axApp = &ax::App::GetInstance();
//	_axApp->Init(ax::Size(500, 500));
////	_axApp->CallMainEntryFunction();
//	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//	[GlobalAppDelegate setNeedsDisplay:YES];
//}
//
//- (void)awakeFromNib
//{
//}
//
//- (id)MemberTestFunc
//{
//	[GlobalAppDelegate setNeedsDisplay:YES];
//	return self;
//}
//
//- (void)SetResizable
//{
//	[[self window] setStyleMask:[[self window] styleMask] | NSResizableWindowMask];
//}
//
//- (void)SetNotResizable
//{
//	[[self window] setStyleMask:[[self window] styleMask] & ~NSResizableWindowMask];
//}
//
//- (void)SetNoTitleBar
//{
//	[[self window] setStyleMask:[[self window] styleMask] & ~NSTitledWindowMask];
//}
//
//- (void)SetTitleBar
//{
//	[[self window] setStyleMask:[[self window] styleMask] | NSTitledWindowMask];
//}
//
//- (void)SetFocusAndCenter
//{
//	NSApplication* myApp = [NSApplication sharedApplication];
//	[myApp activateIgnoringOtherApps:YES];
//	
//
//	[[self window] center];
//
//	[[NSRunningApplication currentApplication]
//		activateWithOptions:(NSApplicationActivateAllWindows | NSApplicationActivateIgnoringOtherApps)];
//	
//	[[self window] orderFrontRegardless];
//	
//	
////	[[NSApplication sharedApplication] makeKeyAndOrderFront:myApp];
//
//	//	[self.window makeKeyAndOrderFront];
//}
//
//- (void)windowDidResize:(NSNotification*)notification
//{
//	ax::Size size([[self window] frame].size.width, [[self window] frame].size.height);
//
//	ax::Size size2([self bounds].size.width, [self bounds].size.height);
//
//	ax::Size size3(
//		[[self window] contentLayoutRect].size.width, [[self window] contentLayoutRect].size.height);
//
//	ax::App::GetInstance().SetFrameSize(size3);
//
//	// Resize openGL panel.
//	//	[GlobalAppDelegate setFrame:NSMakeRect(0.f, 0.f, size3.x, size3.y)];
//	//	[GlobalAppDelegate setFrameSize:NSMakeSize(size3.x, size3.y)];
//	//	[[GlobalAppDelegate window] center];
//	//	ax::Print("WINDOW DID RESIZE");
//}
//
//// Close application when clicking on the top left red "x" button.
//- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
//{
//	return TRUE;
//}
//
//- (void)windowDidMove:(NSNotification*)notification
//{
//	//    std::cout << "Mouve. " << std::endl;
//}
//
//- (void)SetFrameSize:(NSSize)newSize
//{
//	// Resize frame.
//	[[GlobalAppDelegate window] setContentSize:newSize];
//
//	//	GlobalAppDelegate setFrameSize:NSMakeSize(size3.x, size3.y)];
//
//	//	[GlobalAppDelegate
//	//		setFrameSize:NSMakeSize(newSize.width, newSize.height)];
//
//	// Resize openGL panel.
//	[GlobalAppDelegate setFrame:NSMakeRect(0.f, 0.f, newSize.width, newSize.height)];
//
//	//	[[GlobalAppDelegate window] center];
//	//	[GlobalAppDelegate
//	//		setBounds:NSMakeRect(0.f, 0.f, newSize.width, newSize.height)];
//}
//
//- (id)ChangeMouseCursor:(int)cursor_id
//{
//	//	ax::Print("Mouse in cocoa.");
//	if (cursor_id == 0) {
//		[[NSCursor arrowCursor] set];
//	}
//	
//	/// @todo Leaks ????????????????????????????????????????
//	else if (cursor_id == 1) {
////		[[NSCursor resizeUpDownCursor] set];
//		NSString *cursorName = @"resizenorthsouth";
//		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
//		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
//		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
//		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
//		
//		[cursor set];
//	}
//	else if (cursor_id == 2) {
////		[[NSCursor resizeLeftRightCursor] set];
//		
//		NSString *cursorName = @"resizeeastwest";
//		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
//		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
//		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
//		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
//		
//		[cursor set];
//	}
//	else if (cursor_id == 3) {
//		NSString *cursorName = @"resizenorthwestsoutheast";
//		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
//		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
//		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
//		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
//		
//		[cursor set];
//	}
//	else if (cursor_id == 4) {
//		NSString *cursorName = @"resizenortheastsouthwest";
//		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
//		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
//		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
//		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
//		
//		[cursor set];
//	}
//	
//	else if (cursor_id == 5) {
//		NSString *cursorName = @"move";
//		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
//		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
//		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
//		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
//		
//		[cursor set];
//	}
//	
//
//	return self;
//}
//
//- (void)mouseDown:(NSEvent*)event
//{
//	NSPoint locationInView = [self convertPoint:[event locationInWindow] fromView:nil];
//
//	ax::Point pos(locationInView.x, locationInView.y);
//
//	// Double click.
//	if (event.clickCount == 2) {
//		_axApp->GetPopupManager()->OnMouseLeftDoubleClick(pos);
//		if (_axApp->GetPopupManager()->IsEventReachWindow() == false) {
//			_axApp->GetWindowManager()->OnMouseLeftDoubleClick(pos);
//		}
//	}
//
//	// Simple click.
//	else {
//		_axApp->GetPopupManager()->OnMouseLeftDown(pos);
//
//		if (_axApp->GetPopupManager()->IsEventReachWindow() == false) {
//			_axApp->GetWindowManager()->OnMouseLeftDown(pos);
//		}
//	}
//}
//
//- (void)rightMouseDown:(NSEvent*)event
//{
//	NSPoint locationInView = [self convertPoint:[event locationInWindow] fromView:nil];
//
//	ax::Point pos(locationInView.x, locationInView.y);
//
//	// Double click.
//	if (event.clickCount == 2) {
//		//        _axApp->GetPopupManager()->OnMouseRightDoubleClick(pos);
//		//        if(_axApp->GetPopupManager()->IsEventReachWindow() == false)
//		//        {
//		//            _axApp->GetWindowManager()->OnMouseRightDoubleClick(pos);
//		//        }
//	}
//
//	// Simple click.
//	else {
//		_axApp->GetPopupManager()->OnMouseRightDown(pos);
//
//		if (_axApp->GetPopupManager()->IsEventReachWindow() == false) {
//			_axApp->GetWindowManager()->OnMouseRightDown(pos);
//		}
//	}
//}
//
//// Working.
//- (void)mouseUp:(NSEvent*)anEvent
//{
//	NSPoint locationInView = [self convertPoint:[anEvent locationInWindow] fromView:nil];
//
//	ax::Point pos(locationInView.x, locationInView.y);
//	_axApp->GetPopupManager()->OnMouseLeftUp(pos);
//
//	if (_axApp->GetPopupManager()->IsEventReachWindow() == false) {
//		_axApp->GetWindowManager()->OnMouseLeftUp(pos);
//	}
//}
//
//- (void)mouseDragged:(NSEvent*)theEvent
//{
//	NSPoint locationInView = [self convertPoint:[theEvent locationInWindow] fromView:nil];
//
//	ax::Point pos(locationInView.x, locationInView.y);
//	_axApp->GetPopupManager()->OnMouseLeftDragging(pos);
//
//	if (_axApp->GetPopupManager()->IsEventReachWindow() == false) {
//		_axApp->GetWindowManager()->OnMouseLeftDragging(pos);
//	}
//}
//
//- (void)mouseMoved:(NSEvent*)evt
//{
//	NSPoint locationInView = [self convertPoint:[evt locationInWindow] fromView:nil];
//
//	ax::Point pos(locationInView.x, locationInView.y);
//	_axApp->GetPopupManager()->OnMouseMotion(pos);
//
//	if (_axApp->GetPopupManager()->IsEventReachWindow() == false) {
//		_axApp->GetWindowManager()->OnMouseMotion(pos);
//	}
//}
//
//- (void)mouseEntered:(NSEvent*)theEvent
//{
//	//    NSLog(@"Mouse enter");
//}
//
//- (void)mouseExited:(NSEvent*)theEvent
//{
//	//    NSLog(@"Mouse leave");
//}
//
//- (BOOL)canBecomeKeyWindow
//{
//	return true;
//}
//
//- (void)flagsChanged:(NSEvent*)evt
//{
//	unsigned int key = [evt keyCode];
//
//	//	ax::Print("Flag :", key);
//
//	if (key == 55) {
//		_axApp->GetWindowManager()->OnCmdDown();
//	}
//}
//- (void)keyUp:(NSEvent*)event
//{
//	unsigned short key = [event keyCode];
//
//	// BackSpace.
//	if (key == 51) {
//		//		_axApp->GetWindowManager()->OnBackSpaceDown();
//		//		_axApp->GetPopupManager()->OnBackSpaceDown();
//	}
//	// Delete
//	else if (key == 117) {
//		//		_axApp->GetWindowManager()->OnKeyDeleteDown();
//		//		_axApp->GetPopupManager()->OnKeyDeleteDown();
//	}
//	// Enter.
//	else if (key == 36) {
//		//		_axApp->GetWindowManager()->OnEnterDown();
//		//		_axApp->GetPopupManager()->OnEnterDown();
//	}
//	// Left arrow.
//	else if (key == 123) {
//		//		_axApp->GetWindowManager()->OnLeftArrowDown();
//		//		_axApp->GetPopupManager()->OnLeftArrowDown();
//	}
//	// Right arrow.
//	else if (key == 124) {
//		//		_axApp->GetWindowManager()->OnRightArrowDown();
//		//		_axApp->GetPopupManager()->OnRightArrowDown();
//	}
//	// Arrow down.
//	else if (key == 125) {
//		//		_axApp->GetWindowManager()->OnDownArrowDown();
//		//		_axApp->GetPopupManager()->OnDownArrowDown();
//	}
//	// Arrow up.
//	else if (key == 126) {
//		//		_axApp->GetWindowManager()->OnUpArrowDown();
//		//		_axApp->GetPopupManager()->OnUpArrowDown();
//	}
//	else {
//		//		std::string str = [[event characters] UTF8String];
//		//		_axApp->GetWindowManager()->OnKeyDown(str[0]);
//		//		_axApp->GetPopupManager()->OnKeyDown(str[0]);
//	}
//}
//
//- (void)scrollWheel:(NSEvent*)event; // Mouse scroll wheel movement
//{
//	double dx = -[event deltaX];
//	double dy = -[event deltaY];
//
//	if (dy == 0 && dx == 0) {
//		return;
//	}
//
//	ax::Point delta(dx, dy);
//	_axApp->GetPopupManager()->OnScrollWheel(delta);
//
//	if (_axApp->GetPopupManager()->IsEventReachWindow() == false) {
//		_axApp->GetWindowManager()->OnScrollWheel(delta);
//	}
//}
//
//- (void)keyDown:(NSEvent*)event
//{
//	unsigned short key = [event keyCode];
//
//	//	ax::Print(key);
//
//	// BackSpace.
//	if (key == 51) {
//		_axApp->GetWindowManager()->OnBackSpaceDown();
//		_axApp->GetPopupManager()->OnBackSpaceDown();
//	}
//	// Delete
//	else if (key == 117) {
//		_axApp->GetWindowManager()->OnKeyDeleteDown();
//		_axApp->GetPopupManager()->OnKeyDeleteDown();
//	}
//	// Enter.
//	else if (key == 36) {
//		_axApp->GetWindowManager()->OnEnterDown();
//		_axApp->GetPopupManager()->OnEnterDown();
//	}
//	// Left arrow.
//	else if (key == 123) {
//		_axApp->GetWindowManager()->OnLeftArrowDown();
//		_axApp->GetPopupManager()->OnLeftArrowDown();
//	}
//	// Right arrow.
//	else if (key == 124) {
//		_axApp->GetWindowManager()->OnRightArrowDown();
//		_axApp->GetPopupManager()->OnRightArrowDown();
//	}
//	// Arrow down.
//	else if (key == 125) {
//		_axApp->GetWindowManager()->OnDownArrowDown();
//		_axApp->GetPopupManager()->OnDownArrowDown();
//	}
//	// Arrow up.
//	else if (key == 126) {
//		_axApp->GetWindowManager()->OnUpArrowDown();
//		_axApp->GetPopupManager()->OnUpArrowDown();
//	}
//	else {
//		std::string str = [[event characters] UTF8String];
//		_axApp->GetWindowManager()->OnKeyDown(str[0]);
//		_axApp->GetPopupManager()->OnKeyDown(str[0]);
//	}
//}
//
//// static int test_value = 0;
//void MyRunLoopObserver(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void* info)
//{
//	ax::App& app(ax::App::GetInstance());
//	std::shared_ptr<ax::event::Manager> evt(app.GetEventManager());
//
//	while (evt->GetEventQueueSize()) {
//		evt->CallNext();
//	}
//	//*
//	//    ax::App::GetInstance().GetEventManager()->CallNext();
//	//    axEventManager::GetInstance()->CallNext();
//}
//
//- (void)installRunLoopObserver
//{
//	// Run loop observer.
//	CFRunLoopObserverRef myObserver = NULL;
//	int myActivities = kCFRunLoopAllActivities; // kCFRunLoopBeforeWaiting;
//
//	// Create observer reference.
//	myObserver = CFRunLoopObserverCreate(NULL, myActivities, YES, 0, &MyRunLoopObserver, NULL);
//
//	if (myObserver) {
//		CFRunLoopAddObserver(CFRunLoopGetCurrent(), myObserver, kCFRunLoopCommonModes);
//	}
//}
//
//// Timer callback method
//- (void)timerFired:(id)sender
//{
//}
//
//// Set origin at top left position.
//- (BOOL)isFlipped
//{
//	return YES;
//}
//
//- (void)itemChanged:(NSMenuItem*)anObject
//{
//	//	std::cout << "Menu item" << std::endl;
//}
//
//// Each time window has to be redrawn, this method is called
//- (void)drawRect:(NSRect)bounds
//{
//	//    std::cout << "DrawRect" << std::endl;
//	// int frame_height = bounds.size.height;
//
//	NSRect backingBounds = [self convertRectToBacking:[self bounds]];
//
//	//*
//	//    axCore* core = _axApp->GetCore();
//
//	//    ax::Size global_size = core->GetGlobalSize();
//	ax::Size global_size = _axApp->GetFrameSize();
//
//	if (global_size.w != backingBounds.size.width || global_size.h != backingBounds.size.height) {
//
//		//		ax::Print("RESIZE");
//
//		ax::Size size3(
//			[[self window] contentLayoutRect].size.width, [[self window] contentLayoutRect].size.height);
//
//		ax::App::GetInstance().SetFrameSize(size3);
//
//		// Resize openGL panel.
//		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//		[GlobalAppDelegate setFrame:NSMakeRect(0.f, 0.f, size3.w, size3.h)];
//		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//		//		_axApp->SetFrameSize(
//		//			ax::Size(backingBounds.size.width,
//		// backingBounds.size.height));
//
//		//        core->ResizeGLScene(ax::Size(backingBounds.size.width,
//		//                                   backingBounds.size.height));
//		//        core->ResizeGLScene(backingBounds.size.width,
//		//                            backingBounds.size.height,
//		//                            frame_height - backingBounds.size.height);
//	}
//
//	if (global_size.w > 0 && global_size.h > 0) {
//
//		if ([self inLiveResize]) {
//			// Draw a quick approximation
//			//		std::cout << "Live resize drawing." << std::endl;
//			//		_axApp->UpdateAll();
//			_axApp->Draw();
//			glFlush();
//		}
//		else {
//			// Is only gonna draw if necessary.
//			//        core->DrawGLScene();
//			_axApp->Draw();
//			glFlush();
//		}
//	}
//	else {
//		glFlush();
//	}
//}
//
//@end
