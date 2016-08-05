#include "axlib.hpp"

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
