#pragma once

#include <iostream>
#include <vector>
#include <string>

/// @defgroup util
/// @{

namespace ax {
namespace util {
	/*
	 * ax::util::Size2D.
	 */
	template <typename T> class Size2D {
	public:
		Size2D(T W = 0, T H = 0)
		{
			w = W;
			h = H;
		}
		
		Size2D(const std::pair<T, T>& p) :
		 w(p.first),
		 h(p.second)
		{
		
		}

		Size2D(const std::string& size_str)
			: w(-1)
			, h(-1)
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

			w = (T)std::stod(size_elem[0]);
			h = (T)std::stod(size_elem[1]);
		}

		T w, h;
		
		std::pair<T, T> ToPair() const {
			return std::pair<T, T>(w, h);
		}

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
