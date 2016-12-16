/*
 * Copyright (c) 2016 Alexandre Arsenault.
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
#ifndef __AX_IMAGE__
#define __AX_IMAGE__

/// @defgroup graphic
/// @{

//#define PNG_SKIP_SETJMP_CHECK

/// @cond EXCLUDE_FROM_DOC
#define PNG_DEBUG 3
/// @endcond

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>

#include "Util.hpp"

namespace ax {
class Image;

struct ImageStruct {
	ImageStruct(uint32_t tex, ax::Size size)
		: _texture(tex)
		, _size(size)
		, ref_count(1)
	{
	}

	uint32_t _texture;
	ax::Size _size;
	unsigned int ref_count;
};

class ImageGlobalMapLoader {
public:
	ImageGlobalMapLoader();

	bool LoadImage(const std::string& path, uint32_t& _texture, ax::Size& _size);

	void RemoveImage(const std::string& path);

private:
	std::map<std::string, ImageStruct> _imageMap;

	bool InitImage(const std::string& path, uint32_t& _texture, ax::Size& _size);
};

class Image {
public:
	enum ColorType { RGB, RGBA };
	
	typedef std::shared_ptr<ax::Image> Ptr;
	
	Image(const std::string& path);

	Image(void* data, const ax::Size& size, ColorType type = RGBA);

	~Image();

	uint32_t GetTexture();
	bool IsImageReady();
	ax::Size GetSize();
	int GetHeight();
	int GetWidth();

	bool SaveImage(const std::string& path);

	std::string GetImagePath() const
	{
		return _path;
	}

private:
	uint32_t _texture;
	ax::Size _size;
	std::string _path;

	static ImageGlobalMapLoader _globalMap;

	friend ImageGlobalMapLoader;
};

class BigImage {
public:
	BigImage(const std::string& path);

	~BigImage()
	{
		delete[](unsigned char*)_imgData;
	}

	bool InitImage(const std::string& path);

	enum ColorType { RGB, RGBA };

	enum PixelDepth { UNSIGNED_BYTE };

	void* GetImageData()
	{
		return _imgData;
	}

	ColorType GetColorType() const
	{
		return _colorType;
	}

	PixelDepth GetPixelDepth() const
	{
		return _pixelDepth;
	}

	ax::Size GetImageSize() const
	{
		return _size;
	}

	bool IsImageReady() const
	{
		return _imgData != nullptr;
	}

private:
	std::string _path;
	ax::Size _size;
	void* _imgData;
	ColorType _colorType;
	PixelDepth _pixelDepth;
};
}

/// @}
#endif //__AX_IMAGE__
