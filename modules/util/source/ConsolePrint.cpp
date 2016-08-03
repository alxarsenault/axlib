#include "ConsolePrint.hpp"

namespace ax {
namespace util {
	namespace console {
		std::recursive_mutex safe_print_mutex;

		const std::string COLOR_STRING_ARRAY[] = {
			"\033[0m", // Reset.

			"\033[30m", // Black.
			"\033[31m", // Red.
			"\033[32m", // Green.
			"\033[33m", // Yellow.
			"\033[34m", // Blue.
			"\033[35m", // Magenta.
			"\033[36m", // Cyan.
			"\033[37m", // White.

			"\033[1m\033[30m", // Bold Black.
			"\033[1m\033[31m", // Bold Red.
			"\033[1m\033[32m", // Bold Green.
			"\033[1m\033[33m", // Bold Yellow.
			"\033[1m\033[34m", // Bold Blue.
			"\033[1m\033[35m", // Bold Magenta.
			"\033[1m\033[36m", // Bold Cyan.
			"\033[1m\033[37m" // Bold White.
		};

		std::ostream& operator<<(std::ostream& stream, const Color& color)
		{
			return stream << COLOR_STRING_ARRAY[static_cast<std::size_t>(color)];
		}

		void WriteChild()
		{
			safe_print_mutex.unlock();
		}

		void PrintChild()
		{
			std::cout << std::endl;
			safe_print_mutex.unlock();
		}

		void CPrintChild()
		{
			// Reset console color.
			std::cout << COLOR_STRING_ARRAY[0] << std::endl;
			safe_print_mutex.unlock();
		}

		void ErrorChild()
		{
			// Reset console color.
			std::cerr << COLOR_STRING_ARRAY[0] << std::endl;
			safe_print_mutex.unlock();
		}

	} // console.
} // util.
} // ax.