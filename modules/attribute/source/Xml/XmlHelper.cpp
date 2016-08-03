#include "XmlHelper.hpp"
#include <iostream>

namespace ax {

XmlHelper::XmlHelper(const std::string& path)
	: _file_path(path)
{
}

XmlHelper::XmlHelper()
{
	rapidxml::xml_node<>* decl = _xml_doc.allocate_node(rapidxml::node_declaration);
	decl->append_attribute(_xml_doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(_xml_doc.allocate_attribute("encoding", "utf-8"));
	_xml_doc.append_node(decl);
}

void XmlHelper::Save(const std::string& path)
{
	std::ofstream file_stored(path);

	file_stored << _xml_doc;
	file_stored.close();
	_xml_doc.clear();
}

std::string XmlHelper::GetString()
{
	std::stringstream str;
	str << _xml_doc;
	return str.str();
}

bool XmlHelper::Parse()
{
	// Read the xml file into a vector.
	std::ifstream menu_file_path(_file_path);

	_xml_buffer = std::vector<char>(
		(std::istreambuf_iterator<char>(menu_file_path)), std::istreambuf_iterator<char>());
	_xml_buffer.push_back('\0');

	try {
		_xml_doc.parse<0>(&_xml_buffer[0]);
	}
	catch (rapidxml::parse_error& e) {
		std::cerr << "Xml parsing " << e.what() << std::endl;
		return false;
	}

	return true;
}

bool XmlHelper::Parse(const std::string& content)
{
	_xml_buffer = std::vector<char>(content.begin(), content.end());
	_xml_buffer.push_back('\0');

	_xml_doc.clear();

	try {
		_xml_doc.parse<0>(&_xml_buffer[0]);
	}
	catch (rapidxml::parse_error& e) {
		std::cerr << "Xml parsing " << e.what() << std::endl;
		return false;
	}

	return true;
}

XmlHelper::Node XmlHelper::GetNode(const std::string& name)
{
	return XmlHelper::Node(_xml_doc.first_node(name.c_str()));
}

/*
 * Xml::Node.
 */
XmlHelper::Node::Node(rapidxml::xml_node<>* node)
	: _node(node)
{
}

XmlHelper::Node::Node(const Node& node)
	: _node(node._node)
{
}

XmlHelper::Node& XmlHelper::Node::operator=(const Node& node)
{
	_node = node._node;
	return *this;
}

XmlHelper::Node XmlHelper::Node::GetNode(const std::string& name)
{
	return _node->first_node(name.c_str());
}

std::string XmlHelper::Node::GetAttribute(const std::string& att_name)
{
	rapidxml::xml_attribute<>* att = _node->first_attribute(att_name.c_str());

	if (!att) {
		throw XmlHelper::Exception("Parsing attribute name : " + att_name + ".");
		return "";
	}

	return std::string(att->value(), att->value_size());
}

std::string XmlHelper::Node::GetValue()
{
	return std::string(_node->value(), _node->value_size());
}

std::string XmlHelper::Node::GetChildNodeValue(const std::string& name)
{
	rapidxml::xml_node<>* node = _node->first_node(name.c_str());

	if (!node) {
		throw XmlHelper::Exception("Parsing node name : " + name + ".");
		return "";
	}
	return std::string(node->value(), node->value_size());
}

std::vector<std::pair<std::string, std::string>> XmlHelper::Node::GetAtributes()
{
	std::vector<std::pair<std::string, std::string>> atts;

	rapidxml::xml_attribute<>* att = _node->first_attribute();

	if (!att) {
		throw XmlHelper::Exception("Reading attributes");
		return atts;
	}

	while (att) {
		atts.push_back(std::pair<std::string, std::string>(
			std::string(att->name(), att->name_size()), std::string(att->value(), att->value_size())));

		att = att->next_attribute();
	}

	return atts;
}

bool XmlHelper::Node::IsValid() const
{
	return _node != nullptr;
}

XmlHelper::Node XmlHelper::Node::GetNextSibling()
{
	return XmlHelper::Node(_node->next_sibling());
}

XmlHelper::Node XmlHelper::Node::GetFirstNode()
{
	return XmlHelper::Node(_node->first_node());
}

std::string XmlHelper::Node::GetName()
{
	return std::string(_node->name(), _node->name_size());
}

XmlHelper::Node XmlHelper::CreateNode(const std::string& name)
{
	char* nn = _xml_doc.allocate_string(name.c_str());
	return Node(_xml_doc.allocate_node(rapidxml::node_element, nn));
}

void XmlHelper::AddMainNode(XmlHelper::Node& node)
{
	_xml_doc.append_node(node.GetNodeHandle());
}

XmlHelper::Node XmlHelper::CreateNode(const std::string& name, const std::string& value)
{
	char* nn = _xml_doc.allocate_string(name.c_str());
	char* vv = _xml_doc.allocate_string(value.c_str());
	return Node(_xml_doc.allocate_node(rapidxml::node_element, nn, vv));
}
}