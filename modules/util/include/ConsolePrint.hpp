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

#include <iostream>
#include <iomanip>
#include <ctime>
#include <mutex>

namespace ax {
namespace util {
	namespace console {
		/// Use to order output sequence when using multiple threads.
		extern std::recursive_mutex safe_print_mutex;

		/// List of basic ansi escape color sequence.
		/// Don't change the order of this enum.
		enum class Color {
			Reset,

			Black,
			Red,
			Green,
			Yellow,
			Blue,
			Magenta,
			Cyan,
			White,

			BoldBlack,
			BoldRed,
			BoldGreen,
			BoldYellow,
			BoldBlue,
			BoldMagenta,
			BoldCyan,
			BoldWhite
		};

		/// Convert color type to ansi escape color string.
		std::ostream& operator<<(std::ostream& stream, const Color& color);

		/// Find is type is Color.
		/// Used to remove space character after printing color.
		template <class T> struct TypeIsColor {
			static const bool value = false;
		};

		/// Specialized TypeIsColor implementation.
		template <> struct TypeIsColor<Color> {
			static const bool value = true;
		};

		/*
		 * Write.
		 */

		/// Write to stdout without space or endline at the end of stream.
		template <typename T, typename... P> void Write(T t, P... p);

		/// Write variadic.
		template <typename T, typename... P> void WriteChild(T t, P... p);

		/// Write variadic end point.
		void WriteChild();

		/*
		 * Print.
		 */

		/// Print to stdout with space between each arguments and endline at the end of stream.
		template <typename T, typename... P> void Print(T t, P... p);

		/// Print variadic.
		template <typename T, typename... P> void PrintChild(T t, P... p);

		/// Print variadic end point.
		void PrintChild();

		/*
		 * Warning.
		 */

		/// Print to stdout in bold orange.
		template <typename T, typename... P> void Warning(T t, P... p);

		/*
		 * Log.
		 */

		/// Print to console with time stamp (HH:MM:SS : ).
		template <typename T, typename... P> void Log(T t, P... p);

		/*
		 * CPrint.
		 */

		/// Print to stdout and reset to default color and style at the end of stream.
		template <typename T, typename... P> void CPrint(T t, P... p);

		/// CPrintChild variadic.
		template <typename T, typename... P> void CPrintChild(T t, P... p);

		/// CPrintChild variadic end point.
		void CPrintChild();

		/*
		 * Error.
		 */

		/// Print to stderr in bold red with timestamp.
		template <typename T, typename... P> void Error(T t, P... p);

		/// Error variadic.
		template <typename T, typename... P> void ErrorChild(T t, P... p);

		// Error variadic end point.
		void ErrorChild();
	} // console.
} // util.
} // ax.

/*
 * Template implementations.
 */
namespace ax {
namespace util {
	namespace console {

		/*
		 * Write.
		 */

		template <typename T, typename... P> void WriteChild(T t, P... p)
		{
			std::cout << t;
			WriteChild(p...);
		}

		template <typename T, typename... P> void Write(T t, P... p)
		{
			safe_print_mutex.lock();
			{
				std::cout << t;
				WriteChild(p...);
			}
		}

		/*
		 * Print.
		 */

		void PrintChild();

		template <typename T, typename... P> void PrintChild(T t, P... p)
		{
			if (TypeIsColor<T>::value) {
				std::cout << t;
			}
			else {
				std::cout << t << ' ';
			}

			PrintChild(p...);
		}

		template <typename T, typename... P> void Print(T t, P... p)
		{
			safe_print_mutex.lock();
			{
				if (TypeIsColor<T>::value) {
					std::cout << t;
				}
				else {
					std::cout << t << ' ';
				}

				PrintChild(p...);
			}
		}

		/*
		 * Warning.
		 */
		template <typename T, typename... P> void Warning(T t, P... p)
		{
			safe_print_mutex.lock();
			{
				std::cout << "[WARNING] : " << t << ' ';
				CPrintChild(p...);
			}
		}

		/*
		 * Log.
		 */

		template <typename T, typename... P> void Log(T t, P... p)
		{
			safe_print_mutex.lock();

			std::time_t tt = std::time(nullptr);
			std::cout << "[" << std::put_time(std::localtime(&tt), "%T") << "] : ";

			if (TypeIsColor<T>::value) {
				std::cout << t;
			}
			else {
				std::cout << t << ' ';
			}

			PrintChild(p...);
		}

		/*
		 * CPrint.
		 */

		template <typename T, typename... P> void CPrintChild(T t, P... p)
		{
			if (TypeIsColor<T>::value) {
				std::cout << t;
			}
			else {
				std::cout << t << ' ';
			}

			CPrintChild(p...);
		}

		template <typename T, typename... P> void CPrint(T t, P... p)
		{
			safe_print_mutex.lock();
			{
				if (TypeIsColor<T>::value) {
					std::cout << t;
				}
				else {
					std::cout << t << ' ';
				}

				CPrintChild(p...);
			}
		}

		/*
		 * Error.
		 */
		template <typename T, typename... P> void ErrorChild(T t, P... p)
		{
			if (TypeIsColor<T>::value) {
				std::cerr << t;
			}
			else {
				std::cerr << t << ' ';
			}

			ErrorChild(p...);
		}

		template <typename T, typename... P> void Error(T t, P... p)
		{
			safe_print_mutex.lock();
			{
				std::cout << "[ ERROR ] : " << t << ' ';
				ErrorChild(p...);
			}
		}
	} // console.
} // util.
} // ax.
