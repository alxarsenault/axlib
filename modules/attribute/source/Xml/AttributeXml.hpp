#pragma once

#include "Attribute.hpp"
#include "Xml.hpp"

namespace ax {
void XmlRecursiveWriter(const ax::Attribute& att, Xml& doc, Xml::Node& parent, bool value_as_attribute);

std::string XmlWriter(const ax::Attribute& att, bool value_as_attribute);
}