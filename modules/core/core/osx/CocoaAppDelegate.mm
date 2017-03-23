#import "CocoaAppDelegate.h"
#include "CocoaOpenGLView.h"
#include "CocoaInterface.h"
#include "axCoreMac.hpp"

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <iostream>

#include <fst/print.h>

#include "App.hpp"
#include "EventManager.hpp"

@implementation CocoaAppDelegate

- (id)init {
	NSRect contentSize = NSMakeRect(0.0f, 0.0f, 480.0f, 320.0f);
	
	if ( self = [super initWithFrame:contentSize] ) {
		std::cout << "Bang\n";
		
		// Allocate window.
		_ns_window = [[NSWindow alloc] initWithContentRect:contentSize
			styleMask:NSWindowStyleMaskTitled backing:NSBackingStoreBuffered defer:YES];
		
		[_ns_window setTitle:@"test string"];
		
		[self wantsBestResolutionOpenGLSurface];
		
		// allocate view
//		view = [[NSView alloc] initWithFrame:contentSize];
	}
	return self;
}

- (id)initWithRect:(NSRect)contentSize core:(ax::core::CoreMac*)core cpp_view:(CppView*)cpp_view {

	if ( self = [super initWithFrame:contentSize] ) {
		_core = core;
		_cpp_view = cpp_view;
		
		[self installRunLoopObserver];
		
		std::cout << "Bang\n";
		
		// allocate window
		unsigned int frame_style_flags = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
			NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;
		
		_ns_window = [[NSWindow alloc] initWithContentRect:contentSize
			styleMask:frame_style_flags backing:NSBackingStoreBuffered defer:YES];
		
		[_ns_window setTitle:@"test string"];
		
		[self wantsBestResolutionOpenGLSurface];
		
		// allocate view
		//		view = [[NSView alloc] initWithFrame:contentSize];
	}
	return self;
}

- (BOOL)canBecomeKeyWindow
{
	return true;
}

- (void)applicationWillFinishLaunching:(NSNotification *)notification {
	std::cout << "applicationWillFinishLaunching\n";
	// Attach the view to the window
	[_ns_window setContentView:self];
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
	std::cout << "applicationDidFinishLaunching\n";
	
	// Make the window visible.
	[_ns_window makeKeyAndOrderFront:self];
	[_ns_window center];
	[_ns_window orderFrontRegardless];
}

- (void)dealloc {
	
	// don’t forget to release allocated objects!
//	[view release];
	[_ns_window release];
	
	[super dealloc];
}

// Close application when clicking on the top left red "x" button.
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
{
	return TRUE;
}

//----------------------------
// Custom events.
//----------------------------
- (void)RefreshView
{
	//[GlobalAppDelegate setNeedsDisplay:YES];
	[self setNeedsDisplay:YES];
	//return self;
}

// This function gets called a lot.
void RunLoopObserverCallback(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void* info)
{
	ax::core::CoreMac* core = (ax::core::CoreMac*)info;
	std::shared_ptr<ax::event::Manager> evt(core->GetEventManager());
	
	while (evt->GetEventQueueSize()) {
		evt->CallNext();
	}
}

- (void)installRunLoopObserver
{
	// Run loop observer.
	int myActivities = kCFRunLoopAllActivities; // kCFRunLoopBeforeWaiting;
	
//	typedef struct {
//		CFIndex	version;
//		void *	info;
//		const void *(*retain)(const void *info);
//		void	(*release)(const void *info);
//		CFStringRef	(*copyDescription)(const void *info);
//	} CFRunLoopObserverContext;

    CFRunLoopObserverContext context;
	
	context.info = (void*)_core;
	context.retain = nullptr;
	context.release = nullptr;
	context.copyDescription = nullptr;
	
	// Create observer reference.
	CFRunLoopObserverRef myObserver = CFRunLoopObserverCreate(NULL, myActivities, YES, 0, &RunLoopObserverCallback, &context);
	
	if (myObserver) {
		CFRunLoopAddObserver(CFRunLoopGetCurrent(), myObserver, kCFRunLoopCommonModes);
	}
}

