#pragma once

#include "Attribute.hpp"

#include "rapidjson/document.h"
#include "rapidjson/reader.h"

#include <fstream>
#include <sstream>
#include <stack>

namespace ax {

/*
 * JsonWriter.
 */
std::string format_string(const std::string& str);

void JsonRecursiveWriter(
	std::stringstream& ss, const ax::Attribute& att, bool indent, int& level, bool is_last);

std::string JsonWriter(const ax::Attribute& att, bool indent);

/*
 * JsonReader.
 */
struct JsonHandler {
	inline JsonHandler()
		: _need_to_push_stack_obj(false)
	{
	}

	inline bool Null()
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nA "
						  "null was given as root.")
					  << std::endl;
			return false;
		}

		return true;
	}
	inline bool Bool(bool b)
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nA "
						  "bool was given as root.")
					  << std::endl;
			return false;
		}

		_attributes_stack.top()->Back().SetValue<bool>(b);
		return true;
	}
	inline bool Int(int i)
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nA "
						  "int was given as root.")
					  << std::endl;
			return false;
		}

		_attributes_stack.top()->Back().SetValue<int>((int)i);
		return true;
	}
	inline bool Uint(unsigned u)
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nA "
						  "unint was given as root.")
					  << std::endl;
			return false;
		}

		_attributes_stack.top()->Back().SetValue<unsigned int>(u);

		return true;
	}
	inline bool Int64(int64_t i)
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nA "
						  "int64 was given as root.")
					  << std::endl;
			return false;
		}

		_attributes_stack.top()->Back().SetValue<int>((int)i);
		return true;
	}
	inline bool Uint64(uint64_t u)
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nA "
						  "unint64 was given as root.")
					  << std::endl;
			return false;
		}

		_attributes_stack.top()->Back().SetValue<int>((int)u);
		return true;
	}
	inline bool Double(double d)
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nA "
						  "double was given as root.")
					  << std::endl;
			return false;
		}

		_attributes_stack.top()->Back().SetValue<double>(d);
		return true;
	}
	inline bool RawNumber(const char* str, rapidjson::SizeType length, bool copy)
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nA "
						  "raw number was given as root.")
					  << std::endl;
			return false;
		}

		return true;
	}

	inline bool String(const char* str, rapidjson::SizeType length, bool copy)
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nA "
						  "string was given as root.")
					  << std::endl;
			return false;
		}

		_attributes_stack.top()->Back().SetValue<std::string>(std::string(str, length));
		return true;
	}

	bool StartObject();

	bool Key(const char* str, rapidjson::SizeType length, bool copy);

	inline bool EndObject(rapidjson::SizeType memberCount)
	{
		_attributes_stack.pop();
		return true;
	}

	inline bool StartArray()
	{
		if (_attributes_stack.empty()) {
			std::cerr << ("tk::AttributeDocument only support json file starting with json objects.\nAn "
						  "array was given as root.")
					  << std::endl;
			return false;
		}

		_attributes_stack.top()->Back().SetType(Attribute::Type::ARRAY);
		return true;
	}

	inline bool EndArray(rapidjson::SizeType elementCount)
	{
		return true;
	}

	inline Attribute& GetMainAttribute()
	{
		return _main_attribute;
	}

private:
	Attribute _main_attribute;
	std::stack<Attribute*> _attributes_stack;
	bool _need_to_push_stack_obj;
};

/*
 * AttributeTree::Base.
 */
struct JsonReader {
	JsonReader();

	JsonReader(const std::string& file_path);

	JsonReader(const std::vector<char>& file_data);

	inline bool IsOpen() const
	{
		return _is_open;
	}

	inline bool IsValid() const
	{
		return _is_open && _is_valid;
	}

	inline int GetErrorCharOffset() const
	{
		return _error_char_offset;
	}

	inline std::pair<int, int> GetErrorLineCharOffset() const
	{
		return _error_line_char_offset;
	}

	JsonHandler handler;
	std::vector<char> data;
	bool _is_open = true;
	bool _is_valid = false;
	int _error_char_offset;
	std::pair<int, int> _error_line_char_offset;
};
}