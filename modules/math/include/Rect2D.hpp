#pragma once

#include "Point2D.hpp"
#include "Size2D.hpp"

/// @defgroup math
/// @{

namespace ax {
namespace math {
	/*
	 * ax::math::RectPoints.
	 */
	template <typename T> struct RectPoints {
		RectPoints()
		{
		}

		RectPoints(const T& bl, const T& tl, const T& tr, const T& br)
			: bottom_left(bl)
			, top_left(tl)
			, top_right(tr)
			, bottom_right(br)
		{
		}

		T bottom_left, top_left, top_right, bottom_right;
	};

	/*
	 * ax::math::Rect2D.
	 */
	template <typename T> class Rect2D {
	public:
		Rect2D(const Point2D<T>& pt_ = Point2D<T>(0, 0), const Size2D<T>& size_ = Size2D<T>(0, 0))
			: position(pt_)
			, size(size_)
		{
		}

		Rect2D(T x, T y, T w, T h)
			: position(x, y)
			, size(w, h)
		{
		}

		Rect2D(T x, T y, const Size2D<T>& size_)
			: position(x, y)
			, size(size_)
		{
		}

		Point2D<T> position;
		Size2D<T> size;

		//		template <typename P> Rect2D<P> Cast() const
		//		{
		//			return Rect2D<Point2D<P>, Point2D<P>, P>(position.template Cast<P>(), size.template
		// Cast<P>());
		//		}

		//		Rect2D operator+(const Rect2D& rect) const
		//		{
		//			return Rect2D(position.x + rect.position.x, position.y + rect.position.y, size.w +
		// rect.size.w,
		//				size.h + rect.size.h);
		//		}
		//
		//		Rect2D operator-(const Rect2D& rect) const
		//		{
		//			return Rect2D(position.x - rect.position.x, position.y - rect.position.y, size.w -
		// rect.size.w,
		//				size.h - rect.size.h);
		//		}
		//
		//		bool operator==(const Rect2D& rect) const
		//		{
		//			return (rect.position.x == position.x && rect.position.y == position.y && rect.size.x ==
		// size.x
		//				&& rect.size.y == size.y);
		//		}
		//
		//		bool operator!=(const Rect2D& rect) const
		//		{
		//			return ((rect.position.x != position.x || rect.position.y != position.y)
		//				|| (rect.size.x != size.x || rect.size.y != size.y));
		//		}
		//
		//		bool operator<(const Rect2D& rect) const
		//		{
		//			return (size.x < rect.size.x && size.y < rect.size.y);
		//		}
		//
		//		bool operator<=(const Rect2D& rect) const
		//		{
		//			return (size.x <= rect.size.x && size.y <= rect.size.y);
		//		}
		//
		//		bool operator>(const Rect2D& rect) const
		//		{
		//			return (size.x > rect.size.x && size.y > rect.size.y);
		//		}
		//
		//		bool operator>=(const Rect2D& rect) const
		//		{
		//			return (size.x >= rect.size.x && size.y >= rect.size.y);
		//		}

		bool IsPointInside(const Point2D<T>& pos) const
		{
			return pos.x >= position.x && pos.x <= position.x + size.w && pos.y >= position.y
				&& pos.y <= position.y + size.h;
		}

		Rect2D GetInteriorRect(const Point2D<T>& point) const
		{
			return Rect2D(position.x + point.x, position.y + point.y, size.w - (T)(2.0 * point.x),
				size.h - (T)(2.0 * point.y));
		}

		Point2D<T> GetTopLeft() const
		{
			return position;
		}

		Point2D<T> GetTopRight() const
		{
			return Point2D<T>(position.x + size.w, position.y);
		}

		Point2D<T> GetBottomLeft() const
		{
			return Point2D<T>(position.x, position.y + size.h);
		}

		Point2D<T> GetBottomRight() const
		{
			return Point2D<T>(position.x + size.w, position.y + size.h);
		}

		Point2D<T> GetMiddle() const
		{
			return Point2D<T>(position.x + size.w * 0.5, position.y + size.h * 0.5);
		}

		Point2D<T> GetNextPosRight(const T& delta) const
		{
			return Point2D<T>(position.x + size.w + delta, position.y);
		}

		Point2D<T> GetNextPosDown(const T& delta) const
		{
			return Point2D<T>(position.x, position.y + size.h + delta);
		}

		Point2D<T> GetNextPosLeft(const T& delta) const
		{
			return Point2D<T>(position.x, position.y - delta);
		}

		Point2D<T> GetNextPosUp(const T& delta) const
		{
			return Point2D<T>(position.x, position.y - delta);
		}

		template <typename P> RectPoints<P> GetPoints() const
		{
			return RectPoints<P>(P(position.x, position.y + size.h), P(position.x, position.y),
				P(position.x + size.w, position.y), P(position.x + size.w, position.y + size.h));
		}

		friend std::ostream& operator<<(std::ostream& stream, const Rect2D& rect)
		{
			stream << rect.position.x << ", " << rect.position.y << ", " << rect.size.w << ", "
				   << rect.size.h;
			return stream;
		}
	};
}
}

/// @}
