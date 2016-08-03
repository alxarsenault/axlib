/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of OpenAX.
 *
 * OpenAX is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial OpenAX License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenAX. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses OpenAX, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#ifndef __AX_FONT__
#define __AX_FONT__

/*
 * @file    Font.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   Font.
 * @date    13/01/2015
 */

/// @defgroup Graphic
/// @{

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Util.hpp"
#include "Math.hpp"
#include <map>

namespace ax {
const unsigned char* GetDefaultFontData(const int& index);
const long GetDefaultFontDataSize(const int& index);

// class FontTexture
//{
// public:
//	FontTexture(const std::string& font);
//};

class Font {
public:
	Font();

	// Create font from font path.
	Font(const std::string& font);

	// Create default font. Only 0 and 1 supported for now.
	Font(const int& data_index);

	// No copy constructor.
	Font(const Font&) = delete;

	// No copy possible.
	Font& operator=(const Font&) = delete;

	~Font();

	uint32_t GetTexture();

	bool operator==(const bool& exist);

	bool operator!=(const bool& exist);

	bool IsFontReady() const;

	// Equivalent to IsFontReady.
	operator bool() const;

	// Char won't work if SetFontSize is not call first.
	void SetFontSize(const int& size);

	void SetChar(const unsigned long& letter);

	ax::Size GetSize() const;

	ax::Point GetDelta() const;

	int GetNextPosition() const;

	void SetFontType(const std::string& font_type);

	int GetFontSize() const;

private:
	FT_Library _freeType;
	FT_Face _face;
	uint32_t _texture;
	ax::Size _size;
	ax::Point _delta;
	int _next, _font_size;
	bool _isReady;

	struct FontCharData {
		uint32_t texture;
		ax::Size size;
		ax::Point delta;
		int next;
	};

	std::map<unsigned long, FontCharData> _font_map;

	bool LoadFont(const std::string& path, FT_Face& face);
};
}

/// @}
#endif // __AX_FONT__
