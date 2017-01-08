#include "Xml.hpp"
#include <iostream>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

namespace ax {

Xml::Xml(const std::string& path)
	: _file_path(path)
{
	_xml_doc = std::make_shared<rapidxml::xml_document<>>();
}

Xml::Xml()
{
	_xml_doc = std::make_shared<rapidxml::xml_document<>>();
	rapidxml::xml_node<>* decl = _xml_doc->allocate_node(rapidxml::node_declaration);
	decl->append_attribute(_xml_doc->allocate_attribute("version", "1.0"));
	decl->append_attribute(_xml_doc->allocate_attribute("encoding", "utf-8"));
	_xml_doc->append_node(decl);
}

void Xml::Save(const std::string& path)
{
	std::ofstream file_stored(path);
	file_stored << *(_xml_doc.get());
	file_stored.close();
	_xml_doc->clear();
}

std::string Xml::GetString()
{
	std::stringstream str;
	str << *(_xml_doc.get());
	return str.str();
}

bool Xml::Parse()
{
	// Read the xml file into a vector.
	std::ifstream menu_file_path(_file_path);

	_xml_buffer = std::vector<char>(
		(std::istreambuf_iterator<char>(menu_file_path)), std::istreambuf_iterator<char>());
	_xml_buffer.push_back('\0');

	try {
		_xml_doc->parse<0>(&_xml_buffer[0]);
	}
	catch (rapidxml::parse_error& e) {
		std::cerr << "Xml parsing " << e.what() << std::endl;
		return false;
	}

	return true;
}

bool Xml::Parse(const std::string& content)
{
	_xml_buffer = std::vector<char>(content.begin(), content.end());
	_xml_buffer.push_back('\0');

	_xml_doc->clear();

	try {
		_xml_doc->parse<0>(&_xml_buffer[0]);
	}
	catch (rapidxml::parse_error& e) {
		std::cerr << "Xml parsing " << e.what() << std::endl;
		return false;
	}

	return true;
}

Xml::Node Xml::GetNode(const std::string& name)
{
	return Xml::Node(_xml_doc->first_node(name.c_str()));
}

/*
 * Xml::Node.
 */
Xml::Node::Node(rapidxml::xml_node<>* node)
	: _node(node)
{
}

Xml::Node::Node(const Node& node)
	: _node(node._node)
{
}

Xml::Node& Xml::Node::operator=(const Node& node)
{
	_node = node._node;
	return *this;
}

Xml::Node Xml::Node::GetNode(const std::string& name)
{
	return _node->first_node(name.c_str());
}

std::string Xml::Node::GetAttribute(const std::string& att_name)
{
	rapidxml::xml_attribute<>* att = _node->first_attribute(att_name.c_str());

	if (!att) {
		throw Xml::Exception("Parsing attribute name : " + att_name + ".");
		return "";
	}

	return std::string(att->value(), att->value_size());
}

std::string Xml::Node::GetValue()
{
//	_node->remove_node(<#xml_node<char> *where#>)
	return std::string(_node->value(), _node->value_size());
}

std::string Xml::Node::GetChildNodeValue(const std::string& name)
{
	rapidxml::xml_node<>* node = _node->first_node(name.c_str());

	if (!node) {
		throw Xml::Exception("Parsing node name : " + name + ".");
		return "";
	}
	return std::string(node->value(), node->value_size());
}

void Xml::Node::RemoveChildNode(const std::string& name)
{
	rapidxml::xml_node<>* node = _node->first_node(name.c_str());
	
	if (node) {
		_node->remove_node(node);
	}
}

std::vector<std::pair<std::string, std::string>> Xml::Node::GetAtributes()
{
	std::vector<std::pair<std::string, std::string>> atts;

	rapidxml::xml_attribute<>* att = _node->first_attribute();

	if (!att) {
		throw Xml::Exception("Reading attributes");
		return atts;
	}

	while (att) {
		atts.push_back(std::pair<std::string, std::string>(
			std::string(att->name(), att->name_size()), std::string(att->value(), att->value_size())));

		att = att->next_attribute();
	}

	return atts;
}

bool Xml::Node::IsValid() const
{
	return _node != nullptr;
}

Xml::Node Xml::Node::GetNextSibling()
{
	return Xml::Node(_node->next_sibling());
}

Xml::Node Xml::Node::GetFirstNode()
{
	return Xml::Node(_node->first_node());
}

std::string Xml::Node::GetName()
{
	return std::string(_node->name(), _node->name_size());
}

rapidxml::xml_node<>* Xml::Node::GetNodeHandle()
{
	return _node;
}

void Xml::Node::AddAttribute(const std::string& name, const std::string& value)
{
	rapidxml::xml_document<>* doc = _node->document();
	char* nn = doc->allocate_string(name.c_str());
	char* vv = doc->allocate_string(value.c_str());
	_node->append_attribute(doc->allocate_attribute(nn, vv));
}

void Xml::Node::AddNode(Node& node)
{
	_node->append_node(node._node);
}

void Xml::Node::AddNode(const Node& node)
{
	_node->append_node(node._node);
}

Xml::Node Xml::CreateNode(const std::string& name)
{
	char* nn = _xml_doc->allocate_string(name.c_str());
	return Node(_xml_doc->allocate_node(rapidxml::node_element, nn));
}

void Xml::AddMainNode(Xml::Node& node)
{
	_xml_doc->append_node(node.GetNodeHandle());
}

Xml::Node Xml::CreateNode(const std::string& name, const std::string& value)
{
	char* nn = _xml_doc->allocate_string(name.c_str());
	char* vv = _xml_doc->allocate_string(value.c_str());
	return Node(_xml_doc->allocate_node(rapidxml::node_element, nn, vv));
}
}
