/*
 * Copyright (c) 2013 Alexandre Arsenault.
 *
 * This file is part of axLibrary.
 *
 * axLibrary is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axLibrary License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLibrary. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLibrary, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */
#include "GC.hpp"
#include "RenderMath.hpp"
#include <cmath>

#include "Render.hpp"
#include <algorithm>

#ifdef ANDROID
#define LOG_TAG "EglSample"
#define LOG_INFO(x)
#endif

ax::GL::Shader ax::GC::shader_fb;
ax::GL::Shader ax::GC::shader_normal;
ax::GL::Shader ax::GC::shader_font;
ax::GL::Shader ax::GC::shader_image;
ax::GL::Shader ax::GC::shader_image_alpha;
ax::GL::Shader ax::GC::shader_image_color;
glm::mat4 ax::GC::mvp_matrix;
ax::Color ax::GC::current_color;

void axGlColor4(float r, float g, float b, float a)
{
	glColor4f(r, g, b, a);
}

ax::GC::GC()
{
}

ax::FRect ax::GC::RectToFRect(const ax::Rect& rect)
{
	return ax::FRect(float(rect.position.x), float(rect.position.y), float(rect.size.w), float(rect.size.h));
}

void ax::GC::SetColor(const float& r, const float& g, const float& b)
{
	current_color = ax::Color(r, g, b, 1.0f);
	axGlColor4(r, b, g, 1.0);
}

void ax::GC::SetColor(const float& r, const float& g, const float& b, const float& a)
{
	current_color = ax::Color(r, g, b, a);
	axGlColor4(r, g, b, a);
}

