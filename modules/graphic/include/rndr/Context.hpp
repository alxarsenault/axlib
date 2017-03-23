#pragma once

#include "GL.hpp"
#include "Util.hpp"

namespace ax {
namespace rndr {
	class Context {
	public:
		Context();

		void SetGLContext(GLContext* gl_context);

		void Init();

		void Resize(const ax::Size& size);

		void Clear();

		bool IsCurrent() const;
        
        void MakeCurrent();
        
        unsigned long GetId() const {
            return _id;
        }

	private:
		GLContext* _gl_context = nullptr;
        unsigned long _id;
	};

} // rndr.
} // ax.
