#include "Context.hpp"


namespace ax {
    namespace rndr {
        Context::Context()
        {
            static unsigned long id_count = 0;
            _id = id_count++;
        }
        
        void Context::SetGLContext(GLContext* gl_context)
        {
            _gl_context = gl_context;
        }
        
        void Context::Init()
        {
            MakeCurrent();
            
            // Enable Smooth Shading.
            glShadeModel(GL_SMOOTH);
            
            // Black Background
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            
            // Depth Buffer Setup
#ifdef ANDROID
            glClearDepthf(1.0f);
#else
            glClearDepth(1.0f);
#endif
            
            // Enables Depth Testing
            glEnable(GL_DEPTH_TEST);
            
            // glEnable(GL_CULL_FACE);
            
            // Enable blending.
            glEnable(GL_BLEND);
        }
        
        void Context::Resize(const ax::Size& size)
        {
            MakeCurrent();
            glViewport(0, 0, size.w, size.h);

        }
        
        void Context::Clear()
        {
            MakeCurrent();
            
            // Clear screen and depth buffer.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        
        bool Context::IsCurrent() const
        {
            return true;
        }
        
        void Context::MakeCurrent()
        {
            /// @todo Set as current context (Platform dependant).
        }
        
        //
        // Private.
        //
        
        
        
        
    } // rndr.
} // ax.