void ax::GC::SetColor(const ax::Color& color)
{
	current_color = color;
	axGlColor4(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

void ax::GC::SetColor(const ax::Color& color, const float& alpha)
{
	current_color = color;
	current_color.SetAlpha(alpha);
	axGlColor4(color.GetRed(), color.GetGreen(), color.GetBlue(), alpha);
}

void ax::GC::DrawRectangle(const ax::Rect& rect)
{
	ax::FRect frect = RectToFRect(rect);

	// Order : bl, tl, tr, br.
	ax::math::RectPoints<ax::FPoint> points(frect.GetPoints<ax::FPoint>());

	ax::Color& c0(current_color);
	ax::Color colors[4] = { c0, c0, c0, c0 };

	shader_normal.Activate();

	// ModelViewProjection matrix.
	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &points);
	glEnableVertexAttribArray(0);

	// Color coordinates.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void ax::GC::DrawRectangleContour(const ax::Rect& rect, float linewidth)
{
	ax::FRect frect = ax::GC::RectToFRect(rect);

	// Note that OpenGL coordinate space has no notion of integers,
	// everything is a float and the "centre" of an OpenGL pixel is
	// really at the 0.5,0.5 instead of it's top-left corner.
	// Therefore, if you want a 1px wide line from 0,0 to 10,10 inclusive,
	// you really had to draw a line from 0.5,0.5 to 10.5,10.5.

	frect.position.x -= 0.5; // Seems to be only on linux and mac.

	glLineWidth(linewidth);

	// Order : bl, tl, tr, br.
	ax::math::RectPoints<ax::FPoint> points = frect.GetPoints<ax::FPoint>();

	GLubyte indices[] = { 1, 2, 2, 3, 3, 0, 0, 1 };

	ax::Color& c0(current_color);
	ax::Color colors[4] = { c0, c0, c0, c0 };

	shader_normal.Activate();

	// ModelViewProjection matrix.
	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &points);
	glEnableVertexAttribArray(0);

	// Color coordinates.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors);
	glEnableVertexAttribArray(2);

	glDrawElements(GL_LINE_LOOP, 8, GL_UNSIGNED_BYTE, indices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	glLineWidth(1.0f);
}

void DrawQuarterCircleContour(
	const ax::FPoint& pos, const int& radius, const double& angle, const int& nSegments)
{
#ifdef ANDROID
#else
	glBegin(GL_LINES);
	for (int i = 1; i < nSegments; i++) {
		// Get the current angle.
		double theta = (2.0f * M_PI) * 0.25 * (double(i - 1)) / double(nSegments);

		double x = radius * cosf(theta + angle);
		double y = radius * sinf(theta + angle);

		glVertex2d(x + pos.x, y + pos.y);

		theta = (2.0f * M_PI) * 0.25 * (double(i)) / double(nSegments);

		x = radius * cosf(theta + angle);
		y = radius * sinf(theta + angle);
		glVertex2d(x + pos.x, y + pos.y);
	}
	glEnd();
#endif
}

void ax::GC::DrawRoundedRectangleContour(const ax::Rect& rect, const int& radius)
{
	int r = radius;

	if (r > rect.size.h * 0.5) {
		r = rect.size.h * 0.5;
	}

	int nSegments = 10;
	ax::FRect frect = RectToFRect(rect);

	glBegin(GL_LINES);

	// Top line.
	glVertex2d(frect.position.x + r - 2, frect.position.y);

	glVertex2d(frect.position.x + frect.size.w - r + 2, frect.position.y);

	// Bottom line.
	glVertex2d(frect.position.x + r - 2, frect.position.y + frect.size.w);

	glVertex2d(frect.position.x + frect.size.w - r + 2, frect.position.y + frect.size.h);

	// Left line.
	glVertex2d(frect.position.x, frect.position.y + r - 2);

	glVertex2d(frect.position.x, frect.position.y + frect.size.h - r + 2);

	// Right line.
	glVertex2d(frect.position.x + +frect.size.w, frect.position.y + r - 2);

	glVertex2d(frect.position.x + +frect.size.w, frect.position.y + frect.size.h - r + 2);
	glEnd();

	// Bottom right.
	DrawQuarterCircleContour(
		ax::FPoint(frect.position.x + frect.size.w - r, frect.position.y + frect.size.h - r), r, 0,
		nSegments);

	// Top left.
	DrawQuarterCircleContour(
		ax::FPoint(frect.position.x + r - 1, frect.position.y + r - 1), r, M_PI, nSegments);

	// Top right.
	DrawQuarterCircleContour(ax::FPoint(frect.position.x + frect.size.w - r, frect.position.y + r - 1), r,
		3.0 * M_PI * 0.5, nSegments);

	// Bottom left.
	DrawQuarterCircleContour(
		ax::FPoint(frect.position.x + r - 1, frect.position.y + frect.size.h - r), r, M_PI * 0.5, nSegments);
}

void DrawQuarterCircleContourSmooth(
	ax::GC* gc, const ax::FPoint& pos, const int& radius, const double& angle, const int& nSegments)
{
#ifdef ANDROID
#else
	//    glBegin(GL_LINES);
	for (int i = 1; i < nSegments; i++) {
		// Get the current angle.
		double theta = (2.0f * M_PI) * 0.25 * (double(i - 1)) / double(nSegments);

		double x = radius * cosf(theta + angle);
		double y = radius * sinf(theta + angle);

		//        glVertex2d(x + pos.x, y + pos.y);

		ax::Point pt1(x + pos.x, y + pos.y);
		theta = (2.0f * M_PI) * 0.25 * (double(i)) / double(nSegments);

		x = radius * cosf(theta + angle);
		y = radius * sinf(theta + angle);

		ax::Point pt2(x + pos.x, y + pos.y);
		//        glVertex2d(x + pos.x, y + pos.y);

		gc->DrawSmouthLine(pt1, pt2, 3);
	}
//    glEnd();
#endif
}

void ax::GC::DrawRoundedRectangleContourSmooth(const ax::Rect& rect, const int& radius)
{
#ifdef ANDROID
#else
	int r = radius;

	if (r > rect.size.h * 0.5) {
		r = rect.size.h * 0.5;
	}

	int nSegments = 5;
	ax::FRect frect = RectToFRect(rect);

	glLineWidth(2.0f);
	glEnable(GL_LINE_SMOOTH);
	//    glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glBegin(GL_LINES);

	// Top line.
	DrawSmouthLine(ax::Point(frect.position.x + r - 2, frect.position.y),
		ax::Point(frect.position.x + frect.size.w - r + 2, frect.position.y));

	// Bottom line.
	DrawSmouthLine(ax::Point(frect.position.x + r - 2, frect.position.y + frect.size.h),
		ax::Point(frect.position.x + frect.size.w - r + 2, frect.position.y + frect.size.h));

	//    DrawSmouthLine();
	//    DrawSmouthLine();
	// Top line.
	//    glVertex2d(frect.position.x + r - 2,
	//               frect.position.y);
	//
	//    glVertex2d(frect.position.x + frect.size.w - r + 2,
	//               frect.position.y);
	//
	//    // Bottom line.
	//    glVertex2d(frect.position.x + r - 2,
	//               frect.position.y + frect.size.h);
	//
	//    glVertex2d(frect.position.x + frect.size.w - r + 2,
	//               frect.position.y + frect.size.h);
	//
	//    // Left line.
	//    glVertex2d(frect.position.x,
	//               frect.position.y + r - 2);
	//
	//    glVertex2d(frect.position.x,
	//               frect.position.y + frect.size.h - r + 2);
	//
	//    // Right line.
	//    glVertex2d(frect.position.x + + frect.size.w,
	//               frect.position.y + r - 2);
	//
	//    glVertex2d(frect.position.x + + frect.size.w,
	//               frect.position.y + frect.size.h - r + 2);
	//    glEnd();

	// Bottom right.
	DrawQuarterCircleContourSmooth(this,
		ax::FPoint(frect.position.x + frect.size.w - r, frect.position.y + frect.size.h - r), r, 0,
		nSegments);

	// Top left.
	DrawQuarterCircleContourSmooth(
		this, ax::FPoint(frect.position.x + r, frect.position.y + r), r, M_PI, nSegments);

	// Top right.
	DrawQuarterCircleContourSmooth(this,
		ax::FPoint(frect.position.x + frect.size.w - r, frect.position.y + r), r, 3.0 * M_PI * 0.5,
		nSegments);

	// Bottom left.
	DrawQuarterCircleContourSmooth(this,
		ax::FPoint(frect.position.x + r, frect.position.y + frect.size.h - r), r, M_PI * 0.5, nSegments);

	glDisable(GL_LINE_SMOOTH);
	glLineWidth(1.0f);
//    glDisable(GL_POLYGON_SMOOTH);
#endif
}

void ax::GC::DrawQuarterCircle(
	const ax::FPoint& pos, const int& radius, const double& angle, const int& nSegments)
{
	ax::Color& c0(ax::GC::current_color);

	std::vector<ax::FPoint> points;
	points.reserve(nSegments + 1);
	points.push_back(ax::FPoint(pos.x, pos.y));

	std::vector<ax::Color> colors;
	colors.reserve(nSegments + 1);
	colors.push_back(c0);

	double quarter_pi_ratio = 2.0 * M_PI * 0.25 / double(nSegments);
	for (int i = 0; i <= nSegments; i++) {
		double theta = double(i) * quarter_pi_ratio;
		double x = radius * cosf(theta + angle);
		double y = radius * sinf(theta + angle);
		points.push_back(ax::FPoint(x + pos.x, y + pos.y));
		colors.push_back(c0);
	}

	ax::GC::shader_normal.Activate();

	// ModelViewProjection matrix.
	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)points.data());
	glEnableVertexAttribArray(0);

	// Colors.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors.data());
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)points.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void ax::GC::DrawQuarterCircle(const ax::FPoint& pos, const int& radius, const double& angle,
	const int& nSegments, const ax::Color& middle, const ax::Color& around)
{
	std::vector<ax::FPoint> points;
	points.reserve(nSegments + 1);
	points.push_back(ax::FPoint(pos.x, pos.y));

	std::vector<ax::Color> colors;
	colors.reserve(nSegments + 1);
	colors.push_back(middle);

	double quarter_pi_ratio = 2.0 * M_PI * 0.25 / double(nSegments);
	for (int i = 0; i <= nSegments; i++) {
		double theta = double(i) * quarter_pi_ratio;
		double x = radius * cosf(theta + angle);
		double y = radius * sinf(theta + angle);
		points.push_back(ax::FPoint(x + pos.x, y + pos.y));
		colors.push_back(around);
	}

	// ModelViewProjection matrix.
	glUniformMatrix4fv(ax::GC::shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE,
		(float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)points.data());
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors.data());
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)points.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void ax::GC::DrawRoundedRectangle(const ax::Rect& rect, const int& radius)
{
	int r = radius;

	if (r > rect.size.h * 0.5) {
		r = rect.size.h * 0.5;
	}

	int nSegments = 40;
	ax::FRect frect = RectToFRect(rect);

	// Middle.
	DrawRectangle(ax::Rect(
		frect.position.x + r - 1, frect.position.y - 1, frect.size.w - 2.0 * r + 1, frect.size.h + 1));

	int size_rect_height = frect.size.h - 2.0 * r + 1;

	if (size_rect_height > 0) {
		// Left.
		DrawRectangle(ax::Rect(frect.position.x - 1, frect.position.y + r - 1, r, size_rect_height));

		// Right.
		DrawRectangle(
			ax::Rect(frect.position.x + frect.size.w - r, frect.position.y + r - 1, r + 1, size_rect_height));
	}

	// Bottom right.
	DrawQuarterCircle(ax::FPoint(frect.position.x + frect.size.w - r, frect.position.y + frect.size.h - r), r,
		0, nSegments);

	// Top left.
	DrawQuarterCircle(ax::FPoint(frect.position.x + r - 1, frect.position.y + r - 1), r, M_PI, nSegments);

	// Top right.
	DrawQuarterCircle(ax::FPoint(frect.position.x + frect.size.w - r, frect.position.y + r - 1), r,
		3.0 * M_PI * 0.5, nSegments);

	// Bottom left.
	DrawQuarterCircle(
		ax::FPoint(frect.position.x + r - 1, frect.position.y + frect.size.h - r), r, M_PI * 0.5, nSegments);
}

