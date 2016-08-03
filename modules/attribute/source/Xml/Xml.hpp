#pragma once

#include "Attribute.hpp"
#include "XmlHelper.hpp"

namespace ax {
void XmlRecursiveWriter(
	const ax::Attribute& att, XmlHelper& doc, XmlHelper::Node& parent, bool value_as_attribute);

std::string XmlWriter(const ax::Attribute& att, bool value_as_attribute);
}