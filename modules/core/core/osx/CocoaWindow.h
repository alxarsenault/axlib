#pragma once

#include "Util.hpp"
#include "FrameInterface.hpp"



namespace cocoa {
    namespace bridge {
    struct CocoaWindow;
    }
    
    class Window : public ax::FrameInterface {
    public:
        Window(const ax::Rect& rect);
        
        virtual void SetSize(const ax::Size& size);
        
    private:
        bridge::CocoaWindow* _cocoa_window;
    };
}
