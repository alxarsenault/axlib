#pragma once

#include <iostream>

/// @defgroup math
/// @{

namespace ax {
namespace math {
	/*
	 * ax::math::Point2D.
	 */
	template <typename T> class Point2D {
	public:
		Point2D(T X = 0, T Y = 0)
		{
			x = X;
			y = Y;
		}

		T x, y;

		template <typename P> Point2D<P> Cast() const
		{
			return Point2D<P>((P)x, (P)y);
		}

		Point2D operator*(const Point2D& pt) const
		{
			return Point2D(x * pt.x, y * pt.y);
		}

		Point2D operator*(const T& v) const
		{
			return Point2D(x * v, y * v);
		}

		Point2D& operator*=(const Point2D& pt)
		{
			x *= pt.x;
			y *= pt.y;
			return *this;
		}

		Point2D& operator*=(const T& v)
		{
			x *= v;
			y *= v;
			return *this;
		}

		Point2D operator+(const Point2D& pt) const
		{
			return Point2D(x + pt.x, y + pt.y);
		}

		Point2D operator-(const Point2D& pt) const
		{
			return Point2D(x - pt.x, y - pt.y);
		}

		Point2D& operator+=(const Point2D& pt)
		{
			x += pt.x;
			y += pt.y;
			return *this;
		}

		Point2D& operator-=(const Point2D& pt)
		{
			x -= pt.x;
			y -= pt.y;
			return *this;
		}

		Point2D& operator-=(const T& v)
		{
			x -= v;
			y -= v;
			return *this;
		}

		Point2D& operator=(const T& pt)
		{
			x = pt;
			y = pt;
			return *this;
		}

		Point2D& operator=(const Point2D& pt)
		{
			x = pt.x;
			y = pt.y;
			return *this;
		}

		bool operator==(const Point2D& pt)
		{
			return (x == pt.x && y == pt.y);
		}

		bool operator!=(const Point2D& pt)
		{
			return !(x == pt.x && y == pt.y);
		}

		bool operator<(const Point2D& pt)
		{
			return (x < pt.x && y < pt.y);
		}

		bool operator<=(const Point2D& pt)
		{
			return (x <= pt.x && y <= pt.y);
		}

		bool operator>(const Point2D& pt)
		{
			return (x > pt.x && y > pt.y);
		}

		bool operator>=(const Point2D& pt)
		{
			return (x >= pt.x && y >= pt.y);
		}

		Point2D& operator()(const T& X, const T& Y)
		{
			x = X;
			y = Y;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& stream, const Point2D& point)
		{
			stream << point.x << ", " << point.y;
			return stream;
		}
	};
}
}

/// @}
