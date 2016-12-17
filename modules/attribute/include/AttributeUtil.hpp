#pragma once

#include <vector>
#include <string>

namespace ax {
namespace util {
	std::pair<int, int> GetLineAndCharIndexFromCharIndex(const std::vector<char>& data, unsigned int c_index);
	std::pair<int, int> GetLineAndCharIndexFromCharIndex(const std::string& data, unsigned int c_index);
}
}