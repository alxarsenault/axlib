#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <deque>
#include <iostream>
#include <assert.h>

namespace ax {
/// @defgroup attribute
/// @{

/**
 * @brief Uniform interface to access different attribute value types.
 * @details Those types are listed in Attribute::Type. Attribute's value are all stored with a std::string and
 *          can be converted to desired C++ type using GetValue() template function.
 *
 *          - Some attribute don't have value (\b NONE, \b ARRAY and \b OBJECT).
 *          - Some Attribute::Type can only be cast in specific C++ type.
 *          - Some attributes (\b ARRAY, \b OBJECT) can have one or multiple child attributes.
 *          - Only data Attribute::Type (\b BOOLEAN, \b NUMBER and \b STRING) contain a value.
 *          - All data Attribute::Type and \b ARRAY are always named.
 *          - \b OBJECT attributes can be named or not.
 *          - \b NONE attributes are never named and represents an invalid attribute.
 */
class Attribute {
public:
	/**
	 * @brief List of attribute types.
	 */
	enum class Type { NONE, ARRAY, BOOLEAN, NUMBER, STRING, OBJECT };

	/**
	 * @brief Create an empty OBJECT attribute.
	 */
	inline Attribute()
		: _type(Type::OBJECT)
	{
	}

	/**
	 * @brief Move constructor.
	 * @param att Attribute to move.
	 */
	inline Attribute(Attribute&& att)
		: _type(std::move(att._type))
		, _name(std::move(att._name))
		, _value(std::move(att._value))
		, _attributes(std::move(att._attributes))
	{
	}

	/**
	 * @brief Copy constructor.
	 * @param att Attribute to copy.
	 */
	inline Attribute(const Attribute& att)
		: _type(att._type)
		, _name(att._name)
		, _value(att._value)
		, _attributes(att._attributes)
	{
	}

	/**
	 * @brief Attribute::Type constructor.
	 * @details This will create an attribute of given type without any value, name or children.
	 * @param type Attribute::Type to create.
	 */
	inline Attribute(Type type)
		: _type(type)
	{
	}

	/**
	 * @brief Named \b OBJECT attribute constructor.
	 * @details This will create an \b OBJECT attribute with the given name.
	 * @param name Attribute name.
	 */
	inline Attribute(const std::string& name)
		: _type(Type::OBJECT)
		, _name(name)
	{
	}

	/**
	 * @brief Named attribute constructor.
	 * @details This will create an attribute with the given type and name.
	 * @param name Attribute name.
	 * @param type Attribute type.
	 */
	inline Attribute(const std::string& name, Type type)
		: _type(type)
		, _name(name)
	{
	}

	/**
	 * @brief Named attribute with value constructor.
	 * @details This will create an attribute with the given type, name and value.
	 * @param name Attribute name.
	 * @param value Attribute value in string format.
	 * @param type Attribute type.
	 * @warning No validation of value or type validity are made. This might lead to a cast error when using
	 *          GetValue<TYPE>(...) function if improper value string is given. Consider using Create<TYPE>()
	 *          function instead.
	 */
	inline Attribute(const std::string& name, const std::string& value, Type type)
		: _type(type)
		, _name(name)
		, _value(value)
	{
	}

	/**
	 * @brief Move assignement operator.
	 * @param att Attribute to be asssigned.
	 */
	inline void operator=(Attribute&& att)
	{
		_type = att._type;
		_name = att._name;
		_value = att._value;
		_attributes = att._attributes;
	}

	/**
	 * @brief Assignement operator.
	 * @param att Attribute to be asssigned.
	 */
	inline void operator=(Attribute& att)
	{
		_type = att._type;
		_name = att._name;
		_value = att._value;
		_attributes = att._attributes;
	}

	/**
	 * @brief Create an attribute with the given name and value.
	 * @details Create an attribute with the given name and value. Attribute::Type will automatically be
	 *          deduce from template type.
	 *
	 *          Here's the current C++ type conversion :
	 *          - \b BOOLEAN : bool.
	 *          - \b NUMBER  : int, unsigned int, short, unsigned short, long, unsigned long, float, double.
	 *          - \b STRING  : std::string.
	 *
	 *          Any type not listed above will create a NONE attribute and output a warning message.
	 * @tparam T C++ type of attribute value.
	 * @param name Attribute name
	 * @param value Attribute value.
	 * @return Created attribute with given name and value.
	 */
	template <typename T> static Attribute Create(const std::string& name, const T& value)
	{
		/// @todo Have this done statically.
		std::cerr << "Create<> :: Type (" << typeid(T).name() << ") is not define as attribute." << std::endl;
		return Attribute(Attribute::Type::NONE);
	}

