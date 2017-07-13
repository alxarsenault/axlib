#pragma once

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>


//#include "Context.hpp"
#include "shader.h"
#include "FrameInterface.hpp"


//namespace cocoa {
//    class Window;
//}

@interface CocoaWindowObjc : NSOpenGLView
{
    NSWindow* _ns_window;
//    ax::rndr::Context _context;
    ax::rndr::shader _shader;
    ax::FrameInterface* _frame_interface;
//    cocoa::Window* _cc_window;
}

//- (void) SetWindow:(cocoa::Window*)window;

- (void) SetSize:(NSSize)size;

- (id) initWithRect:(NSRect)contentSize frame:(ax::FrameInterface*) frame_interface;

- (void) lockFocus;

- (BOOL)isFlipped;

- (void) drawRect: (NSRect) bounds;

- (void) rightMouseDown:(NSEvent*)evt;

@end


