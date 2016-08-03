#pragma once

#include <vector>

namespace ax {
namespace util {
	std::pair<int, int> GetLineAndCharIndexFromCharIndex(const std::vector<char>& data, unsigned int c_index);
}
}