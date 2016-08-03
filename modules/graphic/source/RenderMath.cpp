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
#include "RenderMath.hpp"
#include "Render.hpp"

namespace ax {
namespace GL {
	namespace Math {

		uint32_t GetModelViewMatrixId()
		{
			return GL_MODELVIEW_MATRIX;
		}

		Matrix4::Matrix4()
		{
			for (int i = 0; i < 16; i++) {
				_data[i] = 0.0;
			}
		}
#ifdef ANDROID
		Matrix4::Matrix4(float* data)
#else
		Matrix4::Matrix4(double* data)
#endif
		{
			for (int i = 0; i < 16; i++) {
				_data[i] = data[i];
			}
		}

		Matrix4::Matrix4(uint32_t matrix)
		{
#ifdef ANDROID
			float data[16];
			glGetFloatv(matrix, data);
#else
			double data[16];
			glGetDoublev(matrix, data);

#endif

			for (int i = 0; i < 16; i++) {
				_data[i] = data[i];
			}
		}

#ifdef ANDROID
		float* Matrix4::GetData()
#else
		double* Matrix4::GetData()
#endif
		{
			return _data;
		}

		void Matrix4::Load()
		{
#ifdef ANDROID
			glLoadMatrixf(_data);
#else
			glLoadMatrixd(_data);
#endif
		}

		Matrix4& Matrix4::Identity()
		{
			for (int i = 0; i < 16; i++) {
				_data[i] = 0.0;
			}

			_data[0] = 1.0;
			_data[5] = 1.0;
			_data[10] = 1.0;
			_data[15] = 1.0;

			return *this;
		}

		Matrix4& Matrix4::Translate(const ax::Point& vec)
		{
			Matrix4 trans;
			trans.Identity();
			trans._data[12] = vec.x;
			trans._data[13] = vec.y;
			trans._data[14] = 0.0;

			Multiply(trans);

			return *this;
		}

		Matrix4& Matrix4::Multiply(const Matrix4& mat)
		{
			for (unsigned int i = 0; i < 16; i += 4) {
				for (unsigned int j = 0; j < 4; ++j) {
					_data[i + j] = (mat._data[i] * _data[j])
						+ (mat._data[i + 1] * _data[j + 4])
						+ (mat._data[i + 2] * _data[j + 8])
						+ (mat._data[i + 3] * _data[j + 12]);
				}
			}

			return *this;
		}

		void Matrix4::Process()
		{
#ifdef ANDROID
			glMultMatrixf(_data);
#else
			glMultMatrixd(_data);
#endif
		}

#ifdef ANDROID
		void Ortho2D(float* data, const ax::Size& size)
#else
		void Ortho2D(double* data, const ax::Size& size)
#endif
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			////                if( origin_lower_left )
			//                {
			////                    glOrthof(0, double(size.x), double(size.y),
			///0, -1, 1);
			//                }
			////                else
			//                {
			//                    glOrthof(0, double(size.x), 0, double(size.y),
			//                    -1, 1);
			//                }
			data[0] = 2.0 / double(size.w);
			data[4] = 0.0;
			data[8] = 0.0;
			data[12] = -1.0;

			data[1] = 0.0;
			data[5] = -2.0 / double(size.w);
			data[9] = 0.0;
			data[13] = 1.0;

			data[2] = 0.0;
			data[6] = 0.0;
			data[10] = -1.0;
			data[14] = 0.0;

			data[3] = 0.0;
			data[7] = 0.0;
			data[11] = 0.0;
			data[15] = 1.0;
////
////
////
////
#ifdef ANDROID
			glMultMatrixf(data);
#else
			glMultMatrixd(data);
#endif
		}
	}
}
}