//----------------------------
// Window events.
//----------------------------
- (void)viewDidMoveToWindow
{
	fst::print("(void)viewDidMoveToWindow");
	[self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:YES];
	[[self window] makeFirstResponder:self];
	[[self window] setAcceptsMouseMovedEvents:YES];
}

- (void)windowWillStartLiveResize:(NSNotification *)notification
{
	fst::print("(void)windowWillStartLiveResize:(NSNotification *)notification");
}

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize
{
	fst::print("(NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize");
	return frameSize;
}

- (void)windowDidResize:(NSNotification*)notification
{
	fst::print("(void)windowDidResize:(NSNotification*)notification)");
	ax::Size size([[self window] frame].size.width, [[self window] frame].size.height);
	
	ax::Size size2([self bounds].size.width, [self bounds].size.height);
	
	ax::Size size3([[self window] contentLayoutRect].size.width, [[self window] contentLayoutRect].size.height);
	
	_core->ResizeFrame(size3);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//ax::App::GetInstance().SetFrameSize(size3);
	
	// Resize openGL panel.
	//	[GlobalAppDelegate setFrame:NSMakeRect(0.f, 0.f, size3.x, size3.y)];
	//	[GlobalAppDelegate setFrameSize:NSMakeSize(size3.x, size3.y)];
	//	[[GlobalAppDelegate window] center];
	//	ax::Print("WINDOW DID RESIZE");
}

- (void)windowDidMove:(NSNotification*)notification
{
	fst::print("(void)windowDidMove:(NSNotification*)notification");
}

- (void)SetResizable
{
	[[self window] setStyleMask:[[self window] styleMask] | NSWindowStyleMaskResizable];
}

- (void)SetNotResizable
{
	[[self window] setStyleMask:[[self window] styleMask] & ~NSWindowStyleMaskResizable];
}

- (void)SetNoTitleBar
{
	[[self window] setStyleMask:[[self window] styleMask] & ~NSWindowStyleMaskTitled];
}

- (void)SetTitleBar
{
	[[self window] setStyleMask:[[self window] styleMask] | NSWindowStyleMaskTitled];
}

- (void)SetBorderLess
{
	[[self window] setStyleMask:NSWindowStyleMaskBorderless];
}

- (void)SetDefaultBorder
{
	[[self window] setStyleMask:[[self window] styleMask] | NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable];
}

- (void)SetFocusAndCenter
{
	NSApplication* myApp = [NSApplication sharedApplication];
	[myApp activateIgnoringOtherApps:YES];
	
	[[self window] center];
	
	[[NSRunningApplication currentApplication]
		activateWithOptions:(NSApplicationActivateAllWindows | NSApplicationActivateIgnoringOtherApps)];
	
	[[self window] orderFrontRegardless];
}

//-----------------------------------------------------------------------------
// Mouse events.
//-----------------------------------------------------------------------------
- (void)mouseMoved:(NSEvent*)evt
{
	NSPoint locationInView = [self convertPoint:[evt locationInWindow] fromView:nil];
	const ax::Point pos(locationInView.x, locationInView.y);

	_core->GetPopupManager()->OnMouseMotion(pos);
	
	if (_core->GetPopupManager()->IsEventReachWindow() == false) {
		_core->GetWindowManager()->OnMouseMotion(pos);
	}
}

- (void)mouseDown:(NSEvent*)event
{
	NSPoint locationInView = [self convertPoint:[event locationInWindow] fromView:nil];
	const ax::Point pos(locationInView.x, locationInView.y);
	
	// Double click.
	if (event.clickCount == 2) {
		_core->GetPopupManager()->OnMouseLeftDoubleClick(pos);
		if (_core->GetPopupManager()->IsEventReachWindow() == false) {
			_core->GetWindowManager()->OnMouseLeftDoubleClick(pos);
		}
	}
	
	// Simple click.
	else {
		_core->GetPopupManager()->OnMouseLeftDown(pos);
		
		if (_core->GetPopupManager()->IsEventReachWindow() == false) {
			_core->GetWindowManager()->OnMouseLeftDown(pos);
		}
	}
}

