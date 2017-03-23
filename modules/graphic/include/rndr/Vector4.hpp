#pragma once

#include <cmath>

namespace ax {
namespace rndr {
	template <typename T> struct Vector4 {
		Vector4()
		{
		}

		Vector4(T a, T b, T c, T d)
			: x(a)
			, y(b)
			, z(c)
			, w(d)
		{
		}

		Vector4(T scalar)
			: x(scalar)
			, y(scalar)
			, z(scalar)
			, w(scalar)
		{
		}

		T& operator[](std::size_t index);

		T* data()
		{
			return static_cast<T*>(static_cast<void*>(this));
		}

		const T* data() const
		{
			return &x;
		}

		Vector4 operator+(const Vector4& vec) const;
		Vector4& operator+=(const Vector4& vec);

		Vector4 operator+(T scalar) const;
		Vector4& operator+=(T scalar);

		Vector4 operator-(const Vector4& vec) const;
		Vector4& operator-=(const Vector4& vec);

		Vector4 operator-(T scalar) const;
		Vector4& operator-=(T scalar);

		Vector4 operator*(const Vector4& vec) const;
		Vector4& operator*=(const Vector4& vec);

		Vector4 operator*(T scalar) const;
		Vector4& operator*=(T scalar);

		T norm() const;
		void normalize();
		Vector4<T> get_normalize() const;

		union {
			struct {
				T x, y, z, w;
			}; // Homogeneous coordinates.
			struct {
				T s, t, p, q;
			}; // Normal vector.
		};
	};

	template <typename T> T& Vector4<T>::operator[](std::size_t index)
	{
		return data()[index];
	}

	template <typename T> Vector4<T> Vector4<T>::operator+(const Vector4<T>& vec) const
	{
		return Vector4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	template <typename T> Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}

	template <typename T> Vector4<T> Vector4<T>::operator+(T scalar) const
	{
		return Vector4<T>(x + scalar, y + scalar, z + scalar, w + scalar);
	}

	template <typename T> Vector4<T>& Vector4<T>::operator+=(T scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
		return *this;
	}

	template <typename T> Vector4<T> Vector4<T>::operator-(const Vector4<T>& vec) const
	{
		return Vector4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}

	template <typename T> Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}

	template <typename T> Vector4<T> Vector4<T>::operator-(T scalar) const
	{
		return Vector4<T>(x - scalar, y - scalar, z - scalar, w - scalar);
	}

	template <typename T> Vector4<T>& Vector4<T>::operator-=(T scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
		return *this;
	}

	template <typename T> Vector4<T> Vector4<T>::operator*(const Vector4<T>& vec) const
	{
		return Vector4<T>(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
	}

	template <typename T> Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& vec)
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		w *= vec.w;
		return *this;
	}

	template <typename T> Vector4<T> Vector4<T>::operator*(T scalar) const
	{
		return Vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	template <typename T> Vector4<T>& Vector4<T>::operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	template <typename T> T Vector4<T>::norm() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	template <typename T> void Vector4<T>::normalize()
	{
		T n = norm();
		x /= n;
		y /= n;
		z /= n;
		w /= n;
	}

	template <typename T> Vector4<T> Vector4<T>::get_normalize() const
	{
		T n = norm();
		return Vector4<T>(x / n, y / n, z / n, w / n);
	}
}
}
