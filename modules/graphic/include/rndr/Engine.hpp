
#pragma once

#include <vector>
#include "Context.hpp"

namespace ax {
namespace rndr {
	class Engine {
	public:
        inline static Engine& GetInstance() {
            static Engine engine;
            return engine;
        }
        
        unsigned long CreateContext();
        
        Context* GetContext(unsigned long id);
        
    private:
        Engine();
        
        std::vector<Context> _contexts;
	};

} // rndr.
} // ax.
