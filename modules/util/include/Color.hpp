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

#pragma once

/// @defgroup util
/// @{

#include "Clamp.hpp"
#include "axString.hpp"
#include "ConsolePrint.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>

namespace ax {
namespace util {

	template <typename T> class Color {
	public:
		static Color FromString(const std::string& color_str)
		{
			std::vector<std::string> color_elem = String::Split(color_str, ",");
			Color color(0.0f, 0.0f, 0.0f, 1.0f);

			if (color_elem.size() < 3) {
				ax::util::console::Print(
					"Parsing color (not enough argument) -> should be \"r, g, b\" or \"r, g, b, a\".");
				return color;
			}
			else if (color_elem.size() > 4) {
				ax::util::console::Print(
					"Parsing color (too many argument) -> should be \"r, g, b\" or \"r, g, b, a\".");
				return color;
			}

			color.SetRed(std::stoi(color_elem[0]) / 255.0f);
			color.SetGreen(std::stoi(color_elem[1]) / 255.0f);
			color.SetBlue(std::stoi(color_elem[2]) / 255.0f);

			if (color_elem.size() == 4) {
				color.SetAlpha(std::stoi(color_elem[3]) / 255.0f);
			}

			return color;
		}

		explicit Color(const T& r, const T& g, const T& b)
			: _r(r)
			, _g(g)
			, _b(b)
			, _a(1.0)
		{
		}

		explicit Color(const T& r, const T& g, const T& b, const T& a)
			: _r(r)
			, _g(g)
			, _b(b)
			, _a(a)
		{
		}

		explicit Color(const int& r, const int& g, const int& b, const int& a = 255)
			: _r(r / 255.0f)
			, _g(g / 255.0f)
			, _b(b / 255.0f)
			, _a(a / 255.0f)
		{
		}

		explicit Color(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a = 255)
			: _r(r / 255.0f)
			, _g(g / 255.0f)
			, _b(b / 255.0f)
			, _a(a / 255.0f)
		{
		}

		Color()
			: _r(0.0)
			, _g(0.0)
			, _b(0.0)
			, _a(1.0)
		{
		}

		Color(const Color& col)
			: _r(col._r)
			, _g(col._g)
			, _b(col._b)
			, _a(col._a)
		{
		}

		Color(const T& all, const T& alpha)
			: _r(all)
			, _g(all)
			, _b(all)
			, _a(alpha)
		{
		}

		Color(const T& all)
			: _r(all)
			, _g(all)
			, _b(all)
			, _a(1)
		{
		}

		inline bool operator==(const Color& c)
		{
			return _r == c._r && _g == c._g && _b == c._b && _a == c._a;
		}

		inline bool operator!=(const Color& c)
		{
			return !(operator==(c));
		}

		Color(const std::string& color)
		{
			std::string c = color;

			unsigned int r_i, g_i, b_i;

			sscanf(c.substr(1, 2).c_str(), "%x", &r_i);
			sscanf(c.substr(3, 2).c_str(), "%x", &g_i);
			sscanf(c.substr(5, 2).c_str(), "%x", &b_i);

			_r = T(r_i / 255.0);
			_g = T(g_i / 255.0);
			_b = T(b_i / 255.0);
			_a = 1.0;
		}

		T GetRed() const
		{
			return _r;
		}

		T GetGreen() const
		{
			return _g;
		}

		T GetBlue() const
		{
			return _b;
		}

		T GetAlpha() const
		{
			return _a;
		}

		void SetRed(const T& red)
		{
			_r = ax::util::Clamp<T>(red, 0.0, 1.0);
		}

		void SetGreen(const T& green)
		{
			_g = ax::util::Clamp<T>(green, 0.0, 1.0);
		}

		void SetBlue(const T& blue)
		{
			_b = ax::util::Clamp<T>(blue, 0.0, 1.0);
		}

		void SetAlpha(const T& alpha)
		{
			_a = ax::util::Clamp<T>(alpha, 0.0, 1.0);
		}

		// Serialization.
		void SerializeOutput(std::fstream& out)
		{
			out.write(reinterpret_cast<char*>(this), sizeof(Color));
		}

		void SerializeInput(std::fstream& in)
		{
			in.read(reinterpret_cast<char*>(this), sizeof(Color));
		}

		void LoadFromString(const std::string& str)
		{
			if (str.find_first_of("#") != std::string::npos) {
				std::string c = str;

				unsigned int r_i, g_i, b_i;

				sscanf(c.substr(1, 2).c_str(), "%x", &r_i);
				sscanf(c.substr(3, 2).c_str(), "%x", &g_i);
				sscanf(c.substr(5, 2).c_str(), "%x", &b_i);

				_r = T(r_i / 255.0);
				_g = T(g_i / 255.0);
				_b = T(b_i / 255.0);
				_a = 1.0;
			}
			else {
				std::vector<std::string> strVec = String::Split(str, ",");
				_r = stof(strVec[0]);
				_g = stof(strVec[1]);
				_b = stof(strVec[2]);

				if (strVec.size() == 4) {
					_a = stof(strVec[3]);
				}
				else {
					_a = 1.0;
				}
			}
		}

		std::string ToString() const
		{
			std::string red = std::to_string(int(_r * 255));
			std::string green = std::to_string(int(_g * 255));
			std::string blue = std::to_string(int(_b * 255));
			std::string alpha = std::to_string(int(_a * 255));
			return red + ", " + green + ", " + blue + ", " + alpha;
		}

		Color Interpolate(const Color& color, const float& mu) const
		{
			return Color(_r + (color._r - _r) * mu, _g + (color._g - _g) * mu, _b + (color._b - _b) * mu,
				_a + (color._a - _a) * mu);
		}

		friend std::ostream& operator<<(std::ostream& stream, const Color<float>& color)
		{
			stream << int(color._r * 255) << ", " << int(color._g * 255) << ", " << int(color._b * 255)
				   << ", " << int(color._a * 255);
			return stream;
		}

	private:
		T _r, _g, _b, _a;
	};

	typedef std::vector<Color<float>> ColorVector;

	ColorVector CreateHeatColors(const int& n);
	ColorVector CreateRainbowColors(const int& n);
}
}

/// @}
