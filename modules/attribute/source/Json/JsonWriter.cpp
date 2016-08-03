
#include "Json.hpp"
#include "Attribute.hpp"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace ax {

std::string format_string(const std::string& str)
{
	return "\"" + str + "\"";
}

void JsonRecursiveWriter(
	std::stringstream& ss, const ax::Attribute& att, bool indent, int& level, bool is_last)
{
	std::string tabs(level * 2, ' ');

	switch (att.GetType()) {
	case ax::Attribute::Type::OBJECT:
		if (att.GetName().empty()) {
			if (indent) {
				ss << tabs;
			}
			ss << "{";

			if (indent) {
				ss << "\n";
			}
		}
		else {
			if (indent) {
				ss << tabs;
			}

			ss << format_string(att.GetName()) << ": {";

			if (indent) {
				ss << "\n";
			}
		}
		break;
	case ax::Attribute::Type::ARRAY:
		if (indent) {
			ss << tabs;
		}

		ss << format_string(att.GetName()) << ": [";

		if (indent) {
			ss << "\n";
		}
		break;
	case ax::Attribute::Type::NUMBER:
	case ax::Attribute::Type::BOOLEAN:
	case ax::Attribute::Type::STRING:
		if (indent) {
			ss << tabs;
		}

		ss << format_string(att.GetName()) << ":" << format_string(att.GetValue<std::string>()); // << ",";

		if (!is_last) {
			ss << ",";
		}

		if (indent) {
			ss << "\n";
		}

		break;
	default:
		std::cerr << "Should never happend. (" << (int)att.GetType() << "( " << att.GetTypeString() << ")."
				  << std::endl;

		break;
	}

	level++;

	// Recursive call.
	for (int i = 0; i < att.GetAttributes().size(); i++) {
		JsonRecursiveWriter(ss, att[i], indent, level, i == (att.GetAttributes().size() - 1));
	}

	level--;

	switch (att.GetType()) {
	case ax::Attribute::Type::OBJECT:
		if (indent) {
			ss << tabs;
		}

		ss << "}";

		if (!is_last) {
			ss << ",";
		}

		if (indent) {
			ss << "\n";
		}

		break;
	case ax::Attribute::Type::ARRAY:
		if (indent) {
			ss << tabs;
		}
		ss << "]";

		if (indent) {
			ss << "\n";
		}
		break;
	case ax::Attribute::Type::NUMBER:

		break;
	case ax::Attribute::Type::BOOLEAN:

		break;
	case ax::Attribute::Type::STRING:

		break;

	default:
		std::cerr << "Should never happend. " << (int)att.GetType() << "( " << att.GetTypeString() << ")."
				  << std::endl;
		break;
	}
}

std::string JsonWriter(const ax::Attribute& att, bool indent)
{
	int level = 0;
	std::stringstream ss;

	ss << "{";

	for (int i = 0; i < att.GetAttributes().size(); i++) {
		JsonRecursiveWriter(ss, att[i], indent, level, i == (att.GetAttributes().size() - 1));
	}

	ss << "}";

	return ss.str();
}
}