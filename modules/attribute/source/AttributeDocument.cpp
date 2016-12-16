#include "AttributeDocument.hpp"

#include <fstream>
#include <iostream>
#include <stack>
#include <memory>
#include <algorithm>

#include "Json.hpp"
#include "AttributeXml.hpp"

namespace ax {

AttributeDocument::AttributeDocument(const std::string& file_path, Type type)
{
	JsonReader reader(file_path);
	_root_attribute = std::move(reader.handler.GetMainAttribute());
	_is_open = reader.IsOpen();
	_is_valid = reader.IsValid();
	_error_char_offset = reader.GetErrorCharOffset();
	_error_line_char_offset = reader.GetErrorLineCharOffset();

	if (!_is_open) {
		_error_type = Error::INVALID_PATH;
	}

	if (!_is_valid) {
		_error_type = Error::SYNTAX_ERROR;
	}
}

AttributeDocument::AttributeDocument(const std::vector<char>& file_data, Type type)
{
	JsonReader reader(file_data);
	_root_attribute = std::move(reader.handler.GetMainAttribute());
	_is_open = reader.IsOpen();
	_is_valid = reader.IsValid();
	_error_char_offset = reader.GetErrorCharOffset();
	_error_line_char_offset = reader.GetErrorLineCharOffset();

	if (!_is_open) {
		_error_type = Error::INVALID_PATH;
	}

	if (!_is_valid) {
		_error_type = Error::SYNTAX_ERROR;
	}
}

std::string AttributeDocument::ToString(Type type) const
{
	if (type == Type::JSON) {
		return JsonWriter(GetRootAttribute(), true);
	}
	else if (type == Type::XML) {
		return XmlWriter(GetRootAttribute(), false);
	}

	return "";
}

bool AttributeDocument::Save(const std::string file_path, Type type)
{
	std::ofstream output_file(file_path);

	if (output_file.is_open()) {
		output_file << ToString(type);
		output_file.close();
	}
	return false;
}
}