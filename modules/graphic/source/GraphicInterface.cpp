//
//  axGraphicInterface.cpp
//  axLib
//
//  Created by Alexandre Arsenault on 2015-02-17.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "GraphicInterface.hpp"
#include "RenderMath.hpp"
#include "Render.hpp"

namespace ax {
namespace GL {
	void Resize(const ax::Size& size)
	{
		glViewport(0, 0, size.w, size.h);
//
//		glMatrixMode(GL_PROJECTION);
//
//		ax::GL::Math::Matrix4 proj;
//		ax::GL::Math::Ortho2D(proj.Identity().GetData(), size);
//
//		// Select the modelview matrix.
//		glMatrixMode(GL_MODELVIEW);
	}

	void Init()
	{
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

		glEnable(GL_BLEND); // Enable blending.
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// The type of depth testing to do.
//		glDepthFunc(GL_LEQUAL);
//		glDepthFunc(GL_ALWAYS);

		// Really nice perspective calculations.
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}

	void Draw(const ax::Size& size)
	{
// 		// Clear screen and depth buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 		// Set projection matrix.
// 		glMatrixMode(GL_PROJECTION);

// 		ax::GL::Math::Matrix4 proj;
// 		ax::GL::Math::Ortho2D(proj.Identity().GetData(), size);

// 		glMatrixMode(GL_MODELVIEW);
// 		glLoadIdentity();

// 		// Draw bg rectangle.
// 		glColor4f(0.4f, 0.0f, 0.0f, 1.0f);
// 		ax::FloatRect rect(-1.0, -1.0, size.x * 2.0, size.y * 2.0);
// 		ax::Utils::RectPoints<ax::FloatPoint> points = rect.GetPoints();

// #ifdef ANDROID
// 		GLubyte indices[] = { 0, 1, 2, 2, 3 };
// 		glEnableClientState(GL_VERTEX_ARRAY);
// 		glVertexPointer(2, GL_FLOAT, 0, &points);
// 		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_BYTE, indices);
// 		glDisableClientState(GL_VERTEX_ARRAY);
// #else
// //		GLubyte indices[] = { 0, 1, 2, 2, 3 };
// //		glEnableClientState(GL_VERTEX_ARRAY);
// //		glVertexPointer(2, GL_FLOAT, 0, &points);
// //		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_BYTE, indices);
// //		glDisableClientState(GL_VERTEX_ARRAY);
// #endif
	}

	void BlockDrawing(const ax::Rect& abs_rect, const ax::Rect& shown_rect,
		const ax::Size& frameSize)
	{
		ax::GL::Math::Matrix4 mview;
		mview.Identity().Load();

		double delta_size_y = shown_rect.size.h - abs_rect.size.h;
		double globalY = frameSize.h;

		double sumY = (abs_rect.position.y + shown_rect.position.y
			+ abs_rect.size.h + delta_size_y);

		glScissor(GLint(abs_rect.position.x + shown_rect.position.x),
			GLint(globalY - sumY), GLint(shown_rect.size.w + 1),
			GLint(shown_rect.size.h));

		glEnable(GL_SCISSOR_TEST);
	}

	void UnBlockDrawing()
	{
		glDisable(GL_SCISSOR_TEST);
	}
}
}
