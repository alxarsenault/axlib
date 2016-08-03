#include "AttributeDocument.hh"
#include "ConsolePrint.hh"

#include <fstream>

std::vector<char> FileToCharVector(const std::string& file_path)
{
	std::ifstream file(file_path, std::ios::binary);
	std::vector<char> data;
	//	data.reserve(file_size);
	data.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

	return data;
}

int main()
{
	tk::AttributeDocument att_doc("resources/file01.json", tk::AttributeDocument::Type::JSON);
	std::string json_content = att_doc.ToString(tk::AttributeDocument::Type::JSON);
	std::string xml_content = att_doc.ToString(tk::AttributeDocument::Type::XML);
	tk::console::Print(json_content);
	tk::console::Print(xml_content);

	std::vector<char> content = FileToCharVector("resources/file01.json");
	tk::AttributeDocument att_doc2(content, tk::AttributeDocument::Type::JSON);

	auto& menu = att_doc2.GetRootAttribute()["menu"];
	menu["id"].SetValue<std::string>("Tralala");
	menu["value"].SetValue<std::string>("Bangerang");
	att_doc2.Save("file01_mod.json", tk::AttributeDocument::Type::JSON);

	// Start from scratch.
	tk::AttributeDocument att_doc3;
	att_doc3.GetRootAttribute().Add(tk::Attribute("menu", tk::Attribute::Type::OBJECT));

	auto& menu3 = att_doc3.GetRootAttribute()["menu"];
	menu3.Add(tk::Attribute::Create<std::string>("id", "file"));
	menu3.Add(tk::Attribute::Create<std::string>("value", "File"));

	menu3.Add(tk::Attribute("menuitem", tk::Attribute::Type::ARRAY));

	auto& menu_array = menu3["menuitem"];

	auto obj1 = tk::Attribute(tk::Attribute::Type::OBJECT);
	obj1.Add(tk::Attribute::Create<std::string>("value", "New"));
	obj1.Add(tk::Attribute::Create<std::string>("onclick", "CreateNewDoc()"));

	menu_array.Add(std::move(obj1));

	auto obj2 = tk::Attribute(tk::Attribute::Type::OBJECT);
	obj2.Add(tk::Attribute::Create<std::string>("value", "Open"));
	obj2.Add(tk::Attribute::Create<std::string>("onclick", "OpenDoc()"));

	menu_array.Add(std::move(obj2));

	auto obj3 = tk::Attribute(tk::Attribute::Type::OBJECT);
	obj3.Add(tk::Attribute::Create<std::string>("value", "Close"));
	obj3.Add(tk::Attribute::Create<std::string>("onclick", "CloseDoc()"));

	menu_array.Add(std::move(obj3));

	att_doc3.Save("resources/file01_scratch.json", tk::AttributeDocument::Type::JSON);

	return 0;
}