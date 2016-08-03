
#include "ConsolePrint.hh"
#include "Attribute.hh"
#include "AttributeDocument.hh"

class MyClass {
public:
	MyClass()
	{
	}

	MyClass(double vd, int vi, const std::string& str)
		: _v1(vd)
		, _v2(vi)
		, _v3(str)
	{
	}

	MyClass(const tk::Attribute& att)
	{
		_v1 = att["v1"].GetValue<double>();
		_v2 = att["v2"].GetValue<int>();
		_v3 = att["v3"].GetValue<std::string>();
	}

	tk::Attribute ToAttribute()
	{
		tk::Attribute obj("MyClass", tk::Attribute::Type::OBJECT);
		obj.Add(tk::Attribute::Create<double>("v1", _v1));
		obj.Add(tk::Attribute::Create<int>("v2", _v2));
		obj.Add(tk::Attribute::Create<std::string>("v3", _v3));
		return obj;
	}

	void Print()
	{
		tk::console::Print(_v1, _v2, _v3);
	}

private:
	double _v1;
	int _v2;
	std::string _v3;
};

int main()
{
	MyClass my_class1(0.23, 83, "John Doe");
	MyClass my_class2(123.2321, 87, "John");

	// Create attribute document.
	tk::AttributeDocument att_doc;
	{
		// Main attribute object.
		tk::Attribute main_obj("main_obj", tk::Attribute::Type::OBJECT);
		{
			// Create attribute array.
			tk::Attribute my_class_array("my_array", tk::Attribute::Type::ARRAY);

			// Add MyClass info.
			my_class_array.Add(my_class1.ToAttribute());
			my_class_array.Add(my_class2.ToAttribute());

			// Add array to main attribute.
			main_obj.Add(std::move(my_class_array));
		}

		// Add main attribute to document.
		att_doc.GetRootAttribute().Add(std::move(main_obj));
	}

	// Output attribute document content in json.
	tk::console::Print(att_doc.ToString(tk::AttributeDocument::Type::JSON));

	// Output attribute document content in xml.
	tk::console::Print(att_doc.ToString(tk::AttributeDocument::Type::XML));

	// Create two classes from the attribute document.
	{
		auto& my_class_att_array(att_doc["main_obj"]["my_array"]);
		MyClass my_class3(my_class_att_array[0]);
		MyClass my_class4(my_class_att_array[1]);

		my_class3.Print();
		my_class4.Print();
	}

	// Bad way to do it.
	// Calls to Attribute::operator[](const std::string&) are expensive.
	{
		MyClass my_class5(att_doc["main_obj"]["my_array"][0]);
		MyClass my_class6(att_doc["main_obj"]["my_array"][1]);

		my_class5.Print();
		my_class6.Print();
	}

	return 0;
}

// Program output.

/*
{"main_obj": {
	"my_array": [
		"MyClass": {
			"v1":"0.230000",
			"v2":"83",
			"v3":"John Doe"
		},
		 "MyClass": {
			 "v1":"123.232100",
			 "v2":"87",
			 "v3":"John"
		 }
	 ]
}
}
<?xml version="1.0" encoding="utf-8"?>
<main_obj>
	<my_array>
		<MyClass>
			<v1>0.230000</v1>
			<v2>83</v2>
			<v3>John Doe</v3>
		</MyClass>
	</my_array>
	<my_array>
		<MyClass>
			<v1>123.232100</v1>
			<v2>87</v2>
			<v3>John</v3>
		</MyClass>
	</my_array>
</main_obj>


0.23 83 John Doe
123.232 87 John
0.23 83 John Doe
123.232 87 John
*/