	/**
	 * @brief Get attribute value.
	 * @details Get attribute value of the given C++ template type. If type differ from the ones listed in
	 *          Attribute::Create documentation, the function will return an empty object of the given type
	 *          and output a warning message. Compilation error will occur if the unlisted template type
	 *          doesn't have a default constructor.
	 * @tparam T C++ type of attribute value.
	 * @return Attribute value of given type.
	 * @throw std::invalid_argument If no conversion could be performed.
	 * @throw std::out_of_range If the converted value would fall out of the range of the result type.
	 * @warning No validation of value or type validity are made. This might lead to a cast error and an
	 *          exception might be thrown.
	 */
	template <typename T> T GetValue() const
	{
		/// @todo Have this done statically.
		std::cerr << "Create<> :: Type (" << typeid(T).name() << ") is not define as attribute." << std::endl;
		return T();
	}

	/**
	 * @brief Get the value of child attribute with given name if it exist or return the default value if not.
	 * @details This function is the equivalent of using (but a bit faster)
	 *          \code
	 *          if(att.Has("att_name") {
	 *          	return att["att_name"].GetValue<T>();
	 *          }
	 *          return default_value;
	 *          \endcode
	 * @param name Attribute name.
	 * @param default_value Default value to be returned is attribute doesn't exist.
	 * @return The attribute value or default value.
	 * @throw std::invalid_argument If no conversion could be performed.
	 * @throw std::out_of_range If the converted value would fall out of the range of the result type.
	 * @warning If attribute exist, no validation of value or type validity are made. This might lead to a
	 *          cast error and an exception might be thrown.
	 */
	template <typename T>
	inline T GetAttributeDefaultValue(const std::string& name, const T& default_value) const
	{
		for (auto& n : _attributes) {
			if (n.GetName() == name) {
				return n.GetValue<T>();
			}
		}

		return default_value;
	}

	/**
	 * @brief Set attribute value.
	 * @details This will set attribute value and Attribute::Type  accordingly. A warning message will be
	 *          output if C++ data type is not listed in Attribute::Create documentation.
	 * @tparam T C++ value type.
	 * @param value Attribute value.
	 * @warning Wrong usage of the function on certain attribute types might lead to invalid attribute tree
	 *          generation. By example, using this on an ARRAY type will cause invalid output.
	 */
	template <typename T> void SetValue(const T& value)
	{
		/// @todo Have this done statically.
		std::cerr << "Attribute::SetValue<> :: Type (" << typeid(T).name() << ") is not define as attribute."
				  << std::endl;
	}

	/**
	 * @brief Get attribute type.
	 * @return Attribute type.
	 */
	inline Type GetType() const
	{
		return _type;
	}

	/**
	 * @brief Set attribute type.
	 * @param Attribute type.
	 * @warning Setting an incorrect type to attribute already containing value might lead to invalid
	 *          attribute tree generation. No check is made.
	 */
	void SetType(Type type)
	{
		_type = type;
	}

	/**
	 * @brief Get attribute type as string.
	 * @return String name of attribute.
	 */
	inline std::string GetTypeString() const;

	/**
	 * @brief Get attribute name.
	 * @return Attribute name or empty string if attribute doesn't have one.
	 */
	inline const std::string& GetName() const
	{
		return _name;
	}

	/**
	 * @brief Set attribute name.
	 * @param name Attribute name.
	 * @warning Setting a name uncorrect attribute type might lead to undefined behavior. No check is made.
	 */
	inline void SetName(const std::string& name)
	{
		_name = name;
	}

	/**
	 * @brief Add a child attribute to parent's attribute children list.
	 * @param att Child attribute.
	 * @warning This can definitely lead to invalid attribute tree generation. No check is made.
	 *          By example, adding a child to a value type attribute will to undefined behavior.
	 */
	void Add(Attribute&& att);

