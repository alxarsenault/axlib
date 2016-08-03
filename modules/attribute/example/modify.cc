#include "AttributeDocument.hh"
#include "ConsolePrint.hh"

int main()
{
	tk::AttributeDocument att_doc("resources/file01.json", tk::AttributeDocument::Type::JSON);

	if (!att_doc.IsOpen()) {
		tk::console::Error("Can't open document.");
		std::exit(1);
	}

	if (!att_doc.IsValid()) {
		tk::console::Error("Document is not valid.");
		std::exit(1);
	}

	tk::Attribute& menu = att_doc.GetRootAttribute()["menu"];

	std::string v = menu.GetAttributeDefaultValue<std::string>("john", "Patrick");
	std::string v2 = menu.GetAttributeDefaultValue<std::string>("john____", "Patrick");
	double v3 = menu.GetAttributeDefaultValue<double>("john____", 12345);

	tk::console::Print(v);
	tk::console::Print(v2);
	tk::console::Print(v3);

	// Add value on top.
	menu.AddFront(tk::Attribute::Create<std::string>("name", "George"));

	// Add array.
	tk::Attribute banana("banana", tk::Attribute::Type::ARRAY);

	// Add first array object.
	tk::Attribute obj1(tk::Attribute::Type::OBJECT);
	obj1.Add(tk::Attribute::Create<std::string>("type1", "b2"));
	obj1.Add(tk::Attribute::Create<std::string>("type2", "b2"));
	obj1.Add(tk::Attribute::Create<std::string>("type3", "b2"));
	obj1.Add(tk::Attribute::Create<std::string>("type4", "b2"));
	obj1.Add(tk::Attribute::Create<double>("type5", 12345.6789));
	banana.Add(std::move(obj1));

	// Add second array object.
	tk::Attribute obj2(tk::Attribute::Type::OBJECT);
	obj2.Add(tk::Attribute::Create<std::string>("type1", "b2"));
	obj2.Add(tk::Attribute::Create<std::string>("type2", "b2"));
	obj2.Add(tk::Attribute::Create<std::string>("type3", "b2"));
	obj2.Add(tk::Attribute::Create<std::string>("type4", "b2"));
	obj2.Add(tk::Attribute::Create<double>("type5", 145.6789));
	banana.Add(std::move(obj2));

	att_doc.GetRootAttribute()["menu"].Add(std::move(banana));

	std::string json_content = att_doc.ToString(tk::AttributeDocument::Type::JSON);
	tk::console::Print(json_content);

	tk::AttributeDocument obj_to_str_doc;
	tk::Attribute popup = menu["popup"];
	obj_to_str_doc.GetRootAttribute().Add(std::move(popup));

	tk::console::Print("POOPUPUPUP ::");
	tk::console::Print(obj_to_str_doc.ToString(tk::AttributeDocument::Type::JSON));

	// Look if popup still exist.
	tk::console::Print("PP value", menu["popup"]["menuitem"][0]["value"].GetValue<std::string>());

	return 0;
}