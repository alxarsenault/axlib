#include "axlib.hpp"
#include "Button.hpp"
#include "Sprite.hpp"

int main(int arc, char* argv[])
{
	ax::Xml xml;
	ax::Xml::Node layout = xml.CreateNode("Layout");
	xml.AddMainNode(layout);
	xml.Save("/Users/alexarse/Desktop/potatoj.xml");
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

		// Add button.
		auto btn = std::make_shared<ax::Button>(ax::Rect(20, 20, 60, 25),
			ax::Button::Events([](ax::event::Msg* msg) { ax::util::console::Print("Button click");
			std::string file = ax::App::GetInstance().OpenFileDialog();
			ax::console::Print("File :", file);
//			ax::App::GetInstance().SetFrameSize(ax::Size(200, 200));
//			ax::App::GetInstance().SetTitleBar(false);
}
			),
			ax::Button::Info(), "", "Button");

		win->node.Add(btn);

		ax::Point next_pos_right = btn->GetWindow()->dimension.GetRect().GetNextPosRight(8);

		ax::Button::Builder btn_builder;
		auto btn2 = btn_builder.Create(
			next_pos_right, "/Users/alexarse/Desktop/Projects/axlib/example/widget/ButtonText.json");

		//		auto btn = std::make_shared<ax::Button>( );
		//
		//		auto btn2 = std::make_shared<ax::Button>(ax::Rect(next_pos_right, ax::Size(60, 25)),
		//			ax::Button::Events([](ax::event::Msg* msg) { ax::util::console::Print("Button click"); }),
		//			ax::Button::Info(), "", "Button");

		if (btn2 != nullptr) {
			win->node.Add(btn2);
		}
		
		ax::Sprite::Info sprite_info;
		sprite_info.sprite_size = ax::Size(9, 9);
		sprite_info.n_sprite = 2;
		sprite_info.img_path = "/Users/alexarse/Desktop/resources/axLED_9x9.png";
		auto sprite = std::make_shared<ax::Sprite>(ax::Rect(100, 100, 9, 9), sprite_info);
		sprite->SetCurrentIndex(1);
		win->node.Add(sprite);
		
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
