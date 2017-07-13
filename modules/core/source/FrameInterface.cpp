#include "FrameInterface.hpp"
#include "Engine.hpp"

#include <fst/print.h>
#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

namespace ax {
    FrameInterface::FrameInterface(): _debug_int(234)
    {
        
    }
    
    void FrameInterface::Init(const ax::Size& size)
    {
        fst::print("FrameInterface::Init()");
        _context_id = ax::rndr::Engine::GetInstance().CreateContext();
        
        ax::rndr::Context* context = ax::rndr::Engine::GetInstance().GetContext(_context_id);
        	if (context == nullptr) {
        		return;
        	}
        
        const char* v_normal("uniform sampler2D texture1; 						\
                             uniform mat4 mvp_matrix;							\
                             attribute vec4 vPosition;							\
                             attribute vec4 vColor;								\
                             varying vec4 fragColor;							\
                             \
                             void main()										\
                             {													\
                             fragColor = vColor;								\
                             gl_Position = mvp_matrix * vPosition;			\
                             }													");
        
        // Normal fragment shader.
        const char* f_normal("varying vec4 fragColor;							\
                             uniform sampler2D texture1;						\
                             \
                             void main()										\
                             {													\
                             gl_FragColor = fragColor;						\
                             }													");
        _shader.compile(v_normal, f_normal);
        _shader.link({{0, "vPosition"}, {1, "vTexCoord"}, {2, "vColor"}});
        
        
        context->Init();
        context->Resize(size);
    }
    
    void FrameInterface::OnDraw(const ax::Size& size)
    {
        
        ax::rndr::Context* context = ax::rndr::Engine::GetInstance().GetContext(_context_id);
        if (context == nullptr) {
            return;
        }
        
        context->Clear();
        context->Resize(size);
        
        //    ax::Size global_size = ax::App::GetInstance().GetFrameSize();
        
        // Projection matrix.
        glm::mat4 projMat = glm::ortho((float)0.0, (float)size.w, (float)size.h, (float)0.0);
        
        ax::FRect frect(50.0, 50.0, 200.0, 20.0);
        
        // Order : bl, tl, tr, br.
        ax::util::RectPoints<ax::FPoint> points(frect.GetPoints<ax::FPoint>());
        
        ax::Color c0(ax::Color(255, 200, 200));
        ax::Color colors[4] = { c0, c0, ax::Color(0, 200, 200), c0 };
        
        _shader.activate();
        
        // ModelViewProjection matrix.
        //    ax::rndr::Matrix4x4<float> ind = ax::rndr::Matrix4x4<float>::Identity();
        glUniformMatrix4fv(
                           _shader.get_uniform_location("mvp_matrix"), 1, GL_FALSE, (float*)&projMat[0][0]);//(float*)ind.data());
        
        // Vertex coordinates.
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &points);
        glEnableVertexAttribArray(0);
        
        // Color coordinates.
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
        glEnableVertexAttribArray(2);
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(2);
        
        glFlush();
    }
} // ax.
