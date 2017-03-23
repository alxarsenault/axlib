#include "Engine.hpp"

namespace ax {
    namespace rndr {
        Engine::Engine()
        {
            
        }
        
        unsigned long Engine::CreateContext()
        {
            Context context;
            unsigned long id = context.GetId();
            _contexts.push_back(context);
            return id;
        }
        
        Context* Engine::GetContext(unsigned long id)
        {
            for(auto& n : _contexts) {
                if(n.GetId() == id) {
                    return &n;
                }
            }
            
            return nullptr;
        }
        
        
    } // rndr.
} // ax.
