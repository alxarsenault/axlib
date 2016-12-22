#include "CocoaOpenGLView.h"
#include "axCoreMac.hpp"
#include <fst/print.h>

namespace cocoa {
void OpenGLView::OnInit()
{
	// fst::print(ptrace);
	_core->InitGL();
	_core->ResizeFrame(_core->GetFrameSize());
}

void OpenGLView::OnDraw()
{
	// fst::print(ptrace);
	_core->DrawGLScene();
}

ax::core::CoreMac* OpenGLView::GetCore()
{
	return _core;
}
}
