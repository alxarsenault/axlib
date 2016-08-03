#pragma once

#include <iostream>

/// @defgroup math
/// @{

namespace ax {
namespace math {
	/*
	 * ax::math::Size2D.
	 */
	template <typename T> class Size2D {
	public:
		Size2D(T W = 0, T H = 0)
		{
			w = W;
			h = H;
		}

		T w, h;

		template <typename P> Size2D<P> Cast() const
		{
			return Size2D<P>((P)w, (P)h);
		}

		Size2D operator*(const Size2D& size) const
		{
			return Size2D(w * size.w, h * size.h);
		}

		Size2D operator*(const T& v) const
		{
			return Size2D(w * v, h * v);
		}

		Size2D& operator*=(const Size2D& size)
		{
			w *= size.w;
			h *= size.h;
			return *this;
		}

		Size2D& operator*=(const T& v)
		{
			w *= v;
			h *= v;
			return *this;
		}

		Size2D operator+(const Size2D& size) const
		{
			return Size2D(w + size.w, h + size.h);
		}

		Size2D operator-(const Size2D& size) const
		{
			return Size2D(w - size.w, h - size.h);
		}

		Size2D& operator+=(const Size2D& size)
		{
			w += size.w;
			h += size.h;
			return *this;
		}

		Size2D& operator-=(const Size2D& size)
		{
			w -= size.w;
			h -= size.h;
			return *this;
		}

		Size2D& operator-=(const T& v)
		{
			w -= v;
			h -= v;
			return *this;
		}

		Size2D& operator=(const T& size)
		{
			w = size;
			h = size;
			return *this;
		}

		Size2D& operator=(const Size2D& size)
		{
			w = size.w;
			h = size.h;
			return *this;
		}

		bool operator==(const Size2D& size)
		{
			return (w == size.w && h == size.h);
		}

		bool operator!=(const Size2D& size)
		{
			return !(w == size.w && h == size.h);
		}

		bool operator<(const Size2D& size)
		{
			return (w < size.w && h < size.h);
		}

		bool operator<=(const Size2D& size)
		{
			return (w <= size.w && h <= size.h);
		}

		bool operator>(const Size2D& size)
		{
			return (w > size.w && h > size.h);
		}

		bool operator>=(const Size2D& size)
		{
			return (w >= size.w && h >= size.h);
		}

		Size2D& operator()(const T& W, const T& H)
		{
			w = W;
			h = H;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& stream, const Size2D& size)
		{
			stream << size.w << ", " << size.h;
			return stream;
		}
	};
}
}

/// @}
