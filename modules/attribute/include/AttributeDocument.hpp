#pragma once

#include <string>
#include <vector>

#include "Attribute.hpp"

namespace ax {
/// @defgroup attribute
/// @{

/**
 * @brief Create or export attribute tree from (or to) JSON or XML file.
 * @details	This class creates an attribute tree based mostly on JSON data types. All data types are defined
 *          in Attribute.hh as Attribute::Type. These types can then be cast in an actual C++ type using
 *          Attribute::GetValue() template functions.
 */
class AttributeDocument {
public:
	/**
	 * @brief List of supported types for creating or exporting attribute tree.
	 */
	enum class Type { JSON, XML };

	/**
	 * @brief List of possible error types while opening attribute document.
	 */
	enum class Error { NONE, INVALID_PATH, SYNTAX_ERROR };

	/**
	 * @brief Create empty document with Attribute::Type::OBJECT as root.
	 * @details	This constructor is used to create an attribute tree from scratch (without using an existing
	 *          file).
	 * @warning Only Attribute::Type::OBJECT are currently supported as root node.
	 */
	AttributeDocument()
		: _root_attribute(Attribute::Type::OBJECT)
		, _is_open(true)
		, _is_valid(true)
		, _error_char_offset(-1)
		, _error_line_char_offset(-1, -1)
	{
	}

	/**
	 * @brief Create attribute tree using file path.
	 * @details This constructor will never throw exeptions. You can check document validity by using
	 *          IsValid() or GetErrorType() functions. If IsValid() returns false then error type will be
	 *          different from AttributeDocument::Error::NONE, the given file as then either an incorrect
	 *          syntax or an invalid path. In that case, no more functions shall be call and will lead to
	 *          undefined behaviors.
	 * @param file_path Path of the attribute file to parse.
	 * @param type Type of file to parse from AttributeDocument::Type.
	 */
	AttributeDocument(const std::string& file_path, Type type);

	/**
	 * @brief Create attribute tree using a raw char vector.
	 * @details This constructor will never throw exeptions. You can check document validity by using
	 *          IsValid() or GetErrorType() functions. If IsValid() returns false then error type will be
	 *          different from AttributeDocument::Error::NONE, the given file as an incorrect syntax. In that
	 *          case, no more functions shall be call and will lead to undefined behaviors.
	 * @warning The data vector must end with a '\n' character, if not, this might lead to an invalid syntax
	 *          error.
	 * @param file_data Data of the attribute to parse.
	 * @param type Type of file to parse from AttributeDocument::Type.
	 */
	AttributeDocument(const std::vector<char>& file_data, Type type);

	/**
	 * @brief Get a reference of root attribute.
	 * @details For now, the root attribute can only be an Attribute::Type::OBJECT and attribute name should
	 *          be empty. This can be verify by using Attribute::GetType() and Attribute::GetName().
	 * @return Reference of root attribute.
	 */
	inline Attribute& GetRootAttribute()
	{
		return _root_attribute;
	}

	/**
	 * @brief Get a const reference of root attribute.
	 * @details For now, the root attribute can only be an Attribute::Type::OBJECT and attribute name should
	 *          be empty. This can be verify by using Attribute::GetType() and Attribute::GetName().
	 * @return Const reference of root attribute.
	 */
	inline const Attribute& GetRootAttribute() const
	{
		return _root_attribute;
	}

	/**
	 * @brief Verify if current document was opened correcly.
	 * @details A false value can only be optain when an invalid file path was given to the constructor. This
	 *          will also force the document to become invalid.
	 * @return True when document was open correcly, false if not.
	 */
	inline bool IsOpen() const
	{
		return _is_open;
	}

	/**
	 * @brief Verify if current document has a valid syntax.
	 * @details A false value can be optain when IsOpen() returns false or if syntax is incorrect.
	 * @return True when document has a valid syntax, false if not.
	 */
	inline bool IsValid() const
	{
		return _is_valid;
	}

	/**
	 * @brief Get the character absolute index of the first syntax error found in document.
	 * @details If document wasn't opened correcly or if document has no syntax error, the index will be -1.
	 * @return The character absolute index in file of the first syntax error.
	 */
	inline int GetErrorCharOffset() const
	{
		return _error_char_offset;
	}

	/**
	 * @brief Get the line and character index of the first syntax error found in document.
	 * @details If document wasn't opened correcly or if document has no syntax error, the indexes will be
	 *          (-1, -1).
	 * @return The line and character index of the first syntax error (first = line, second = char).
	 */
	inline std::pair<int, int> GetErrorLineCharOffset() const
	{
		return _error_line_char_offset;
	}

	/**
	 * @brief Get the current error type.
	 * @return The current error type.
	 */
	inline Error GetErrorType() const
	{
		return _error_type;
	}

	/**
	 * @brief Get the current attribute document as a formatted std::string according the given type format.
	 * @param type Type of document to format with.
	 * @return The formatted string.
	 * @warning The returned string is not guaranteed to be valid if improper modifications were made.
	 */
	std::string ToString(Type type) const;

	/**
	 * @brief Save the current attribute document as a formatted file.
	 * @details Save the current attribute document as a formatted file according the given type format.
	 * @param file_path Path of the output file.
	 * @param type Type of the ouput document format.
	 * @return True is file was succefully saved, false if not.
	 */
	bool Save(const std::string file_path, Type type);

	/**
	 * @brief Obtain a reference of the first root child attribute with the given name.
	 * @details Obtain a reference of the first root child attribute with the given name.
	 * @param name Name of the wanted attribute.
	 * @return The first root child attribute with the given name. If attribute is not found, it returns a
	 *         reference on Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function. If invalid, the returned variable shall not be modified.
	 *
	 * @todo Modify this to return an attribute iterator.
	 */
	Attribute& operator[](const std::string& name)
	{
		for (auto& n : _root_attribute.GetAttributes()) {
			if (n.GetName() == name) {
				return n;
			}
		}

		return Attribute::End();
	}

	/**
	 * @brief Obtain a reference of the first root child attribute with the given name.
	 * @details Obtain a reference of the first root child attribute with the given name.
	 * @param name Name of the wanted attribute.
	 * @return The first root child attribute with the given name. If attribute is not found, it returns a
	 *         reference on Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function.
	 *
	 * @todo Modify this to return an attribute iterator.
	 */
	const Attribute& operator[](const std::string& name) const
	{
		for (auto& n : _root_attribute.GetAttributes()) {
			if (n.GetName() == name) {
				return n;
			}
		}

		return Attribute::End();
	}

private:
	Attribute _root_attribute;
	bool _is_open;
	bool _is_valid;
	int _error_char_offset;
	std::pair<int, int> _error_line_char_offset;
	Error _error_type = Error::NONE;
};
/// @}
} // ax.