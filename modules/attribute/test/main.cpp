#include <iostream>
#include <exception>
#include "ConsolePrint.hh"
#include "FilePrint.hh"

#include "AttributeDocument.hh"

#include "gtest/gtest.h"

TEST(AttributeDocumentRead, WrongFile)
{
	erft::tk::AttributeDocument att_doc_empty;
	EXPECT_EQ(false, att_doc_empty.IsOpen());

	erft::tk::AttributeDocument att_doc("john_doe.json", erft::tk::AttributeDocument::Type::JSON);
	EXPECT_EQ(false, att_doc.IsOpen());
	EXPECT_EQ(false, att_doc.IsValid());

	erft::tk::AttributeDocument att_doc2("file02.json", erft::tk::AttributeDocument::Type::JSON);
	EXPECT_EQ(true, att_doc2.IsOpen());
	EXPECT_EQ(false, att_doc2.IsValid());

	erft::tk::AttributeDocument att_doc3("file02.json", erft::tk::AttributeDocument::Type::JSON);
	EXPECT_EQ(true, att_doc3.IsOpen());
	EXPECT_EQ(false, att_doc3.IsValid());
}

TEST(AttributeDocumentRead, ValidFile)
{
	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
	EXPECT_EQ(true, att_doc.IsOpen());
	EXPECT_EQ(true, att_doc.IsValid());
}

TEST(MainAttributeRead, MainAttribute)
{
	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
	EXPECT_EQ("", att_doc.GetMainAttribute().GetName());
}

TEST(MainAttributeRead, MainAttributeType)
{
	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
	EXPECT_EQ(erft::tk::Attribute::Type::OBJECT, att_doc.GetMainAttribute().GetType());
}

TEST(AttributeRead, Attribute)
{
	//	{
	//		"menu":
	//		{
	//			"id" : "file",
	//			"value" : "File",
	//			"popup":
	//			{
	//				"menuitem" :[
	//					{ "value" : "New", "onclick" : "CreateNewDoc()" },
	//					{ "value" : "Open", "onclick" : "OpenDoc()" },
	//					{ "value" : "Close", "onclick" : "CloseDoc()" }
	//				]
	//			}
	//		}
	//	}

	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
	EXPECT_EQ("", att_doc.GetMainAttribute()["menu"].GetValue<std::string>());
	EXPECT_EQ("file", att_doc.GetMainAttribute()["menu"]["id"].GetValue<std::string>());
	EXPECT_EQ("File", att_doc.GetMainAttribute()["menu"]["value"].GetValue<std::string>());
}

TEST(AttributeRead, AttributeArray)
{
	//	{
	//		"menu":
	//		{
	//			"id" : "file",
	//			"value" : "File",
	//			"popup":
	//			{
	//				"menuitem" :[
	//					{ "value" : "New", "onclick" : "CreateNewDoc()" },
	//					{ "value" : "Open", "onclick" : "OpenDoc()" },
	//					{ "value" : "Close", "onclick" : "CloseDoc()" }
	//				]
	//			}
	//		}
	//	}

	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
	erft::tk::Attribute& att = att_doc.GetMainAttribute()["menu"]["popup"]["menuitem"];

	EXPECT_EQ(3, att.GetAttributes().size());

	EXPECT_EQ("New", att[0]["value"].GetValue<std::string>());
	EXPECT_EQ("Open", att[1]["value"].GetValue<std::string>());
	EXPECT_EQ("Close", att[2]["value"].GetValue<std::string>());

	EXPECT_EQ("CreateNewDoc()", att[0]["onclick"].GetValue<std::string>());
	EXPECT_EQ("OpenDoc()", att[1]["onclick"].GetValue<std::string>());
	EXPECT_EQ("CloseDoc()", att[2]["onclick"].GetValue<std::string>());
}

TEST(AttributeRead, InvalidAttribute)
{
	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
	erft::tk::Attribute& menu = att_doc.GetMainAttribute()["menu"];

	EXPECT_EQ(erft::tk::Attribute::Type::NONE, menu["banana"].GetType());
	EXPECT_EQ(false, menu["banana"].IsValue());
}

TEST(AttributeRead, ValidAttribute)
{
	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
	erft::tk::Attribute& menu = att_doc.GetMainAttribute()["menu"];

	EXPECT_EQ(erft::tk::Attribute::Type::STRING, menu["id"].GetType());
	EXPECT_EQ(true, menu["id"].IsValue());
}

TEST(AttributeRead, HasAttribute)
{
	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
	erft::tk::Attribute& menu = att_doc.GetMainAttribute()["menu"];

	EXPECT_EQ(true, menu.Has("id"));
	EXPECT_EQ(true, menu["popup"].Has("menuitem"));
	EXPECT_EQ(false, menu.Has("john doe"));
}

TEST(AttributeRead, ArrayType)
{
	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
	erft::tk::Attribute& att = att_doc.GetMainAttribute()["menu"]["popup"]["menuitem"];

	EXPECT_EQ(erft::tk::Attribute::Type::ARRAY, att.GetType());
}

TEST(FileWrite, Writer)
{
	erft::tk::AttributeDocument att_doc("file01.json", erft::tk::AttributeDocument::Type::JSON);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}