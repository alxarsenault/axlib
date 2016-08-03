#pragma once

#include <iostream>

/// @defgroup math
/// @{

namespace ax {
namespace math {
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