	/**
	 * @brief Add a child attribute at the beginning of parent's attribute children list.
	 * @param att Child attribute.
	 * @warning This can definitely lead to invalid attribute tree generation. No check is made.
	 *          By example, adding a child to a value type attribute will to undefined behavior.
	 */
	void AddFront(Attribute&& att);

	/**
	 * @brief Get a list of children attributes.
	 * @return Vector of children attributes. Returns an empty vector if attribute has no child.
	 */
	inline std::vector<Attribute>& GetAttributes()
	{
		return _attributes;
	}

	/**
	 * @brief Get a list of children attributes.
	 * @return Vector of children attributes. Returns an empty vector if attribute has no child.
	 */
	inline const std::vector<Attribute>& GetAttributes() const
	{
		return _attributes;
	}

	/**
	 * @brief Get the first attribute with the given name.
	 * @return The first attribute with the given name. If no attribute is found, it returns a reference
	 *         on Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function. If invalid, the returned variable shall not be modified.
	 */
	inline Attribute& operator[](const std::string& name);

	/**
	 * @brief Get the first attribute with the given name.
	 * @return The first attribute with the given name. If no attribute is found, it returns a reference
	 *         on Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function.
	 */
	inline const Attribute& operator[](const std::string& name) const;

	/// Get attribute by index.
	/// @return Attribute of type NONE if index is out of bounds.

	/**
	 * @brief Get attribute by index.
	 * @details This function is usefull when dealing with ARRAY attribute. Use
	 *          Attribute::GetAttributes().size() to obtain the number of children.
	 * @param index Index of attribute.
	 * @return The attribute at given index. If index is out of bounds, it returns a reference on
	 *         Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function. If invalid, the returned variable shall not be modified.
	 */
	inline Attribute& operator[](const std::size_t& index);

	/**
	 * @brief Get attribute by index.
	 * @details This function is usefull when dealing with ARRAY attribute. Use
	 *          Attribute::GetAttributes().size() to obtain the number of children.
	 * @param index Index of attribute.
	 * @return The attribute at given index. If index is out of bounds, it returns a reference on
	 *         Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function.
	 */
	inline const Attribute& operator[](const std::size_t& index) const;

	/// Check if object contain attribute name.

	/**
	 * @brief Verify if attribute has a child with given name.
	 * @param name Attribute name to look for.
	 * @return True if attribute has child attribute with given name, false otherwise.
	 */
	inline bool Has(const std::string& name) const;

	/**
	 * @brief Verify if attribute has all children with given names.
	 * @param names Vector of attribute names to look for.
	 * @return True if attribute has all of the given names as children, false otherwise.
	 */
	inline bool Has(const std::vector<std::string>& names) const;

	/**
	 * @brief Get a reference of last child attribute.
	 * @return Reference of last child attribute. If attribute has no child, it returns a reference on
	 *         Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function. If invalid, the returned variable shall not be modified.
	 */
	inline Attribute& Back();

	/**
	 * @brief Get a const reference of last child attribute.
	 * @return Reference of last child attribute. If attribute has no child, it returns a reference on
	 *         Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function.
	 */
	inline const Attribute& Back() const;

	/**
	 * @brief Get a reference of first child attribute.
	 * @return Reference of first child attribute. If attribute has no child, it returns a reference on
	 *         Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function. If invalid, the returned variable shall not be modified.
	 */
	inline Attribute& Front();

	/**
	 * @brief Get a const reference of first child attribute.
	 * @return Reference of first child attribute. If attribute has no child, it returns a reference on
	 *         Attribute::End() with type Attribute::Type::NONE. This can be verify by using
	 *         Attribute::IsValid() function.
	 */
	inline const Attribute& Front() const;

	/**
	 * @brief Print raw attribute tree structure to stdout.
	 */
	void Print();

	/**
	 * @brief Visit current attribute and all chilrden.
	 * @param visitor_fct Function to be executed on every attributes.
	 */
	void Visit(std::function<void(Attribute&)> visitor_fct);

	/**
	 * @brief Visit current attribute and all chilrden.
	 * @details The begin function will be executed when passing on the current attribute for the first time,
	 *          and end function will be executed after visiting all of the current attribute's children.
	 * @param visitor_begin Function to be executed at the beginning of every attributes.
	 * @param visitor_end Function to be executed at the end of every attributes.
	 */
	void Visit(std::function<void(Attribute&)> visitor_begin, std::function<void(Attribute&)> visitor_end);

