#include "AttributeXml.hpp"
#include <sstream>

namespace ax {

void XmlRecursiveWriter(const Attribute& att, Xml& doc, Xml::Node& parent, bool value_as_attribute)
{
	switch (att.GetType()) {
	case Attribute::Type::OBJECT:
		if (att.GetName().empty()) {
			for (auto& n : att.GetAttributes()) {
				XmlRecursiveWriter(n, doc, parent, value_as_attribute);
			}
		}
		else {
			Xml::Node child_node = doc.CreateNode(att.GetName());
			parent.AddNode(child_node);

			for (auto& n : att.GetAttributes()) {
				XmlRecursiveWriter(n, doc, child_node, value_as_attribute);
			}
		}
		break;
	case Attribute::Type::ARRAY:
		for (auto& n : att.GetAttributes()) {
			Xml::Node child_node = doc.CreateNode(att.GetName());
			parent.AddNode(child_node);
			XmlRecursiveWriter(n, doc, child_node, value_as_attribute);
		}
		break;
	case Attribute::Type::NUMBER:
	case Attribute::Type::BOOLEAN:
	case Attribute::Type::STRING:

		if (value_as_attribute) {
			parent.AddAttribute(att.GetName(), att.GetValue<std::string>());
		}
		else {
			Xml::Node child_node = doc.CreateNode(att.GetName(), att.GetValue<std::string>());
			parent.AddNode(child_node);
		}

		break;
	default:
		std::cerr << "Should never happend." << std::endl;
		break;
	}
}

std::string XmlWriter(const Attribute& att, bool value_as_attribute)
{
	Xml doc;
	if (att.GetAttributes().size() == 1) {
		Xml::Node child_node = doc.CreateNode(att.GetAttributes()[0].GetName());
		doc.AddMainNode(child_node);

		for (auto& n : att.GetAttributes()[0].GetAttributes()) {
			XmlRecursiveWriter(n, doc, child_node, value_as_attribute);
		}
	}

	return doc.GetString();
}
}