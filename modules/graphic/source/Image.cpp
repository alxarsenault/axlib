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
#include "Image.hpp"
#include "png.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Render.hpp"
#define LOG_INFO(x)

namespace ax {
ImageGlobalMapLoader Image::_globalMap;

ImageGlobalMapLoader::ImageGlobalMapLoader()
{
}

bool ImageGlobalMapLoader::LoadImage(const std::string& path, GLuint& _texture, ax::Size& _size)
{
	//#ifdef _AX_VST_APP_
	//	/// @todo Find a way to have a map with multiple opengl contexts.
	//	if (InitImage(path, _texture, _size) == false) {
	//		return true;
	//	}
	//
	//	return false;
	//
	//#else
	std::map<std::string, ImageStruct>::iterator it = _imageMap.find(path);

	if (it != _imageMap.end()) {
		_texture = it->second._texture;
		_size = it->second._size;
		it->second.ref_count++;
		return true;
	}
	else {
		if (InitImage(path, _texture, _size) == false) {
			ImageStruct img_info(_texture, _size);
			_imageMap.insert(std::pair<std::string, ImageStruct>(path, img_info));
			return true;
		}
	}

	return false;
	//#endif // _AX_VST_APP_
}

void ImageGlobalMapLoader::RemoveImage(const std::string& path)
{
	std::map<std::string, ImageStruct>::iterator it = _imageMap.find(path);

	if (it != _imageMap.end()) {
		it->second.ref_count--;

		if (it->second.ref_count == 0) {
			glDeleteTextures(1, &it->second._texture);
			_imageMap.erase(it);
		}
	}
}

bool ImageGlobalMapLoader::InitImage(const std::string& path, GLuint& _texture, ax::Size& _size)
{

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "BEFORE LOAD IMAGE : OpenGL error in ax::Image with error code : " << err << std::endl;
	}
	//	glGenTextures(1, &_texture);

	// http://zarb.org/~gc/html/libpng.html.
	// http://stackoverflow.com/questions/11296644/loading-png-textures-to-opengl-with-libpng-only.
	// Reading png.
	png_byte header[8];

	FILE* fp = fopen(path.c_str(), "rb");

	if (fp == NULL) {
		std::cerr << "Error opening png image : " << path << std::endl;
		std::cerr << "Error : " << strerror(errno) << std::endl;
		LOG_INFO("Error opening png image : ");
		return 1;
	}

	// Read header.
	fread(header, 1, 8, fp);

	if (png_sig_cmp(header, 0, 8)) {
		std::cerr << "Error invalid image format." << std::endl;
		LOG_INFO("Error invalid image format.");
		fclose(fp);
		return true;
	}

	// Read png struct.
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		std::cerr << "Error png_create_read_struct." << std::endl;
		LOG_INFO("Error png_create_read_struct.");
		fclose(fp);
		return true;
	}

	// Create png info struct.
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		std::cerr << "Error png_create_info_struct." << std::endl;
		LOG_INFO("Error png_create_info_struct.");
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return true;
	}

	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info) {
		std::cerr << "Error png_create_info_struct." << std::endl;
		LOG_INFO("Error png_create_info_struct.");
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		fclose(fp);
		return true;
	}

	// Gets called if libpng encounters an error.
	if (setjmp(png_jmpbuf(png_ptr))) {
		std::cerr << "Error libpng." << std::endl;
		LOG_INFO("Error libpng.");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return true;
	}

	// Init png reading.
	png_init_io(png_ptr, fp);

	// Let libpng know you already read the first 8 bytes.
	png_set_sig_bytes(png_ptr, 8);

	// Read all info up to the image data.
	png_read_info(png_ptr, info_ptr);

	// Variables to get info.
	int depth, color_type;
	png_uint_32 w, h;

	// Get info about png.
	png_get_IHDR(png_ptr, info_ptr, &w, &h, &depth, &color_type, NULL, NULL, NULL);

	//    0       1,2,4,8,16  Each pixel is a grayscale sample.

	//    2       8,16        Each pixel is an R,G,B triple.

	//    3       1,2,4,8     Each pixel is a palette index;
	//                         a PLTE chunk must appear.

	//    4       8,16        Each pixel is a grayscale sample,
	//                         followed by an alpha sample.

	//    6       8,16        Each pixel is an R,G,B triple,
	//                         followed by an alpha sample.

	_size = ax::Size(w, h);

	// Update png info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Row size in bytes.
	int rowbytes = (int)png_get_rowbytes(png_ptr, info_ptr);

	// OpenGL glTexImage2d requires rows to be 4-byte aligned.
	rowbytes += 3 - ((rowbytes - 1) % 4);

	// Allocate the image_data as a big block, to be given to opengl.
	png_byte* image_data;
	image_data = (png_byte*)malloc(rowbytes * _size.h * sizeof(png_byte) + 15);

	if (image_data == NULL) {
		std::cerr << "Error memory allocation for PNG image data." << std::endl;
		LOG_INFO("Error memory allocation for PNG image data.");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

		fclose(fp);
		return true;
	}

	// Pointing to image_data for reading the png with libpng.
	png_bytep* row_pointers = (png_bytep*)malloc(_size.h * sizeof(png_bytep));

	if (row_pointers == NULL) {
		std::cout << "Error memory allocation for PNG row pointers." << std::endl;
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

		free(image_data);
		fclose(fp);
		return 1;
	}

	// Set each row_pointer at the correct offsets of image_data.
	for (int i = 0; i < _size.h; ++i) {
		row_pointers[_size.h - 1 - i] = image_data + i * rowbytes;
	}

	// Read png into image_data through row_pointers.
	png_read_image(png_ptr, row_pointers);

	//	err = glGetError();
	//	if (err != GL_NO_ERROR) {
	//		std::cout << "BEFORE glTex2D : OpenGL error in ax::Image with error code : " << err << std::endl;
	//	}

	glGenTextures(1, &_texture);
	// Bind texture object.
	glBindTexture(GL_TEXTURE_2D, _texture);

	if (color_type == 2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _size.w, _size.h, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.w, _size.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	}

	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "Error in image : " << path << std::endl;
		std::cout << "OpenGL error in ax::Image with error code : " << err << std::endl;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//--------------------------------------------------------------------------------------------------------------------
	// glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

	// clean up.
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	free(image_data);
	free(row_pointers);
	fclose(fp);

	return false;
}