void ax::GC::DrawTexture(GLuint texture, const ax::Rect& rect, ax::Color color)
{
	//#ifdef ANDROID
	ax::Point pos = rect.position;
	ax::Size img_size = rect.size;

	float vertices[8] = {
		(float)pos.x, (float)pos.y, // Top-left.
		(float)pos.x, (float)pos.y + img_size.h, // Bottom-left.
		(float)pos.x + img_size.w, (float)pos.y + img_size.h, // Bottom-right.
		(float)pos.x + img_size.w, (float)pos.y // Top-right.
	};

	float tex_coords[8] = {
		0.0, 0.0, // Top-left.
		0.0, 1.0, // Bottom-left.
		1.0, 1.0, // Bottom-right.
		1.0, 0.0 // Top-right.
	};

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	// Texture coordinate.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDisable(GL_TEXTURE_2D);
}

struct axRectPointsOrder {
	axRectPointsOrder()
	{
	}
	axRectPointsOrder(const ax::math::RectPoints<ax::FPoint>& points)
		: top_left(points.top_left)
		, top_right(points.top_right)
		, bottom_left(points.bottom_left)
		, bottom_right(points.bottom_right)
	{
	}
	axRectPointsOrder(const ax::FPoint& tl, const ax::FPoint& tr, const ax::FPoint& bl, const ax::FPoint& br)
		: top_left(tl)
		, top_right(tr)
		, bottom_left(bl)
		, bottom_right(br)
	{
	}

	ax::FPoint top_left, top_right, bottom_left, bottom_right;
};

void ax::GC::DrawImage(ax::Image* img, const ax::Point& position, float alpha)
{
	ax::Point pos = position;
	ax::Size img_size = img->GetSize();

	float vertices[8] = {
		(float)pos.x, (float)pos.y, // Top-left.
		(float)pos.x, (float)pos.y + img_size.h, // Bottom-left.
		(float)pos.x + img_size.w, (float)pos.y + img_size.h, // Bottom-right.
		(float)pos.x + img_size.w, (float)pos.y // Top-right.
	};

	float tex_coords[8] = {
		0.0, 1.0, // Top-left.
		0.0, 0.0, // Bottom-left.
		1.0, 0.0, // Bottom-right.
		1.0, 1.0 // Top-right.
	};

	if (alpha == 1.0f) {
		shader_image.Activate();
		GLuint prog_id = ax::GC::shader_image.GetProgramId();
		GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);
	}
	else {
		shader_image_alpha.Activate();
		GLuint prog_id = ax::GC::shader_image_alpha.GetProgramId();
		GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, img->GetTexture());

	glDepthMask(GL_TRUE);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	// Texture coordinates.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisable(GL_TEXTURE_2D);
}