- (void)rightMouseDown:(NSEvent*)event
{    
	NSPoint locationInView = [self convertPoint:[event locationInWindow] fromView:nil];
	const ax::Point pos(locationInView.x, locationInView.y);
	
	// Double click.
	if (event.clickCount == 2) {
		//        _axApp->GetPopupManager()->OnMouseRightDoubleClick(pos);
		//        if(_axApp->GetPopupManager()->IsEventReachWindow() == false)
		//        {
		//            _axApp->GetWindowManager()->OnMouseRightDoubleClick(pos);
		//        }
	}
	
	// Simple click.
	else {
		_core->GetPopupManager()->OnMouseRightDown(pos);
		
		if (_core->GetPopupManager()->IsEventReachWindow() == false) {
			_core->GetWindowManager()->OnMouseRightDown(pos);
		}
	}
}

// Working.
- (void)mouseUp:(NSEvent*)anEvent
{
	NSPoint locationInView = [self convertPoint:[anEvent locationInWindow] fromView:nil];
	const ax::Point pos(locationInView.x, locationInView.y);
	
	_core->GetPopupManager()->OnMouseLeftUp(pos);
	
	if (_core->GetPopupManager()->IsEventReachWindow() == false) {
		_core->GetWindowManager()->OnMouseLeftUp(pos);
	}
}

- (void)mouseDragged:(NSEvent*)theEvent
{
	NSPoint locationInView = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	const ax::Point pos(locationInView.x, locationInView.y);
	
	_core->GetPopupManager()->OnMouseLeftDragging(pos);
	
	if (_core->GetPopupManager()->IsEventReachWindow() == false) {
		_core->GetWindowManager()->OnMouseLeftDragging(pos);
	}
}

// Mouse scroll wheel movement.
- (void)scrollWheel:(NSEvent*)event
{
	double dx = -[event deltaX];
	double dy = -[event deltaY];
	
	if (dy == 0 && dx == 0) {
		return;
	}
	
	ax::Point delta(dx, dy);
	_core->GetPopupManager()->OnScrollWheel(delta);
	
	if (_core->GetPopupManager()->IsEventReachWindow() == false) {
		_core->GetWindowManager()->OnScrollWheel(delta);
	}
}

- (id)ChangeMouseCursor:(int)cursor_id
{
	//	ax::Print("Mouse in cocoa.");
	if (cursor_id == 0) {
		[[NSCursor arrowCursor] set];
	}
	
	/// @todo Leaks ????????????????????????????????????????
	else if (cursor_id == 1) {
		//		[[NSCursor resizeUpDownCursor] set];
		NSString *cursorName = @"resizenorthsouth";
		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
		
		[cursor set];
	}
	else if (cursor_id == 2) {
		//		[[NSCursor resizeLeftRightCursor] set];
		
		NSString *cursorName = @"resizeeastwest";
		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
		
		[cursor set];
	}
	else if (cursor_id == 3) {
		NSString *cursorName = @"resizenorthwestsoutheast";
		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
		
		[cursor set];
	}
	else if (cursor_id == 4) {
		NSString *cursorName = @"resizenortheastsouthwest";
		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
		
		[cursor set];
	}
	
	else if (cursor_id == 5) {
		NSString *cursorName = @"move";
		NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
		NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
		NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
		NSCursor *cursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
		
		[cursor set];
	}
	
	
	return self;
}

//-----------------------------------------------------------------------------
// Key events.
//-----------------------------------------------------------------------------
- (void)flagsChanged:(NSEvent*)evt
{
	unsigned int key = [evt keyCode];
	
	//	ax::Print("Flag :", key);
	
	if (key == 55) {
		_core->GetWindowManager()->OnCmdDown();
	}
}