Image::Image(const std::string& path)
{
	_path = path;

	if (!_path.empty()) {
		if (_globalMap.LoadImage(path, _texture, _size)) {
			_path = path;
		}
		else {
			std::cerr << "Error opening image" << std::endl;
			LOG_INFO("Error opening image");
		}
	}
}

Image::Image(void* data, const ax::Size& size, ColorType type)
	: _size(size)
	, _path("tmp")
{
	int c_type = GL_RGBA;

	if (type == ColorType::RGB) {
		c_type = GL_RGB;
	}

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexImage2D(GL_TEXTURE_2D, 0, c_type, _size.w, _size.h, 0, c_type, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Image::~Image()
{
	_globalMap.RemoveImage(_path);
	//	glDeleteTextures(1, &_texture);
}

bool Image::SaveImage(const std::string& path)
{
#ifdef ANDROID
	return false;
#else
	FILE* fp;
	png_structp png_ptr = nullptr;
	png_infop info_ptr = nullptr;
	png_byte** row_pointers = nullptr;

	/* "status" contains the return value of this function. At first
	 it is set to a value which means 'failure'. When the routine
	 has finished its work, it is set to a value which means
	 'success'. */
	// int status = -1;
	/* The following number is set by trial and error only. I cannot
	 see where it it is documented in the libpng manual.
	 */
	int pixel_size = 4;
	int depth = 8;

	fp = fopen(path.c_str(), "wb");

	if (!fp) {
		std::cerr << "Image::SaveImage : Can't open file : " << path << std::endl;

		return false;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (png_ptr == nullptr) {
		fclose(fp);
		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);

	if (info_ptr == nullptr) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
		//        goto png_create_info_struct_failed;
	}

	// Set up error handling.
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}

	// Set image attributes.
	png_set_IHDR(png_ptr, info_ptr, _size.w, _size.h, depth, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	// Initialize rows of PNG.

	// 0????????????????????????????????????????????????
	row_pointers = (png_byte**)png_malloc(png_ptr, _size.h * sizeof(png_byte*));

	// Get OpenGL texture data.
	glBindTexture(GL_TEXTURE_2D, _texture);

	unsigned char* data = new unsigned char[_size.w * _size.h * 4];
	glGetTexImage(GL_TEXTURE_2D, 0,
		GL_RGBA, // Format.
		GL_UNSIGNED_BYTE, // Type.
		(void*)data);

	//    unsigned char* data_ptr = data + sizeof(unsigned char) * _size.x *
	//    _size.y * 4;
	unsigned char* data_ptr; // = data;

	for (int y = 0; y < _size.h; ++y) {
		png_byte* row = (png_byte*)png_malloc(png_ptr, sizeof(uint8_t) * _size.w * pixel_size);

		row_pointers[y] = row;

		for (int x = 0; x < _size.w; ++x) {
			data_ptr = data + _size.w * (_size.h - 1 - y) * 4 + x * 4;

			*row++ = *data_ptr++;
			*row++ = *data_ptr++;
			*row++ = *data_ptr++;
			*row++ = *data_ptr++;
		}
	}

	// Write the image data to "fp".

	png_init_io(png_ptr, fp);
	png_set_rows(png_ptr, info_ptr, row_pointers);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	/* The routine has successfully written the file, so we set
	 "status" to a value which indicates success. */

	// status = 0;

	for (int y = 0; y < _size.h; y++) {
		png_free(png_ptr, row_pointers[y]);
	}
	png_free(png_ptr, row_pointers);

	// png_failure:
	// png_create_info_struct_failed:
	png_destroy_write_struct(&png_ptr, &info_ptr);

	// png_create_write_struct_failed:
	fclose(fp);

	// fopen_failed:
	return true; // status.
#endif
}

GLuint Image::GetTexture()
{
	return _texture;
}

ax::Size Image::GetSize()
{
	return _size;
}

int Image::GetHeight()
{
	return _size.h;
}

int Image::GetWidth()
{
	return _size.w;
}

bool Image::IsImageReady()
{
	return (_path != "");
}

//------------------------------------------------------------------------------
// axBigimage
//------------------------------------------------------------------------------

BigImage::BigImage(const std::string& path)
{
	if (InitImage(path)) {
		ax::console::Error("Can't load axBigImage : ", path);
	}
}

bool BigImage::InitImage(const std::string& path)
{
	// http://zarb.org/~gc/html/libpng.html.
	// http://stackoverflow.com/questions/11296644/loading-png-textures-to-opengl-with-libpng-only.
	// Reading png.
	png_byte header[8];

	FILE* fp = fopen(path.c_str(), "rb");

	if (fp == NULL) {
		std::cerr << "Error opening png image : " << path << std::endl;
		std::cerr << "Error : " << strerror(errno) << std::endl;
		return 1;
	}

	// Read header.
	fread(header, 1, 8, fp);

	if (png_sig_cmp(header, 0, 8)) {
		std::cerr << "Error invalid image format." << std::endl;
		fclose(fp);
		return true;
	}

	// Read png struct.
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		std::cerr << "Error png_create_read_struct." << std::endl;
		fclose(fp);
		return true;
	}

	// Create png info struct.
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		std::cerr << "Error png_create_info_struct." << std::endl;
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return true;
	}

	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info) {
		std::cerr << "Error png_create_info_struct." << std::endl;
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		fclose(fp);
		return true;
	}

	// Gets called if libpng encounters an error.
	if (setjmp(png_jmpbuf(png_ptr))) {
		std::cerr << "Error libpng." << std::endl;
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return true;
	}

	// Init png reading.
	png_init_io(png_ptr, fp);

	// Let libpng know you already read the first 8 bytes.
	png_set_sig_bytes(png_ptr, 8);

	// Read all info up to the image data.
	png_read_info(png_ptr, info_ptr);

	// Variables to get info.
	int depth, color_type;
	png_uint_32 w, h;

	// Get info about png.
	png_get_IHDR(png_ptr, info_ptr, &w, &h, &depth, &color_type, NULL, NULL, NULL);

	//    0       1,2,4,8,16  Each pixel is a grayscale sample.

	//    2       8,16        Each pixel is an R,G,B triple.

	//    3       1,2,4,8     Each pixel is a palette index;
	//                         a PLTE chunk must appear.

	//    4       8,16        Each pixel is a grayscale sample,
	//                         followed by an alpha sample.

	//    6       8,16        Each pixel is an R,G,B triple,
	//                         followed by an alpha sample.

	_size = ax::Size(w, h);

	// Update png info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Row size in bytes.
	int rowbytes = (int)png_get_rowbytes(png_ptr, info_ptr);

	// OpenGL glTexImage2d requires rows to be 4-byte aligned.
	rowbytes += 3 - ((rowbytes - 1) % 4);

	// Allocate the image_data as a big block, to be given to opengl.
	png_byte* image_data;
	image_data = (png_byte*)malloc(rowbytes * _size.h * sizeof(png_byte) + 15);

	if (image_data == NULL) {
		std::cerr << "Error memory allocation for PNG image data." << std::endl;
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

		fclose(fp);
		return true;
	}

	// Pointing to image_data for reading the png with libpng.
	png_bytep* row_pointers = (png_bytep*)malloc(_size.h * sizeof(png_bytep));

	if (row_pointers == NULL) {
		std::cout << "Error memory allocation for PNG row pointers." << std::endl;
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

		free(image_data);
		fclose(fp);
		return 1;
	}

	// Set each row_pointer at the correct offsets of image_data.
	for (int i = 0; i < _size.h; ++i) {
		row_pointers[_size.h - 1 - i] = image_data + i * rowbytes;
	}

	// Read png into image_data through row_pointers.
	png_read_image(png_ptr, row_pointers);

	// Copy image data.
	_pixelDepth = UNSIGNED_BYTE;

	if (color_type == 2) {
		const std::size_t b_size = _size.w * _size.h * 3 * sizeof(unsigned char);
		_imgData = new unsigned char[b_size];
		_colorType = RGB;
		memcpy(_imgData, image_data, b_size);
	}
	else {
		const std::size_t b_size = _size.w * _size.h * 4 * sizeof(unsigned char);
		_imgData = new unsigned char[b_size];
		_colorType = RGBA;
		memcpy(_imgData, image_data, b_size);
	}

	// clean up.
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	free(image_data);
	free(row_pointers);
	fclose(fp);

	return false;
}
}
