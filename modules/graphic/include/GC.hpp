/*
 * Copyright (c) 2015 Alexandre Arsenault.
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

#pragma once

/// @defgroup Graphic
/// @{

#include "Font.hpp"
#include "Shader.hpp"
#include "Image.hpp"
#include "Util.hpp"
#include <glm/mat4x4.hpp>

namespace ax {
class GC {
public:
	GC();

	void SetColor(const ax::Color& color);

	void SetColor(const ax::Color& color, const float& alpha);

	void SetColor(const float& r, const float& g, const float& b);

	void SetColor(const float& r, const float& g, const float& b, const float& a);

	void DrawRectangle(const ax::Rect& rect);

	void DrawRectangleContour(const ax::Rect& rect, float linewidth = 1.0);

	void DrawQuarterCircle(
		const ax::FPoint& pos, const int& radius, const double& angle, const int& nSegments);

	void DrawQuarterCircle(const ax::FPoint& pos, const int& radius, const double& angle,
		const int& nSegments, const ax::Color& middle, const ax::Color& around);

	void DrawRoundedRectangle(const ax::Rect& rect, const int& radius);

	void DrawRoundedRectangleContour(const ax::Rect& rect, const int& radius);

	void DrawRoundedRectangleContourSmooth(const ax::Rect& rect, const int& radius);

	void DrawImage(ax::Image* img, const ax::Point& pos, float alpha = 1.0);

	void DrawImageColor(ax::Image* img, const ax::Point& pos, const ax::Color& color);

	void DrawImageResizeColor(
		ax::Image* img, const ax::Point& pos, const ax::Size& size, const ax::Color& color);

	void DrawImageResize(ax::Image* img, const ax::Point& position, const ax::Size& size, float alpha = 1.0,
		bool vertical_inversion = false);

	void DrawPartOfImage(ax::Image* img, const ax::Point& posInImage, const ax::Size& sizeInImage,
		const ax::Point& pos, float alpha = 1.0);

	void DrawPartOfImageResize(ax::Image* img, const ax::Point& posInImage, const ax::Size& sizeInImage,
		const ax::Rect& rect, float alpha = 1.0);

	ax::Point DrawChar(ax::Font& font, const char& key, const ax::Point& pos);

	void DrawString(ax::Font& font, const std::string& text, const ax::Point& pos);

	void DrawStringAlignedLeft(ax::Font& font, const std::string& text, const ax::Rect& rect);

	void DrawStringAlignedCenter(ax::Font& font, const std::string& text, const ax::Rect& rect);

	void DrawStringAlignedRight(ax::Font& font, const std::string& text, const ax::Rect& rect);

	void DrawStringAlignedHorizontalCenter(ax::Font& font, const std::string& text, const ax::Rect& rect);

	void DrawRectangleColorFade(const ax::Rect& rect, const ax::Color& c1, const float& alpha1,
		const ax::Color& c2, const float& alpha2);

	void DrawRectangleColorFade(const ax::Rect& rect, const ax::Color& c1, const ax::Color& c2);

	void DrawRectangleVerticalColorFade(const ax::Rect& rect, const ax::Color& c1, const ax::Color& c2);

	// Order : bl, tl, tr, br.
	void DrawRectangleColorFade(const ax::Rect& rect, const std::vector<ax::Color>& colors);

	void DrawPolygone(const std::vector<ax::Point>& points);

	void DrawArrow(const ax::Point& p1, const ax::Point& p2, const double& arrow_length = 12,
		const double& base_length = 8, const double& width = 1);

	void DrawTriangleColorFade(const ax::Point& p1, const ax::Point& p2, const ax::Point& p3,
		const ax::Color& c1, const ax::Color& c2, const ax::Color& c3);

	void DrawLine(const ax::Point& pt1, const ax::Point& pt2, float width = 1.0);

	void DrawLines(
		const std::vector<ax::Point>& points, const std::vector<ax::Color>& colors, float width = 1.0);

	void DrawLineStripple(const ax::Point& pt1, const ax::Point& pt2);

	void DrawLineColorfade(const ax::Point& pt1, const ax::Point& pt2, const ax::Color& c1,
		const ax::Color& c2, float width = 1.0);

	void DrawSmouthLine(const ax::Point& pt1, const ax::Point& pt2, float width = 2.0);

	void DrawLines(const std::vector<ax::Point>& pts, float width = 1.0);

	void DrawLines(const std::vector<ax::FPoint>& pts, float width = 1.0);

	void DrawPoint(const ax::Point& pt, const int& size);

	/// @todo This function is not finish. (Add some param)
	void DrawLineCubic(const ax::Point& pt1, const ax::Point& pt2);

	void SetLineWidth(const float& width);

	void SetSmoothLine(const int& width);
	void SetDefaultLine();

	void DrawCircle(const ax::Point& pos, const float& radius, const int& nSegments);

	void DrawTexture(uint32_t texture, const ax::Rect& rect, ax::Color color = ax::Color(0.0f, 0.0f, 0.0f));

	void DrawBigImageResize(
		ax::BigImage* img, const ax::Point& position, const ax::Size& size, float alpha = 1.0);

	//    void DrawWindowBuffer();

	// Just blocking x axis for now.
	//    void BlockDrawing(const ax::Rect& rect);
	//    void UnBlockDrawing();

	// void DrawBuffer(axDrawingBuffer* buffer);

	static ax::GL::Shader shader_fb;
	static ax::GL::Shader shader_normal;
	static ax::GL::Shader shader_font;
	static ax::GL::Shader shader_image;
	static ax::GL::Shader shader_image_alpha;
	static ax::GL::Shader shader_image_color;
	static glm::mat4 mvp_matrix;
	static ax::Color current_color;

private:
	ax::FRect RectToFRect(const ax::Rect& rect);
};
}

/// @}
