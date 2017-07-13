#include "CocoaWindow.h"
#include "CocoaWindowObjc.h"

namespace cocoa {
Window::Window(const ax::Rect& rect)
{
    CocoaWindowObjc * window = [[CocoaWindowObjc alloc]
                                initWithRect:NSMakeRect(rect.position.x, rect.position.y, rect.size.w, rect.size.h) frame:this];
    
    _cocoa_window = static_cast<bridge::CocoaWindow*>(window);
//    [window SetWindow:this];
}
    
void Window::SetSize(const ax::Size& size)
{
    NSSize nSize = { static_cast<CGFloat>(size.w), static_cast<CGFloat>(size.h) };
    CocoaWindowObjc* window = static_cast<CocoaWindowObjc*>(_cocoa_window);
    [window SetSize:nSize];
}
} // cocoa.
