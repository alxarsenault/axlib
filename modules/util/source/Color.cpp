/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axLib.
 *
 * axLib is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axFrameworks License.
 *
 * axLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLib. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLib, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */
 
#include "Color.hpp"

namespace ax {
namespace util {

	ColorVector CreateHeatColors(const int& n)
	{
		ColorVector colors;
		float incr = 1.0 / float(n);
		float v = 0.0;

		float r = 1.0;
		float g = 0.0;
		float b = 0.0;

		for (int i = 0; i < n; i++) {
			g = v;
			v += incr;

			if (v > 1.0)
				v = 1.0;
			if (g > 1.0)
				g = 1.0;

			colors.emplace_back(Color<float>(r, g, b, 1.0));
		}

		return colors;
	}

	ColorVector CreateRainbowColors(const int& n)
	{
		ColorVector colors;

		float separation = 1.0 / 6.0;
		float incr = 1.0 / float(n);
		float v = 0.0;

		for (int i = 0; i < n; i++) {
			float r = 0.0;
			float g = 0.0;
			float b = 0.0;

			float ratio = 0.0;

			float t = v;

			if (t > 5 * separation) {
				ratio = (t - (5.0 * separation)) / (separation);

				r = 1.0;
				g = 0.0;
				b = 1.0 - ratio;
			}
			else if (t > 4 * separation) {
				ratio = (t - (4.0 * separation)) / (separation);

				r = ratio;
				g = 0.0;
				b = 1.0;
			}
			else if (t > 3 * separation) {
				ratio = (t - (3.0 * separation)) / (separation);
				r = 0.0;
				g = 1.0 - ratio;
				b = 1.0;
			}
			else if (t > 2 * separation) {
				ratio = (t - (2.0 * separation)) / (separation);
				r = 0.0;
				g = 1.0;
				b = ratio;
			}
			else if (t > separation) {
				ratio = (t - separation) / (separation);
				r = 1.0 - ratio;
				g = 1.0;
				b = 0.0;
			}
			else {
				ratio = t / (separation);
				r = 1.0;
				g = ratio;
				b = 0.0;
			}

			v += incr;

			if (v > 1.0)
				v = 1.0;
			if (r > 1.0)
				r = 1.0;
			if (g > 1.0)
				g = 1.0;
			if (b > 1.0)
				b = 1.0;

			colors.emplace_back(Color<float>(r, g, b, 1.0));
		}

		return colors;
	}
}
}
