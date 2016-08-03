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

#ifndef __AX_MATH__
#define __AX_MATH__

/// @defgroup Graphic
/// @{

#include "Util.hpp"
#include "Math.hpp"

namespace ax {
namespace GL {
	namespace Math {
		void displayModelviewMatrix(float MV[16]);

		uint32_t GetModelViewMatrixId();

		class Matrix4 {
		public:
			Matrix4();

#ifdef ANDROID
			Matrix4(float* data);
#else
			Matrix4(double* data);
#endif

			Matrix4(uint32_t matrix);

#ifdef ANDROID
			float* GetData();
#else
			double* GetData();
#endif

			Matrix4& Identity();

			Matrix4& Translate(const ax::Point& vec);

			Matrix4& Multiply(const Matrix4& mat);

			void Process();

			void Load();

		private:
#ifdef ANDROID
			float _data[16];
#else
			double _data[16];
#endif
		};

#ifdef ANDROID
		void Ortho2D(float* data, const ax::Size& size);
#else
		void Ortho2D(double* data, const ax::Size& size);
#endif
	}
}
}

// namespace axMath
//{
//    static const double e       =  2.718281828459045235360;
//    static const double pi      =  3.141592653589793238462;
//    static const double pi_2    =  1.570796326794896619231;
//    static const double pi_4    =  0.785398163397448309616;
//    static const double pi_180  =  0.017453292519943295769;
//    static const double _1_pi   =  0.318309886183790671538;
//    static const double _2_pi   =  0.636619772367581343076;
//    static const double _180_pi = 57.295779513082320876798;
//    static const double log2    =  0.693147180559945309417;
//    static const double sqrt2   =  1.414213562373095048801;
//}

/// @}
#endif // __AX_MATH__
