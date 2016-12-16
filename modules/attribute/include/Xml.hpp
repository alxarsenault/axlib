#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// namespace rapidxml{
// template<typename T = char>
// class xml_document;
//
// template<typename T = char>
// class xml_node;
//}

namespace rapidxml {
template <class Ch> class xml_document;
template <class Ch> class xml_node;
}
// namespace rapidxml
//{
//	template<>
//	class xml_document;
//}

namespace ax {
class Xml {
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

	/**
	 * @brief Xml node.
	 */
	class Node {
	public:
		Node(rapidxml::xml_node<char>* node);

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

		rapidxml::xml_node<char>* GetNodeHandle();

		void AddAttribute(const std::string& name, const std::string& value);

		void AddNode(Node& node);

		void AddNode(const Node& node);

	private:
		rapidxml::xml_node<char>* _node;
	};

	/**
	 * @brief Create Xml document from file.
	 */
	Xml(const std::string& path);

	Xml();

	void Save(const std::string& path);

	std::string GetString();

	Node GetNode(const std::string& name);

	bool Parse();

	bool Parse(const std::string& content);

	Node CreateNode(const std::string& name);

	void AddMainNode(Xml::Node& node);

	Node CreateNode(const std::string& name, const std::string& value);

private:
	std::string _file_path;
	std::shared_ptr<rapidxml::xml_document<char>> _xml_doc;
	std::vector<char> _xml_buffer;
};
}