- (void)keyUp:(NSEvent*)event
{
	unsigned short key = [event keyCode];
	
	// BackSpace.
	if (key == 51) {
		//		_axApp->GetWindowManager()->OnBackSpaceDown();
		//		_axApp->GetPopupManager()->OnBackSpaceDown();
	}
	// Delete
	else if (key == 117) {
		//		_axApp->GetWindowManager()->OnKeyDeleteDown();
		//		_axApp->GetPopupManager()->OnKeyDeleteDown();
	}
	// Enter.
	else if (key == 36) {
		//		_axApp->GetWindowManager()->OnEnterDown();
		//		_axApp->GetPopupManager()->OnEnterDown();
	}
	// Left arrow.
	else if (key == 123) {
		//		_axApp->GetWindowManager()->OnLeftArrowDown();
		//		_axApp->GetPopupManager()->OnLeftArrowDown();
	}
	// Right arrow.
	else if (key == 124) {
		//		_axApp->GetWindowManager()->OnRightArrowDown();
		//		_axApp->GetPopupManager()->OnRightArrowDown();
	}
	// Arrow down.
	else if (key == 125) {
		//		_axApp->GetWindowManager()->OnDownArrowDown();
		//		_axApp->GetPopupManager()->OnDownArrowDown();
	}
	// Arrow up.
	else if (key == 126) {
		//		_axApp->GetWindowManager()->OnUpArrowDown();
		//		_axApp->GetPopupManager()->OnUpArrowDown();
	}
	else {
		//		std::string str = [[event characters] UTF8String];
		//		_axApp->GetWindowManager()->OnKeyDown(str[0]);
		//		_axApp->GetPopupManager()->OnKeyDown(str[0]);
	}
}



- (void)keyDown:(NSEvent*)event
{
	unsigned short key = [event keyCode];
	
	//	ax::Print(key);
	
	ax::core::WindowManager* win_manager = _core->GetWindowManager();
	ax::core::WindowManager* popup_manager = _core->GetPopupManager();
	
	// BackSpace.
	if (key == 51) {
		win_manager->OnBackSpaceDown();
		popup_manager->OnBackSpaceDown();
	}
	// Delete
	else if (key == 117) {
		win_manager->OnKeyDeleteDown();
		popup_manager->OnKeyDeleteDown();
	}
	// Enter.
	else if (key == 36) {
		win_manager->OnEnterDown();
		popup_manager->OnEnterDown();
	}
	// Left arrow.
	else if (key == 123) {
		win_manager->OnLeftArrowDown();
		popup_manager->OnLeftArrowDown();
	}
	// Right arrow.
	else if (key == 124) {
		win_manager->OnRightArrowDown();
		popup_manager->OnRightArrowDown();
	}
	// Arrow down.
	else if (key == 125) {
		win_manager->OnDownArrowDown();
		popup_manager->OnDownArrowDown();
	}
	// Arrow up.
	else if (key == 126) {
		win_manager->OnUpArrowDown();
		popup_manager->OnUpArrowDown();
	}
	else {
		std::string str = [[event characters] UTF8String];
		win_manager->OnKeyDown(str[0]);
		popup_manager->OnKeyDown(str[0]);
	}
}

//-----------------------------------------------------------------------------
// Drawing section.
//-----------------------------------------------------------------------------
// Set origin at top left position.
- (BOOL)isFlipped
{
	return YES;
}

- (void)prepareOpenGL
{
	fst::print("- (void)prepareOpenGL");
	// Synchronize buffer swaps with vertical refresh rate
	GLint swapInt = 1;
	[[self window] setAcceptsMouseMovedEvents:YES];
	[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
	
	// Init OpenGL.
	_cpp_view->OnInit();
	
	// Call main entry.
	_core->CallMainEntryFunction();
	_core->CallAfterGUILoadFunction();
	
	[self setNeedsDisplay:YES];
}

// Each time window has to be redrawn, this method is called
- (void)drawRect:(NSRect)bounds
{
	NSRect backingBounds = [self convertRectToBacking:[self bounds]];
	ax::Size current_size(_core->GetFrameSize());
	
	if (current_size.w != backingBounds.size.width || current_size.h != backingBounds.size.height) {
		ax::Size new_size(
					   [[self window] contentLayoutRect].size.width, [[self window] contentLayoutRect].size.height);
	
		// Resize OpenGL panel.
		_core->ResizeFrame(new_size);
		//[self setFrame:NSMakeRect(0.f, 0.f, new_size.w, new_size.h)];
	
	}
	
	_cpp_view->OnDraw();
	glFlush();
}

@end
