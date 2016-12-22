#pragma once

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

namespace ax {
	namespace core {
		class CoreMac;
	}
}

namespace cocoa {
	class OpenGLView;
}

typedef cocoa::OpenGLView CppView;

@interface CocoaAppDelegate : NSOpenGLView <NSApplicationDelegate>
{
	NSWindow* _ns_window;
	cocoa::OpenGLView* _cpp_view;
	ax::core::CoreMac* _core;
}

- (id)initWithRect:(NSRect)contentSize core:(ax::core::CoreMac*)core cpp_view:(CppView*)cpp_view;

- (void)RefreshView;

- (void)installRunLoopObserver;

// Close application when clicking on the top left red "x" button.
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication;

- (void)viewDidMoveToWindow;

- (void)windowWillStartLiveResize:(NSNotification *)notification;

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize;

- (void)windowDidResize:(NSNotification*)notification;

- (void)windowDidMove:(NSNotification*)notification;

- (void)SetNotResizable;
- (void)SetResizable;
- (void)SetNoTitleBar;
- (void)SetTitleBar;

- (void)SetFocusAndCenter;

//-------------------
// Mouse events.
//-------------------
- (void)mouseMoved:(NSEvent*)evt;
- (void)mouseDragged:(NSEvent*)evt;
- (void)mouseUp:(NSEvent*)evt;
- (void)rightMouseDown:(NSEvent*)evt;
- (void)mouseDown:(NSEvent*)evt;
- (void)scrollWheel:(NSEvent*)evt;
- (id)ChangeMouseCursor:(int)cursor_id;

//-------------------
// Key events.
//-------------------
- (void)flagsChanged:(NSEvent*)evt;
- (void)keyUp:(NSEvent*)evt;
- (void)keyDown:(NSEvent*)evt;

-(BOOL) canBecomeKeyWindow;

//---------------------
// Drawing section.
//---------------------

- (BOOL)isFlipped;

- (void)prepareOpenGL;

- (void)drawRect:(NSRect)bounds;

@end

