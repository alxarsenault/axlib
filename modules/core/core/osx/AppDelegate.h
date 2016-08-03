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
#import <Cocoa/Cocoa.h>

//NSOpenGLView,
//NSOpenGLView,
namespace ax
{
    class App;
}

@interface axAppDelegate : NSOpenGLView
{
    ax::App* _axApp;
}


// Windows paint callback.
- (void) drawRect: (NSRect)bounds;

// Mouse mouve event.
- (void) mouseMoved:(NSEvent *) evt;

- (void) windowDidResize:(NSNotification *)notification;
- (void) windowDidMove:(NSNotification *)notification;

//- (void) setFrameSize:(NSSize)newSize;
- (void) SetFrameSize:(NSSize)newSize;
- (void) itemChanged:(NSMenuItem *)anObject;

-(BOOL) canBecomeKeyWindow;

- (void) flagsChanged: (NSEvent *)theEvent;

- (id)ChangeMouseCursor:(int)cursor_id;
- (id) MemberTestFunc;
-(void)SetNotResizable;
-(void)SetResizable;
-(void)SetNoTitleBar;
-(void)SetTitleBar;

-(void)SetFocusAndCenter;

-(void)renderTimer:(NSTimer *)timer;

- (BOOL)application:(NSApplication *)app
		   openFile:(NSString *)filename;

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (void)applicationWillTerminate:(NSNotification *)aNotification;

@property(assign) id< NSApplicationDelegate > delegate;
@end

extern axAppDelegate* GlobalAppDelegate;




