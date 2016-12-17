#pragma once

#include <iostream>
#include <vector>
#include <string>

/// @defgroup util
/// @{

namespace ax {
namespace util {
	/*
	 * ax::util::Point2D.
	 */
	template <typename T> class Point2D {
	public:
		Point2D(T X = 0, T Y = 0)
		{
			x = X;
			y = Y;
		}
		
		Point2D(const std::pair<T, T>& p) :
		x(p.first),
		y(p.second)
		{
		
		}
		
		Point2D(const std::string& size_str)
		: x(-1)
		, y(-1)
		{
			// Split string.
			std::vector<std::string> size_elem;
			std::string r = size_str;
			size_t pos = 0;
			std::string token;
			const std::string delimiter(",");
			
			while ((pos = r.find(delimiter)) != std::string::npos) {
				token = r.substr(0, pos);
				size_elem.push_back(token);
				r.erase(0, pos + delimiter.length());
			}
			
			size_elem.push_back(r);
			
			if (size_elem.size() != 2) {
				return;
			}
			
			x = (T)std::stod(size_elem[0]);
			y = (T)std::stod(size_elem[1]);
		}

		T x, y;
		
		std::pair<T, T> ToPair() const {
			return std::pair<T, T>(x, y);
		}

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
