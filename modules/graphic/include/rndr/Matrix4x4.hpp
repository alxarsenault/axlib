#pragma once

#include "Vector4.hpp"

namespace ax {
namespace rndr {
	template <typename T> struct Matrix4x4 {
		Vector4<T> value[4];

		inline T* data()
		{
			return value[0].data();
		}

		inline const T* data() const
		{
			return value[0].data();
		}

		Matrix4x4& operator*=(const Matrix4x4& mat)
		{
			T* d = data();
			const T* m_d = mat.data();

			for (unsigned int i = 0; i < 16; i += 4) {
				for (unsigned int j = 0; j < 4; ++j) {
					d[i + j] = (m_d[i] * d[j]) + (m_d[i + 1] * d[j + 4]) + (m_d[i + 2] * d[j + 8])
						+ (m_d[i + 3] * d[j + 12]);
				}
			}

			return *this;
		}

		static Matrix4x4 Identity()
		{
			return { Vector4<T>{ 1.0f, 0.0f, 0.0f, 0.0f }, Vector4<T>{ 0.0f, 1.0f, 0.0f, 0.0f }, Vector4<T>{ 0.0f, 0.0f, 1.0f, 0.0f },
				Vector4<T>{ 0.0f, 0.0f, 0.0f, 1.0f } };
		}

		//            Matrix4x4& Translate(const ax::Point& vec)
		//            {
		//                Matrix4x4 trans;
		//                trans.Identity();
		//                trans._data[12] = vec.x;
		//                trans._data[13] = vec.y;
		//                trans._data[14] = 0.0;
		//
		//                Multiply(trans);
		//
		//                return *this;
		//            }
	};
}
}
