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
#include "Font.hpp"

#ifdef ANDROID
#include <EGL/egl.h> // requires ndk r5 or newer
#include <GLES/gl.h>

#elif WAYLAND
#include "GL/gl.h"

#elif axCoreX11
#include "GL/gl.h"

#elif _MSC_VER
#include "GL/glew.h"
#include <windows.h>
//#include <gl\gl.h>
#include <gl\glu.h>

#else //__APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#endif // __APPLE__

namespace ax {
// FontTexture::FontTexture(const std::string& font)
//{
//	char * font_cache = " !\"#$%&'()*+,-./0123456789:;<=>?"
//		"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
//		"`abcdefghijklmnopqrstuvwxyz{|}~";
//}

Font::Font()
	: _isReady(false)
{
}

Font::Font(const int& data_index)
	: _isReady(false)
{
	if (FT_Init_FreeType(&_freeType)) {
		ax::console::Error("Could not init freetype library.");
		FT_Done_FreeType(_freeType);
	}
	else {

		if (data_index > 1) {
			ax::console::Error("Only two default font buffer.");

			FT_Done_FreeType(_freeType);
		}
		else {
			FT_Error err = FT_New_Memory_Face(
				_freeType, GetDefaultFontData(data_index), GetDefaultFontDataSize(data_index), 0, &_face);

			if (err) {
				ax::console::Error("Could not open font index", data_index);
				FT_Done_FreeType(_freeType);
			}
			else {
				_isReady = true;
				SetFontSize(12);
				//				glGenTextures(1, &_texture);
			}
		}
	}
}

Font::Font(const std::string& path)
	: _isReady(false)
{
	if (FT_Init_FreeType(&_freeType)) {
		ax::console::Error("Could not init freetype library.");
		FT_Done_FreeType(_freeType);
	}
	else {
		bool err = LoadFont(path, _face);

		if (err) {
			ax::console::Error("Could not open font", path);
			FT_Done_FreeType(_freeType);
		}
		else {
			_isReady = true;
			SetFontSize(12);
		}
	}
}

Font::~Font()
{
	if (_isReady) {
		FT_Done_Face(_face);
		FT_Done_FreeType(_freeType);

		for (auto& n : _font_map) {
			glDeleteTextures(1, &n.second.texture);
		}

		_font_map.clear();
	}
}

bool Font::operator==(const bool& exist)
{
	return _isReady == exist;
}

bool Font::operator!=(const bool& exist)
{
	return _isReady != exist;
}

bool Font::IsFontReady() const
{
	return _isReady;
}

Font::operator bool() const
{
	return _isReady;
}

int Font::GetFontSize() const
{
	return _font_size;
}

ax::Size Font::GetSize() const
{
	return _size;
}

ax::Point Font::GetDelta() const
{
	return _delta;
}

int Font::GetNextPosition() const
{
	return _next;
}

bool Font::LoadFont(const std::string& path, FT_Face& face)
{
	// Zero mean succes.
	if (FT_New_Face(_freeType, path.c_str(), 0, &_face) != 0) {
		return true;
	}

	return false;
}

void Font::SetFontSize(const int& size)
{
	if (_isReady) {
		_font_size = size;
		FT_Set_Pixel_Sizes(_face, 0, size);
	}
}

void Font::SetChar(const unsigned long& letter)
{
	if (_isReady) {
		std::map<unsigned long, FontCharData>::iterator it = _font_map.find(letter);

		// Char already exist.
		if (it != _font_map.end()) {
			FontCharData& f_data = it->second;
			_texture = f_data.texture;
			_size = f_data.size;
			_delta = f_data.delta;
			_next = f_data.next;
		}
		// Char not in map yet.
		else {
			// Zero mean succes.
			if (FT_Load_Char(_face, letter, FT_LOAD_RENDER) != 0) {
				ax::console::Error("Could not load character", letter);
				return;
			}

			FontCharData f_data;

			FT_GlyphSlot g = _face->glyph;
			f_data.size = ax::Size(g->bitmap.width, g->bitmap.rows);
			f_data.delta = ax::Point(_face->glyph->bitmap_left, _face->glyph->bitmap_top);

			f_data.next = g->advance.x / 64.0;

			glGenTextures(1, &f_data.texture);

			glBindTexture(GL_TEXTURE_2D, f_data.texture);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA,
				GL_UNSIGNED_BYTE, g->bitmap.buffer);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			_texture = f_data.texture;
			_size = f_data.size;
			_delta = f_data.delta;
			_next = f_data.next;

			_font_map.insert(std::pair<unsigned long, FontCharData>(letter, f_data));
		}
	}
	//        if(_isReady)
	//        {
	//            // Zero mean succes.
	//            if(FT_Load_Char(_face, letter, FT_LOAD_RENDER) != 0)
	//            {
	//                ax::Error("Could not load character ", letter);
	//            }
	//            else
	//            {
	//                FT_GlyphSlot g = _face->glyph;
	//                _size = ax::Size(g->bitmap.width, g->bitmap.rows);
	//
	//                _delta = ax::Point(_face->glyph->bitmap_left,
	//                                   _face->glyph->bitmap_top);
	//
	//                _next = g->advance.x / 64.0;
	//
	//                glBindTexture(GL_TEXTURE_2D, _texture);
	//                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//
	//                glTexImage2D(GL_TEXTURE_2D,
	//                             0,
	//                             GL_ALPHA,
	//                             g->bitmap.width,
	//                             g->bitmap.rows,
	//                             0,
	//                             GL_ALPHA,
	//                             GL_UNSIGNED_BYTE,
	//                             g->bitmap.buffer);
	//
	//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
	//                GL_CLAMP_TO_EDGE);
	//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
	//                GL_CLAMP_TO_EDGE);
	//
	//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
	//                GL_LINEAR);
	//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	//                GL_LINEAR);
	//            }
	//        }
}

void Font::SetFontType(const std::string& font_type)
{
	ax::console::Error("SetFontType not implemented yet.");
}

GLuint Font::GetTexture()
{
	return _texture;
}
}
