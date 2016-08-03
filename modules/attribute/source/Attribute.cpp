#include "Attribute.hpp"

namespace ax {
Attribute Attribute::_end = Attribute(Type::NONE);

template <> Attribute Attribute::Create<int>(const std::string& name, const int& value)
{
	Attribute att;
	att._name = name;
	att._value = std::to_string(value);
	att._type = Type::NUMBER;
	return std::move(att);
}

template <> Attribute Attribute::Create<double>(const std::string& name, const double& value)
{
	return std::move(Attribute(name, std::to_string(value), Type::NUMBER));
}

template <> Attribute Attribute::Create<std::string>(const std::string& name, const std::string& value)
{
	return std::move(Attribute(name, value, Type::STRING));
}

template <> void Attribute::SetValue<bool>(const bool& value)
{
	_value = value ? "true" : "false";
	_type = Type::BOOLEAN;
}

template <> void Attribute::SetValue<int>(const int& value)
{
	_value = std::to_string(value);
	_type = Type::NUMBER;
}

template <> void Attribute::SetValue<unsigned int>(const unsigned int& value)
{
	_value = std::to_string(value);
	_type = Type::NUMBER;
}

template <> void Attribute::SetValue<double>(const double& value)
{
	_value = std::to_string(value);
	_type = Type::NUMBER;
}

template <> void Attribute::SetValue<std::string>(const std::string& value)
{
	_value = value;
	_type = Type::STRING;
}

template <> bool Attribute::GetValue<bool>() const
{
	return _value == "true" ? true : false;
}

template <> float Attribute::GetValue<float>() const
{
	return std::stof(_value);
}

template <> double Attribute::GetValue<double>() const
{
	return std::stod(_value);
}

template <> int Attribute::GetValue<int>() const
{
	return std::stoi(_value);
}

template <> unsigned int Attribute::GetValue<unsigned int>() const
{
	return (unsigned int)std::stoi(_value);
}

template <> std::string Attribute::GetValue<std::string>() const
{
	return _value;
}

void Attribute::Add(Attribute&& att)
{
	_attributes.emplace_back(att);
}

void Attribute::AddFront(Attribute&& att)
{
	_attributes.insert(_attributes.begin(), std::move(att));
}

void Attribute::Print()
{
	std::cout << GetName() << " : " << GetValue<std::string>() << std::endl;

	int level = 0;

	for (auto& att : GetAttributes()) {
		PrintRecursive(att, level);
	}
}

void Attribute::Visit(std::function<void(Attribute&)> visitor_fct)
{
	visitor_fct(*this);

	for (auto& att : GetAttributes()) {
		att.Visit(visitor_fct);
	}
}

void Attribute::Visit(
	std::function<void(Attribute&)> visitor_begin, std::function<void(Attribute&)> visitor_end)
{
	visitor_begin(*this);

	for (auto& att : GetAttributes()) {
		att.Visit(visitor_begin, visitor_end);
	}

	visitor_end(*this);
}

void Attribute::PrintRecursive(Attribute& attribute, int& level)
{
	std::string tabs(level * 2, '-');
	std::cout << tabs << " " << attribute.GetName() << " : " << attribute.GetValue<std::string>()
			  << std::endl;

	level++;

	for (auto& att : attribute.GetAttributes()) {
		PrintRecursive(att, level);
	}
	level--;
}
}