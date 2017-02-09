#pragma once

#include <iostream>
#include <string>
#include <vector>

/// @defgroup util
/// @{

namespace ax {
namespace util {
	/*
	 * Range2D.
	 */
	template <typename T> class Range2D {
	public:
		Range2D(T l = 0, T r = 0)
			: left(l)
			, right(r)
		{
		}

		Range2D(const std::string& size_str)
			: left(0)
			, right(1)
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

			left = (T)std::stod(size_elem[0]);
			right = (T)std::stod(size_elem[1]);
		}

		bool IsInside(T value) const
		{
			return value >= left && value <= right;
		}

		bool IsSmaller(T value) const
		{
			return value < left;
		}

		bool IsBigger(T value) const
		{
			return value > right;
		}

		double GetZeroToOneValue(double value) const
		{
			const double denum = right - left;

			if (denum == 0.0) {
				return 0.0;
			}

			double v = double(value - left) / denum;

			if (v > 1.0)
				v = 1.0;

			else if (v < 0.0)
				v = 0.0;

			return v;
		}

		double GetValueFromZeroToOne(double value)
		{
			double v = double(left) + value * double(right - left);

			if (v > right)
				v = right;

			else if (v < left)
				v = left;

			return v;
		}

		std::string ToString() const
		{
			return std::to_string(left) + ", " + std::to_string(right);
		}

		friend std::ostream& operator<<(std::ostream& stream, const Range2D& range)
		{
			stream << range.left << ", " << range.right;
			return stream;
		}

		T left, right;
	};
}
}

/// @}
