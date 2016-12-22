#pragma once

#include <string>
#include "Util.hpp"

namespace cocoa {
	void AddEventToDispatchQueue();
	
	void HideMouse();
	void ShowMouse();
	
	std::string OpenFileDialog();
	std::string SaveFileDialog();
	
	ax::Size GetScreenSize();
	
	std::string GetPasteboardContent();
	
	std::string GetAppPath();
	std::string GetAppDirectory();
}
