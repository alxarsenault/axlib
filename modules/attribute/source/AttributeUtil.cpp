#include "AttributeUtil.hpp"
#include <algorithm>

namespace ax {
namespace util {
	std::pair<int, int> GetLineAndCharIndexFromCharIndex(const std::vector<char>& data, unsigned int c_index)
	{
		std::pair<int, int> position(-1, -1);

		const int line_index = std::count(data.begin(), data.begin() + c_index, '\n');

		std::vector<char>::const_reverse_iterator it
			= std::find_if(data.rend() - c_index, data.rend(), [](const char& c) { return c == '\n'; });

		if (it != data.rend()) {
			return std::pair<int, int>(line_index, c_index - std::distance(it, data.rend()));
		}

		return std::pair<int, int>(line_index, c_index);
	}
}
}