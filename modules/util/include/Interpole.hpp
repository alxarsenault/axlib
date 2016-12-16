#pragma once

#include <cmath>

/// @defgroup util
/// @{

namespace ax {
namespace util {
	namespace Interpole {
		template <typename T> T Lineair(const T& y1, const T& y2, const T& mu)
		{
			return y1 + mu * (y2 - y1);
		}

		template <typename T> T Logarithmic(const T& y1, const T& y2, const T& mu)
		{
			return pow(y2, mu) * pow(y1, 1.0 - mu);
		}
	}
}
}

/// @}