void ax::GC::DrawImageResizeColor(
	ax::Image* img, const ax::Point& pos, const ax::Size& size, const ax::Color& color)
{
	//	ax::Point pos = position;
	ax::Size img_size = size;

	float vertices[8] = {
		(float)pos.x, (float)pos.y, // Top-left.
		(float)pos.x, (float)pos.y + img_size.h, // Bottom-left.
		(float)pos.x + img_size.w, (float)pos.y + img_size.h, // Bottom-right.
		(float)pos.x + img_size.w, (float)pos.y // Top-right.
	};

	float tex_coords[8] = {
		0.0, 1.0, // Top-left.
		0.0, 0.0, // Bottom-left.
		1.0, 0.0, // Bottom-right.
		1.0, 1.0 // Top-right.
	};

	ax::Color c0(color);
	ax::Color colors[4] = { c0, c0, c0, c0 };

	shader_image_color.Activate();

	GLuint prog_id = ax::GC::shader_image_color.GetProgramId();
	GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, img->GetTexture());

	glDepthMask(GL_TRUE);

	// Pre-calculated alpha.
	//	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	// Texture coordinates.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	glEnableVertexAttribArray(1);

	// Colors coordinates.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE,
	//						GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
}

void ax::GC::DrawImageColor(ax::Image* img, const ax::Point& position, const ax::Color& color)
{
	ax::Point pos = position;
	ax::Size img_size = img->GetSize();

	float vertices[8] = {
		(float)pos.x, (float)pos.y, // Top-left.
		(float)pos.x, (float)pos.y + img_size.h, // Bottom-left.
		(float)pos.x + img_size.w, (float)pos.y + img_size.h, // Bottom-right.
		(float)pos.x + img_size.w, (float)pos.y // Top-right.
	};

	float tex_coords[8] = {
		0.0, 1.0, // Top-left.
		0.0, 0.0, // Bottom-left.
		1.0, 0.0, // Bottom-right.
		1.0, 1.0 // Top-right.
	};

	ax::Color c0(color);
	ax::Color colors[4] = { c0, c0, c0, c0 };

	shader_image_color.Activate();

	GLuint prog_id = ax::GC::shader_image_color.GetProgramId();
	GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, img->GetTexture());

	glDepthMask(GL_TRUE);

	// Pre-calculated alpha.
	//	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	// Texture coordinates.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	glEnableVertexAttribArray(1);

	// Colors coordinates.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE,
	//						GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
}

void ax::GC::DrawImageResize(
	ax::Image* img, const ax::Point& position, const ax::Size& size, float alpha, bool vertical_inversion)
{
	glColor4f(1.0, 1.0, 1.0, alpha);
	ax::Color c0(1.0f, 1.0f, 1.0f, alpha);
	ax::Color colors[4] = { c0, c0, c0, c0 };

	ax::Point pos = position;
	ax::Size img_size = size;

	float vertices[8] = {
		(float)pos.x, (float)pos.y, // Top-left.
		(float)pos.x, (float)pos.y + img_size.h, // Bottom-left.
		(float)pos.x + img_size.w, (float)pos.y + img_size.h, // Bottom-right.
		(float)pos.x + img_size.w, (float)pos.y // Top-right.
	};

	float tex_coords[8] = { 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0 };
	float tex_coords_inv[8] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };

	//	ax::GC::shader_image.Activate();

	if (alpha == 1.0f) {
		shader_image.Activate();

		GLuint prog_id = ax::GC::shader_image.GetProgramId();
		GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);
	}
	else {
		shader_image_alpha.Activate();

		GLuint prog_id = ax::GC::shader_image_alpha.GetProgramId();
		GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, img->GetTexture());

	//	glDepthMask(GL_TRUE);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	// Texture coordinates.
	if (vertical_inversion) {
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords_inv);
	}
	else {
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	}
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glDisable(GL_TEXTURE_2D);
}

void ax::GC::DrawPartOfImage(ax::Image* img, const ax::Point& posInImage, const ax::Size& sizeInImage,
	const ax::Point& position, float alpha)
{
	ax::Point pos = position;
	ax::Size img_size = img->GetSize();

	double img_x = (posInImage.x + sizeInImage.w) / double(img_size.w),
		   img_y = 1.0 - (posInImage.y + sizeInImage.h) / double(img_size.h);

	double x = posInImage.x / double(img_size.w);
	double y = 1.0 - posInImage.y / double(img_size.h);

	glColor4f(1.0, 1.0, 1.0, 1.0);

	float vertices[8] = {
		(float)pos.x, (float)pos.y, // Top-left.
		(float)pos.x, (float)pos.y + sizeInImage.h - 1, // Bottom-left.
		(float)pos.x + sizeInImage.w - 1,
		(float)pos.y + sizeInImage.h - 1, // Bottom-right.
		(float)pos.x + sizeInImage.w - 1, (float)pos.y // Top-right.
	};

	float tex_coords[8]
		= { (float)x, (float)y, (float)x, (float)img_y, (float)img_x, (float)img_y, (float)img_x, (float)y };

	shader_image.Activate();
	GLuint prog_id = ax::GC::shader_image.GetProgramId();
	GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, img->GetTexture());

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	// Texture coordinates.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDisable(GL_TEXTURE_2D);
}

void ax::GC::DrawPartOfImageResize(ax::Image* img, const ax::Point& posInImage, const ax::Size& sizeInImage,
	const ax::Rect& rect, float alpha)
{
	ax::Point pos = rect.position;
	ax::Size img_size = img->GetSize();

	double img_x = (posInImage.x + sizeInImage.w) / double(img_size.w),
		   img_y = 1.0 - (posInImage.y + sizeInImage.h) / double(img_size.h);

	double x = posInImage.x / double(img_size.w);
	double y = 1.0 - posInImage.y / double(img_size.h);

	glColor4f(1.0, 1.0, 1.0, alpha);

	float vertices[8] = {
		(float)pos.x, (float)pos.y, // Top-left.
		(float)pos.x, (float)pos.y + rect.size.h, // Bottom-left.
		(float)pos.x + rect.size.w, (float)pos.y + rect.size.h, // Bottom-right.
		(float)pos.x + rect.size.w, (float)pos.y // Top-right.
	};

	float tex_coords[8]
		= { (float)x, (float)y, (float)x, (float)img_y, (float)img_x, (float)img_y, (float)img_x, (float)y };

	shader_image.Activate();

	GLuint prog_id = ax::GC::shader_image.GetProgramId();
	GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, img->GetTexture());

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	// Texture coordinates.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDisable(GL_TEXTURE_2D);
}

