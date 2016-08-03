#include "ConsolePrint.hh"
#include "FileSystem.hh"
#include "AttributeDocument.hh"

int main(int argc, char* argv[])
{
	if(argc < 2) {
		tk::console::Print("Missing filename.");
		return -1;
	}
	
	const std::string filename(argv[1]);
	tk::os::Path filepath(filename);
	
	if(!filepath.IsValid()) {
		tk::console::Error("Invalid file path :", filename);
		return -1;
	}
	
	// Create attribute document.
	tk::AttributeDocument att_doc(filepath.GetPath(), tk::AttributeDocument::Type::JSON);
	
	if(!att_doc.IsOpen()) {
		tk::console::Error("Can't open attribute document.");
		return -1;
	}
	
	if(!att_doc.IsValid()) {
		tk::console::Print("Invalid document format :");
		
		const std::pair<int, int> line_char = att_doc.GetErrorLineCharOffset();
		tk::console::Print("Line :", line_char.first, " char_offset :", line_char.second);
		return -1;
	}
	
	tk::console::Print("All good.");
	
	return 0;
}
