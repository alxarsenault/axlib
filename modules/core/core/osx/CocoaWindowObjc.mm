#include "CocoaWindowObjc.h"
#include <fst/print.h>
#include "Render.hpp"
#include "Util.hpp"
#include "Matrix4x4.hpp"

#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

@implementation CocoaWindowObjc

- (void) SetSize:(NSSize)size
{
    [_ns_window setContentSize:size];
//    [_ns_window setFrame:NSMakeRect(0.f, 0.f, size.width, size.height)];
    
}

- (id)initWithRect:(NSRect)contentSize
{
    if ( self = [super initWithFrame:contentSize] ) {        
        // allocate window
        unsigned int frame_style_flags = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
        NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;
        
        _ns_window = [[NSWindow alloc] initWithContentRect:contentSize
            styleMask:frame_style_flags backing:NSBackingStoreBuffered defer:FALSE];
        
        [_ns_window setTitle:@"test string"];
        
        [_ns_window makeKeyAndOrderFront: _ns_window];
        
        [_ns_window setContentView:self];
        
        [_ns_window display];
        
        [self wantsBestResolutionOpenGLSurface];
        
        
        _context.Init();
        _context.Resize(ax::Size(contentSize.size.width, contentSize.size.height));
        ///////////////////////
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
        
    }
    
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}

- (void) drawRect: (NSRect) bounds
{
    
//    glClearColor(0, 0, 0, 0);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1.0f, 0.85f, 0.35f);
//    glBegin(GL_TRIANGLES);
//    {
//        glVertex3f(  0.0,  0.6, 0.0);
//        glVertex3f( -0.2, -0.3, 0.0);
//        glVertex3f(  0.2, -0.3 ,0.0);
//    }
//    glEnd();
//    glFlush();
    
    
    _context.Clear();
    _context.Resize(ax::Size(bounds.size.width, bounds.size.height));
    
//    ax::Size global_size = ax::App::GetInstance().GetFrameSize();
    
    // Projection matrix.
    glm::mat4 projMat = glm::ortho((float)0.0, (float)bounds.size.width, (float)bounds.size.height, (float)0.0);
    
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

- (void)lockFocus
{
    NSOpenGLContext* context = [self openGLContext];
    
    [super lockFocus];
    if ([context view] != self) {
        [context setView:self];
    }
    [context makeCurrentContext];
}

//void OpenGLView::SetFrameSize(const ax::Size& size) {
//    NSSize nSize = { static_cast<CGFloat>(size.w), static_cast<CGFloat>(size.h) };
//    [[(CocoaAppDelegate*)_app_delegate window] setContentSize:nSize];
//    [(CocoaAppDelegate*)_app_delegate setFrame:NSMakeRect(0.f, 0.f, size.w, size.h)];
//}

//- (void)viewDidMoveToWindow
//{
//    fst::print("(void)viewDidMoveToWindow");
//    [self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:YES];
//    [[self window] makeFirstResponder:self];
//    [[self window] setAcceptsMouseMovedEvents:YES];
//}

- (void)rightMouseDown:(NSEvent*)event
{
    fst::print("CocoaWindowController -> right down");
}

@end