void ax::GC::DrawString(ax::Font& font, const std::string& text, const ax::Point& pos)
{
	if (font) {
		int x = pos.x;

		shader_font.Activate();

		glUniformMatrix4fv(
			shader_font.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

		ax::Color& c0(ax::GC::current_color);
		ax::Color colors[4] = { c0, c0, c0, c0 };

		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		// Colors coordinates.
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
		glEnableVertexAttribArray(2);

		for (int i = 0; i < text.size(); i++) {
			font.SetChar(text[i]);
			ax::Point delta = font.GetDelta();

			DrawTexture(font.GetTexture(),
				ax::Rect(ax::Point(x + delta.x, pos.y - delta.y + font.GetFontSize()), font.GetSize()));

			x += font.GetNextPosition();
		}
		glDisableVertexAttribArray(2);
	}
}

ax::Point ax::GC::DrawChar(ax::Font& font, const char& key, const ax::Point& pos)
{
	if (font) {
		int x = pos.x;

		font.SetChar(key);
		ax::Point delta = font.GetDelta();

		shader_font.Activate();

		glUniformMatrix4fv(
			shader_font.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

		ax::Color& c0(ax::GC::current_color);
		ax::Color colors[4] = { c0, c0, c0, c0 };

		// Pre-calculated alpha.
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		// Colors coordinates.
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
		glEnableVertexAttribArray(2);

		DrawTexture(font.GetTexture(),
			ax::Rect(ax::Point(x + delta.x, pos.y - delta.y + font.GetFontSize()), font.GetSize()));

		glDisableVertexAttribArray(2);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		x += font.GetNextPosition();

		return ax::Point(x, pos.y);
	}

	return ax::Point(0, 0);
}

void ax::GC::DrawStringAlignedLeft(ax::Font& font, const std::string& text, const ax::Rect& rect)
{
	if (font) {
		int height = 0;
		for (int i = 0; i < text.size(); i++) {
			font.SetChar(text[i]);
			if (font.GetSize().h > height)
				height = font.GetSize().h;
		}

		ax::Point pos(5, rect.position.y + ceil((rect.size.h - height) * 0.5));

		int x = pos.x;

		shader_font.Activate();

		glUniformMatrix4fv(
			shader_font.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

		ax::Color& c0(ax::GC::current_color);
		ax::Color colors[4] = { c0, c0, c0, c0 };

		// Pre-calculated alpha;
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < text.size(); i++) {
			font.SetChar(text[i]);
			ax::Point delta = font.GetDelta();

			// Colors coordinates.
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
			glEnableVertexAttribArray(2);

			DrawTexture(font.GetTexture(),
				ax::Rect(ax::Point(x + delta.x, pos.y - delta.y + height), font.GetSize()));

			x += font.GetNextPosition();
		}

		glDisableVertexAttribArray(2);

		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void ax::GC::DrawStringAlignedCenter(ax::Font& font, const std::string& text, const ax::Rect& rect)
{
	if (font) {
		int length = 0;
		int height = 0;
		for (int i = 0; i < text.size(); i++) {
			font.SetChar(text[i]);
			length += font.GetNextPosition();

			if (font.GetSize().h > height)
				height = font.GetSize().h;
		}

		ax::Point pos(rect.position.x + (rect.size.w - length) * 0.5,
			rect.position.y + ceil((rect.size.h - height) * 0.5));

		int x = pos.x;

		shader_font.Activate();

		glUniformMatrix4fv(
			shader_font.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

		ax::Color& c0(ax::GC::current_color);
		ax::Color colors[4] = { c0, c0, c0, c0 };

		// Pre-calculated alpha;
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < text.size(); i++) {
			font.SetChar(text[i]);
			ax::Point delta = font.GetDelta();

			// Colors coordinates.
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
			glEnableVertexAttribArray(2);

			DrawTexture(font.GetTexture(),
				ax::Rect(ax::Point(x + delta.x, pos.y - delta.y + height - 1), font.GetSize()));

			x += font.GetNextPosition();
		}

		glDisableVertexAttribArray(2);

		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void ax::GC::DrawStringAlignedHorizontalCenter(ax::Font& font, const std::string& text, const ax::Rect& rect)
{
	if (font) {
		int length = 0;
		int height = 0;
		for (int i = 0; i < text.size(); i++) {
			font.SetChar(text[i]);
			length += font.GetNextPosition();

			if (font.GetSize().h > height)
				height = font.GetSize().h;
		}

		ax::Point pos(rect.position.x + (rect.size.w - length) * 0.5,
			rect.position.y + ceil((rect.size.h - height) * 0.5));

		int x = pos.x;

		shader_font.Activate();

		glUniformMatrix4fv(
			shader_font.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

		ax::Color& c0(ax::GC::current_color);
		ax::Color colors[4] = { c0, c0, c0, c0 };

		// Pre-calculated alpha;
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < text.size(); i++) {
			font.SetChar(text[i]);
			ax::Point delta = font.GetDelta();

			// Colors coordinates.
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
			glEnableVertexAttribArray(2);

			DrawTexture(font.GetTexture(), ax::Rect(ax::Point(x + delta.x, rect.position.y), font.GetSize()));

			x += font.GetNextPosition();
		}

		glDisableVertexAttribArray(2);

		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void ax::GC::DrawStringAlignedRight(ax::Font& font, const std::string& text, const ax::Rect& rect)
{
	if (font) {
		int length = 0;
		int height = 0;
		for (int i = 0; i < text.size(); i++) {
			font.SetChar(text[i]);
			length += font.GetNextPosition();

			if (font.GetSize().h > height)
				height = font.GetSize().h;
		}

		ax::Point pos(
			rect.position.x + rect.size.w - length - 5, rect.position.y + ceil((rect.size.h - height) * 0.5));

		int x = pos.x;

		shader_font.Activate();

		glUniformMatrix4fv(
			shader_font.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

		ax::Color& c0(ax::GC::current_color);
		ax::Color colors[4] = { c0, c0, c0, c0 };

		// Pre-calculated alpha;
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < text.size(); i++) {
			font.SetChar(text[i]);
			ax::Point delta = font.GetDelta();

			// Colors coordinates.
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, colors);
			glEnableVertexAttribArray(2);

			DrawTexture(font.GetTexture(),
				ax::Rect(ax::Point(x + delta.x, pos.y - delta.y + height), font.GetSize()));

			x += font.GetNextPosition();
		}

		glDisableVertexAttribArray(2);

		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void ax::GC::DrawRectangleColorFade(const ax::Rect& rectangle, const ax::Color& c1, const float& alpha1,
	const ax::Color& c2, const float& alpha2)
{
	ax::Color cc1(c1), cc2(c2);
	cc1.SetAlpha(alpha1);
	cc2.SetAlpha(alpha2);

	ax::FRect rect = RectToFRect(rectangle);
	ax::Color colors[4] = { cc1, cc1, cc2, cc2 };

	// Order : bl, tl, tr, br.
	ax::math::RectPoints<ax::FPoint> points = rect.GetPoints<ax::FPoint>();

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &points);
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void ax::GC::DrawRectangleColorFade(const ax::Rect& rectangle, const ax::Color& c1, const ax::Color& c2)
{
	ax::FRect rect = RectToFRect(rectangle);
	ax::Color colors[4] = { c1, c1, c2, c2 };

	// Order : bl, tl, tr, br.
	ax::math::RectPoints<ax::FPoint> points(rect.GetPoints<ax::FPoint>());

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &points);
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void ax::GC::DrawRectangleVerticalColorFade(
	const ax::Rect& rectangle, const ax::Color& c1, const ax::Color& c2)
{
	ax::FRect rect = RectToFRect(rectangle);
	ax::Color colors[4] = { c1, c2, c2, c1 };

	// Order : bl, tl, tr, br.
	ax::math::RectPoints<ax::FPoint> points(rect.GetPoints<ax::FPoint>());

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)&points);
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void ax::GC::DrawRectangleColorFade(const ax::Rect& rectangle, const std::vector<ax::Color>& colors)
{
	ax::FRect rect = RectToFRect(rectangle);

	// Order : bl, tl, tr, br.
	ax::math::RectPoints<ax::FPoint> points(rect.GetPoints<ax::FPoint>());

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)&points);
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors.data());
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void ax::GC::DrawLines(const std::vector<ax::Point>& pts, float width)
{
	// Convert to float points.
	std::vector<ax::FPoint> points;
	points.reserve(pts.size());

	std::transform(pts.begin(), pts.end(), std::back_inserter(points),
		[](const ax::Point& p) { return p.Cast<float>(); });

	std::vector<ax::Color> colors(points.size(), current_color);

	glLineWidth(width);

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)points.data());
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors.data());
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_LINES, 0, (GLsizei)points.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	glLineWidth(1.0f);
}

void ax::GC::DrawLines(const std::vector<ax::FPoint>& points, float width)
{
	/// @todo Need to remove this memory allocation.
	std::vector<ax::Color> colors(points.size(), current_color);

	glLineWidth(width);

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)points.data());
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors.data());
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_LINES, 0, (GLsizei)points.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	glLineWidth(1.0f);
}

