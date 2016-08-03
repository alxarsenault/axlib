
#ifdef ANDROID
#include <EGL/egl.h> // requires ndk r5 or newer
#include <GLES/gl.h>
#include <GLES2/gl2.h>

#elif WAYLAND
#include "GL/gl.h"
#include "GL/glext.h"
#include "wayland-egl.h"
#include "EGL/egl.h"

#elif axCoreX11
#include "GL/glew.h"

#include "GL/gl.h"
#include "GL/glext.h"
#include "GL/glx.h"

#elif _MSC_VER
#include <windows.h>
#include "GL/glew.h"
//#include <gl\gl.h>
#include <gl\glu.h>

#else //__APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#endif // __APPLE__
