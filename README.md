# axlib
A toolkit to develop better C++ GUI cross-platform multimedia applications.

## Features
- Easy to setup.
- Currently supports Mac OS X (10.11), Windows, Linux (X11) and Raspberry Pi (embedded).
- Extensive use of C++14 and Standard Template Library (STL) syntax.
- Use of C++14 lambda functions and threads for event management.
- Minimize interaction with operating systems.

## Modules
- attribute
- audio
- core
- event
- graphic
- math
- midi
- os
- util
- widget

## Example
Blank example : This will create an empty grey application frame. 

```cpp
#include <axlib/axlib.hpp>

int main(int arc, char* argv[])
{
	// Get app instance.
	ax::App& app(ax::App::GetInstance());

	app.AddMainEntry([&app]() {
		// Create main window.
		ax::Window* win = ax::Window::Create(ax::Rect(0, 0, 500, 500));

		// Set main window drawing callback.
		win->event.OnPaint = ax::WFunc<ax::GC>([win](ax::GC gc) {
			const ax::Rect rect(win->dimension.GetRect());
			// Draw window background.
			gc.SetColor(ax::Color(0.4));
			gc.DrawRectangle(rect);
		});

		// Set main window.
		app.AddTopLevel(std::shared_ptr<ax::Window>(win));
	});

	// Reset frame size after GUI is loaded.
	app.AddAfterGUILoadFunction([&app]() { app.SetFrameSize(ax::Size(500, 500)); });

	// Start main loop.
	// Nothing after this line will be executed.
	app.MainLoop();

	return 0;
}
```