void ax::GC::DrawSmouthLine(const ax::Point& pt1, const ax::Point& pt2, float width)
{
#ifdef ANDROID
#else
	//    glEnable(GL_LINE_SMOOTH);
	//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//
	//    glBegin(GL_LINES);
	//    glVertex2f(pt1.x, pt1.y);
	//    glVertex2f(pt2.x, pt2.y);
	//    glEnd();
	//
	//    glDisable(GL_LINE_SMOOTH);
	//    float width = 3;

	double dx = pt2.x - pt1.x;
	double dy = pt2.y - pt1.y;
	double m = dx == 0.0 ? 999999.9 : dy / dx;

	m = std::abs(m);

	if (m > 1.0) {
		m = std::abs(dy / dx);
	}

	double wx = 0.0;
	double wy = 0.0; // 0.5 - m;

	if (m <= 0.5) {
		wx = ax::util::Clamp<double>(0.5 + m, 0.0, 1.0);
	}
	else {
		wy = ax::util::Clamp<double>(0.5 + m, 0.0, 1.0);
	}

	//    ax::Print("M : ", m);
	//    std::cout << "M : " << m <<

	glEnable(GL_POLYGON_SMOOTH);
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1, 1, 1);
	glVertex3f(pt1.x, pt1.y, 0);
	glVertex3f(pt2.x, pt2.y, 0);

	glColor3f(1, 0, 0);
	glVertex3f(pt1.x + wx, pt1.y + wy, 0);
	glVertex3f(pt2.x + wx, pt2.y + wy, 0);

	glColor3f(1, 1, 1);
	glVertex3f(pt1.x + 2.0 * wx, pt1.y + wy * 2.0, 0);
	glVertex3f(pt2.x + 2.0 * wx, pt2.y + wy * 2.0, 0);
	glEnd();

	glDisable(GL_POLYGON_SMOOTH);
