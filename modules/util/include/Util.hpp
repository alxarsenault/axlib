#pragma once

/// @defgroup util
/// @{

#include "Clamp.hpp"
#include "axString.hpp"
#include "Control.hpp"
#include "Direction.hpp"
#include "Var.hpp"
#include "ConsolePrint.hpp"
#include "Flag.hpp"
#include "Color.hpp"
#include "Property.hpp"
#include "ResourceStorage.hpp"
#include "Component.hpp"
#include "Memory.hpp"
#include "Point2D.hpp"
#include "Size2D.hpp"
#include "Rect2D.hpp"
#include "Range2D.hpp"

namespace ax {

// ax::Color
typedef util::Color<float> Color;

// ax::Property
typedef util::Property<std::string> Property;

namespace console = util::console;

// ax::Point
typedef util::Point2D<int> Point;
typedef util::Point2D<float> FPoint;

// ax::Size
typedef util::Size2D<int> Size;
typedef util::Size2D<float> FSize;

// ax::Rect
typedef util::Rect2D<int> Rect;
typedef util::Rect2D<float> FRect;
}

/// @}
