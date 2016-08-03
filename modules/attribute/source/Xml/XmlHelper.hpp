#pragma once

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace ax {
class XmlHelper {
public:
	struct Exception : public std::exception {
		std::string s;

		Exception(std::string ss)
			: s(ss)
		{
		}

		~Exception() throw()
		{
		}

		const char* what() const throw()
		{
			return s.c_str();
		}
	};

	class Node {
	public:
		Node(rapidxml::xml_node<>* node);

		Node(const Node& node);

		Node& operator=(const Node& node);

		Node GetNode(const std::string& name);

		std::string GetAttribute(const std::string& att_name);

		std::string GetValue();

		std::string GetChildNodeValue(const std::string& name);

		std::vector<std::pair<std::string, std::string>> GetAtributes();

		bool IsValid() const;

		Node GetNextSibling();

		Node GetFirstNode();

		std::string GetName();

		rapidxml::xml_node<>* GetNodeHandle()
		{
			return _node;
		}

		void AddAttribute(const std::string& name, const std::string& value)
		{
			rapidxml::xml_document<>* doc = _node->document();
			char* nn = doc->allocate_string(name.c_str());
			char* vv = doc->allocate_string(value.c_str());
			_node->append_attribute(doc->allocate_attribute(nn, vv));
		}

		void AddNode(Node& node)
		{
			_node->append_node(node._node);
		}

		void AddNode(const Node& node)
		{
			_node->append_node(node._node);
		}

	private:
		rapidxml::xml_node<>* _node;
	};

	XmlHelper(const std::string& path);

	XmlHelper();

	void Save(const std::string& path);

	std::string GetString();

	Node GetNode(const std::string& name);

	bool Parse();

	bool Parse(const std::string& content);

	Node CreateNode(const std::string& name);

	void AddMainNode(XmlHelper::Node& node);

	Node CreateNode(const std::string& name, const std::string& value);

private:
	std::string _file_path;
	rapidxml::xml_document<> _xml_doc;
	std::vector<char> _xml_buffer;
};
}