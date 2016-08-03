#pragma once

#include "Point2D.hpp"
#include "Size2D.hpp"
#include "Rect2D.hpp"

/// @defgroup math
/// @{

namespace ax {
// ax::Point
typedef math::Point2D<int> Point;
typedef math::Point2D<float> FPoint;

// ax::Size
typedef math::Size2D<int> Size;
typedef math::Size2D<float> FSize;

// ax::Rect
typedef math::Rect2D<int> Rect;
typedef math::Rect2D<float> FRect;
}

/// @}
