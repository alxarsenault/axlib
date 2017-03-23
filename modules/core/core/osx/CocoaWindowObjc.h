#pragma once

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>


#include "Context.hpp"
#include "shader.h"


@interface CocoaWindowObjc : NSOpenGLView
{
    NSWindow* _ns_window;
    ax::rndr::Context _context;
    ax::rndr::shader _shader;
}

- (void) SetSize:(NSSize)size;

- (id) initWithRect:(NSRect)contentSize;

- (void) lockFocus;

- (BOOL)isFlipped;

- (void) drawRect: (NSRect) bounds;

- (void) rightMouseDown:(NSEvent*)evt;

@end


