#include "Json.hpp"
#include "Attribute.hpp"
#include "AttributeUtil.hpp"

#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

namespace ax {
/*
 * JsonHandler.
 */
bool JsonHandler::StartObject()
{
	if (_attributes_stack.empty()) {
		_attributes_stack.push(&_main_attribute);
		return true;
	}
	else if (_attributes_stack.top()->Back().GetType() == Attribute::Type::ARRAY) {
		_attributes_stack.top()->Back().Add(Attribute());
		_attributes_stack.push(&_attributes_stack.top()->Back().Back());
		return true;
	}

	_need_to_push_stack_obj = true;

	return true;
}

bool JsonHandler::Key(const char* str, rapidjson::SizeType length, bool copy)
{
	if (_need_to_push_stack_obj) {
		_attributes_stack.top()->Back().Add(Attribute(std::string(str, length)));
		_attributes_stack.push(&_attributes_stack.top()->Back());
		_need_to_push_stack_obj = false;
		return true;
	}

	_attributes_stack.top()->Add(Attribute(std::string(str, length)));

	return true;
}

/*
 * JsonReader.
 */
JsonReader::JsonReader()
	: _error_char_offset(-1)
	, _error_line_char_offset(-1, -1)
{
}

JsonReader::JsonReader(const std::string& file_path)
	: _error_char_offset(-1)
	, _error_line_char_offset(-1, -1)
{
	std::ifstream file_stream(file_path, std::ios::binary);

	// Return if not opened.
	if (!file_stream.is_open()) {
		_is_open = false;
		return;
	}

	// Get file size.
	file_stream.seekg(0, std::ios_base::end);
	const std::size_t file_size = file_stream.tellg();

	std::vector<char> data;
	data.reserve(file_size + 1);

	// Go back to beginning.
	file_stream.seekg(0, std::ios_base::beg);

	// Copy file content to vector.
	data.assign(std::istreambuf_iterator<char>(file_stream), std::istreambuf_iterator<char>());
	data.push_back('\n');
	data.push_back('\n');

	rapidjson::StringStream stream = rapidjson::StringStream(data.data());

	rapidjson::Reader reader;
	rapidjson::ParseResult result = reader.Parse(stream, handler);

	_is_valid = !result.IsError();

	if (!_is_valid) {
		_error_char_offset = result.Offset();
		_error_line_char_offset = util::GetLineAndCharIndexFromCharIndex(data, _error_char_offset);
	}
}

JsonReader::JsonReader(const std::vector<char>& file_data)
	: data(file_data)
{
	rapidjson::StringStream stream = rapidjson::StringStream(data.data());

	rapidjson::Reader reader;
	rapidjson::ParseResult result = reader.Parse(stream, handler);

	_is_valid = !result.IsError();

	if (!_is_valid) {
		_error_char_offset = result.Offset();
		_error_line_char_offset = util::GetLineAndCharIndexFromCharIndex(data, _error_char_offset);
	}
}
}