#endif
}

void ax::GC::DrawLine(const ax::Point& pt1, const ax::Point& pt2, float width)
{
	ax::FPoint points[2] = { pt1.Cast<float>(), pt2.Cast<float>() };
	ax::Color colors[2] = { current_color, current_color };

	glLineWidth(width);

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)&points);
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)&colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_LINES, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	glLineWidth(1.0f);
}

void ax::GC::DrawLines(
	const std::vector<ax::Point>& ipoints, const std::vector<ax::Color>& colors, float width)
{
	// Convert to float points.
	std::vector<ax::FPoint> points;
	points.reserve(ipoints.size());
	std::transform(ipoints.begin(), ipoints.end(), std::back_inserter(points),
		[](const ax::Point& p) { return p.Cast<float>(); });

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (float*)points.data());
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (float*)colors.data());
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_LINES, 0, (GLsizei)points.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void ax::GC::DrawLineStripple(const ax::Point& pt1, const ax::Point& pt2)
{
	ax::FPoint points[2] = { ax::FPoint(pt1.x, pt1.y), ax::FPoint(pt2.x, pt2.y) };

	ax::Color& c0(ax::GC::current_color);
	ax::Color colors[2] = { c0, c0 };

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	glLineStipple(1, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)&points);
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)&colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	// glDisable(GL_LINE_STIPPLE);
}

void ax::GC::DrawLineColorfade(
	const ax::Point& pt1, const ax::Point& pt2, const ax::Color& c1, const ax::Color& c2, float width)
{
	ax::FPoint points[2] = { pt1.Cast<float>(), pt2.Cast<float>() };
	ax::Color colors[2] = { c1, c2 };

	glLineWidth(width);

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)&points);
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)&colors);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_LINES, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	glLineWidth(1.0f);
}

void ax::GC::DrawPoint(const ax::Point& pt, const int& size)
{
	ax::FPoint point(pt.Cast<float>());

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	glEnable(GL_POINT_SMOOTH);
	glPointSize(size);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)&point);
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)&current_color);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	glDisable(GL_POINT_SMOOTH);
}

void ax::GC::DrawLineCubic(const ax::Point& pt1, const ax::Point& pt2)
{
#ifdef ANDROID
#else
	// H1(t) = 2t^3 - 3t^2 + 1
	// H2(t) = -2t^3 + 3t^2
	// H3(t) = t^3 - 2t^2 + t
	// H4(t) = t^3 - t^2
	// V1 = Tengente at point 1.
	// V2 = Tengente at point 2.
	// P(t) = [H1(t) H2(t) H3(t) H4(t)] * [P1 P2 V1 V2];
	// P(t) = H1(t) * P1.x + H2(t) * P2.x + H3(t) *

	//    double t = 0.0;

	double v1x = 100.0, v1y = 200;
	double v2x = 100.0, v2y = -200;

	double pp_x = pt1.x, pp_y = pt1.y;

	glBegin(GL_LINES);
	for (int i = 1; i < 101; i++) {
		double t = i / double(101.0);

		double h1 = 2.0 * pow(t, 3.0) - 3.0 * pow(t, 2.0) + 1.0;
		double h2 = -2.0 * pow(t, 3.0) + 3.0 * pow(t, 2.0);
		double h3 = pow(t, 3.0) - 2.0 * pow(t, 2.0) + t;
		double h4 = pow(t, 3.0) - pow(t, 2.0);

		double p_x = h1 * pt1.x + h2 * pt2.x + h3 * v1x + h4 * v2x;
		double p_y = h1 * pt1.y + h2 * pt2.y + h3 * v1y + h4 * v2y;

		glVertex2f(pp_x, pp_y);
		glVertex2f(p_x, p_y);

		pp_x = p_x;
		pp_y = p_y;
	}
	glEnd();
#endif

	//    glVertex2f(pt1.x, pt1.y);
	//    glVertex2f(pt2.x, pt2.y);
}

void ax::GC::SetLineWidth(const float& width)
{
	//    glEnable(GL_LINE_SMOOTH);
	//    glEnable(GL_POLYGON_SMOOTH);
	//    glEnable(GL_BLEND);
	//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glLineWidth(width);
}

void ax::GC::SetSmoothLine(const int& width)
{
#ifndef ANDROID // NOT ANDROID.
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
#endif
	glLineWidth(width);
}

void ax::GC::SetDefaultLine()
{
#ifndef ANDROID // NOT ANDROID.
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
#endif
	glLineWidth(1.0);
}