	/**
	 * @brief Attribute retuned when trying to access an unexisting or invalid attribute.
	 * @return Empty attribute.
	 */
	static inline Attribute& End()
	{
		return _end;
	}

	/**
	 * @brief Check if attribute has a valid type..
	 * @return True if attribute as a valid type, false if not.
	 */
	inline bool IsValid() const
	{
		return _type != Type::NONE;
	}

private:
	Type _type; /// Attribute type.
	std::string _name; /// Attribute name.
	std::string _value; /// Attribute value.
	std::vector<Attribute> _attributes; /// Vector of attribute children.

	static Attribute _end; /// Returned attribute when trying to access an unexisting or invalid attribute.

	/**
	 * @brief Use by Print() function to output raw attribute tree structure to stdout recursively.
	 * @param attribute Attribute to start from.
	 * @param level Depth of current attribute. Used to have the right indentation level.
	 */
	void PrintRecursive(Attribute& attribute, int& level);
};

//------------------------------------------------------------------------------------------------------------
// Inline implementations of Attribute.
//------------------------------------------------------------------------------------------------------------

std::string Attribute::GetTypeString() const
{
	switch (_type) {
	case Type::NONE:
		return "NONE";

	case Type::ARRAY:
		return "ARRAY";

	case Type::BOOLEAN:
		return "BOOLEAN";

	case Type::NUMBER:
		return "NUMBER";

	case Type::STRING:
		return "STRING";

	case Type::OBJECT:
		return "OBJECT";
	}
}

Attribute& Attribute::operator[](const std::string& name)
{
	for (auto& n : _attributes) {
		if (n.GetName() == name) {
			return n;
		}
	}

	return _end;
}

const Attribute& Attribute::operator[](const std::string& name) const
{
	for (auto& n : _attributes) {
		if (n.GetName() == name) {
			return n;
		}
	}

	return _end;
}

Attribute& Attribute::operator[](const std::size_t& index)
{
	if (index < _attributes.size()) {
		return _attributes[index];
	}

	return _end;
}

const Attribute& Attribute::operator[](const std::size_t& index) const
{
	if (index < _attributes.size()) {
		return _attributes[index];
	}

	return _end;
}

bool Attribute::Has(const std::string& name) const
{
	for (auto& n : _attributes) {
		if (n.GetName() == name) {
			return true;
		}
	}

	return false;
}

bool Attribute::Has(const std::vector<std::string>& names) const
{
	/// @todo Do this better.
	for (auto& n : names) {
		if (!Has(n)) {
			return false;
		}

		return true;
	}

	return false;
}

Attribute& Attribute::Back()
{
	if (_attributes.empty()) {
		return End();
	}

	return _attributes.back();
}

Attribute& Attribute::Front()
{
	if (_attributes.empty()) {
		return End();
	}

	return _attributes[0];
}

const Attribute& Attribute::Back() const
{
	if (_attributes.empty()) {
		return End();
	}

	return _attributes.back();
}

const Attribute& Attribute::Front() const
{
	if (_attributes.empty()) {
		return End();
	}

	return _attributes[0];
}

//------------------------------------------------------------------------------------------------------------
// Template specialization.
//------------------------------------------------------------------------------------------------------------

// Attribute::Create.

template <> Attribute Attribute::Create<int>(const std::string& name, const int& value);

template <> Attribute Attribute::Create<double>(const std::string& name, const double& value);

template <> Attribute Attribute::Create<std::string>(const std::string& name, const std::string& value);

// Attribute::SetValue.

template <> void Attribute::SetValue<bool>(const bool& value);

template <> void Attribute::SetValue<int>(const int& value);

template <> void Attribute::SetValue<unsigned int>(const unsigned int& value);

template <> void Attribute::SetValue<double>(const double& value);

template <> void Attribute::SetValue<std::string>(const std::string& value);

// Attribute::GetValue.

template <> bool Attribute::GetValue<bool>() const;

template <> float Attribute::GetValue<float>() const;

template <> double Attribute::GetValue<double>() const;

template <> int Attribute::GetValue<int>() const;

template <> unsigned int Attribute::GetValue<unsigned int>() const;

template <> std::string Attribute::GetValue<std::string>() const;

/// @}
} // ax.