void ax::GC::DrawCircle(const ax::Point& pos, const float& radius, const int& nSegments)
{
	ax::Point real_pos = pos;
	std::vector<ax::FPoint> points(nSegments);

	for (int i = 0; i < nSegments; i++) {
		// Get the current angle.
		float theta = 2.0f * M_PI * float(i) / float(nSegments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		points[i] = ax::FPoint(x + real_pos.x, y + real_pos.y);
	}

	std::vector<ax::Color> colors(points.size(), current_color);

	glLineWidth(1);

	shader_normal.Activate();

	glUniformMatrix4fv(
		shader_normal.GetUniformLocation("mvp_matrix"), 1, GL_FALSE, (float*)&ax::GC::mvp_matrix[0][0]);

	// Vertex coordinates.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)points.data());
	glEnableVertexAttribArray(0);

	// Color array.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)colors.data());
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_LINE_LOOP, 0, (int)points.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	//	glLineWidth(1.0f);
}

// void GC::DrawBuffer(axDrawingBuffer* buffer)
//{
//    unsigned char* surf_data = buffer->GetData();
//    GLuint texture_id = buffer->GetTexture();
//    ax::Size size(buffer->GetSize());
//
//    if (!surf_data)
//    {
//        printf ("draw_func() - No valid pointer to surface-data passed\n");
//        return;
//    }
//
////    glMatrixMode(GL_MODELVIEW);
////    glLoadIdentity ();
////    glClear(GL_COLOR_BUFFER_BIT);
//
//
//    //glPushMatrix();
//    axPrint("Cairo draw.");
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_TEXTURE_RECTANGLE_ARB);
//    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_id);
//    glTexImage2D (GL_TEXTURE_RECTANGLE_ARB,
//                  0,
//                  GL_RGBA,
//                  size.w,
//                  size.h,
//                  0,
//                  GL_BGRA,
//                  GL_UNSIGNED_BYTE,
//                  surf_data);
//
//    glColor3f (1.0f, 0.0f, 1.0f);
//    glBegin (GL_QUADS);
//
//    glTexCoord2f (0.0f, 0.0f);
//    glVertex2f (0.0f, 0.0f);
//
//    glTexCoord2f ((GLfloat) size.w, 0.0f);
//    glVertex2f (1.0f, 0.0f);
//
//    glTexCoord2f ((GLfloat) size.w, (GLfloat) size.h);
//    glVertex2f (1.0f, 1.0f);
//
//    glTexCoord2f (0.0f, (GLfloat) size.h);
//    glVertex2f (0.0f, 1.0f);
//
//    glEnd ();
//
//    glDisable(GL_TEXTURE_RECTANGLE_ARB);
//    glDisable(GL_TEXTURE_2D);
//
//
////    glPopMatrix();
//
//}

//
void ax::GC::DrawBigImageResize(
	ax::BigImage* img, const ax::Point& position, const ax::Size& size, float alpha)
{
#ifdef ANDROID
#else
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	ax::BigImage::ColorType color_type = img->GetColorType();
	// axBigImage::PixelDepth depth = img->GetPixelDepth();
	ax::Size real_img_size(img->GetImageSize());
	void* data = img->GetImageData();

	if (color_type == ax::BigImage::RGB) {
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGB, real_img_size.w, real_img_size.h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else {
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA, real_img_size.w, real_img_size.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLenum err = glGetError();

	if (err != GL_NO_ERROR) {
		ax::console::Error("Can't draw axBigImage in GC : ", err);
	}

	ax::Point pos = position;

	glColor4f(1.0, 1.0, 1.0, alpha);

	glEnable(GL_TEXTURE_2D);
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// glBindTexture(GL_TEXTURE_2D, texture);
	//	glDepthMask(GL_TRUE);
	ax::Size img_size = size;

	// OpenGL stores texture upside down so glTexCoord2d must be flipped.
	glBegin(GL_QUADS);
	// Buttom left.
	glTexCoord2d(0.0, 1.0);
	glVertex2d(pos.x, pos.y);

	// Top left.
	glTexCoord2d(0.0, 0.0);
	glVertex2d(pos.x, pos.y + img_size.h);

	// Top right.
	glTexCoord2d(1.0, 0.0);
	glVertex2d(pos.x + img_size.w, pos.y + img_size.h);

	// Buttom right.
	glTexCoord2d(1.0, 1.0);
	glVertex2d(pos.x + img_size.w, pos.y);
	glEnd();

	//	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &texture);
#endif
}

void ax::GC::DrawPolygone(const std::vector<ax::Point>& points)
{
#ifdef ANDROID
#else
	glBegin(GL_POLYGON);

	for (auto& n : points) {
		glVertex2d(n.x, n.y);
	}

	glEnd();
#endif
}

void ax::GC::DrawArrow(const ax::Point& p1, const ax::Point& p2, const double& arrow_length,
	const double& base_length, const double& width)
{
#ifdef ANDROID
#else
	glLineWidth(width);
	//    double arrow_length = 12;
	//    double base_length = 8;

	ax::Point arrow_vec = p2 - p1;
	ax::Point normal_vec = ax::Point(-arrow_vec.y, arrow_vec.x);
	double normal_norm = sqrt(normal_vec.x * normal_vec.x + normal_vec.y * normal_vec.y);

	normal_vec.x = (normal_vec.x / normal_norm) * base_length;
	normal_vec.y = (normal_vec.y / normal_norm) * base_length;

	ax::Point arrow_base = arrow_vec;
	double norm = sqrt(arrow_base.x * arrow_base.x + arrow_base.y * arrow_base.y);
	arrow_base.x = (arrow_base.x / norm) * arrow_length;
	arrow_base.y = (arrow_base.y / norm) * arrow_length;
	arrow_base = p2 - arrow_base;

	ax::Point pt_vec1 = arrow_base + normal_vec;
	ax::Point pt_vec2 = arrow_base - normal_vec;

	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(pt_vec1.x, pt_vec1.y);
	glVertex2f(pt_vec2.x, pt_vec2.y);
	glVertex2f(p2.x, p2.y);
	glEnd();

//    glBegin(GL_LINES);
//    glVertex2f(arrow_base.x, arrow_base.y);
//    glVertex2f(pt_vec1.x, pt_vec1.y);
//
//    glVertex2f(arrow_base.x, arrow_base.y);
//    glVertex2f(pt_vec2.x, pt_vec2.y);
//    glEnd();
#endif
}

void ax::GC::DrawTriangleColorFade(const ax::Point& p1, const ax::Point& p2, const ax::Point& p3,
	const ax::Color& c1, const ax::Color& c2, const ax::Color& c3)
{
#ifdef ANDROID
#else
	glBegin(GL_POLYGON);

	SetColor(c1);
	glVertex2d(p1.x, p1.y);
	SetColor(c2);
	glVertex2d(p2.x, p2.y);
	SetColor(c3);
	glVertex2d(p3.x, p3.y);

	glEnd();
#endif
}
