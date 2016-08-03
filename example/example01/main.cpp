#include <iostream>

#include "ConsolePrint.hpp"
#include "Point2D.hpp"
#include "EventManager.hpp"


int main()
{
	ax::math::Point2D<int> p01(12, 32);
	ax::util::console::CPrint(ax::util::console::Color::BoldBlue, p01);
	ax::util::console::Print("test");
	ax::util::console::Log("Bang");
	ax::util::console::Warning("Bang");
	ax::util::console::Error("Bang");
	std::cout << "Test" << std::endl;
	

	ax::event::Manager evt_manager;
	
	ax::event::Object obj0(&evt_manager);
	
	obj0.AddConnection(0, ax::event::Function([](ax::event::Msg* msg) {
		std::cout << "Blblabla " << static_cast<ax::event::StringMsg*>(msg)->GetMsg() << std::endl;
	}));
	
	obj0.PushEvent(0, new ax::event::StringMsg("Bang1"));
	obj0.PushEvent(0, new ax::event::StringMsg("Bang2"));
	obj0.PushEvent(0, new ax::event::StringMsg("Bang3"));
	
//	while(1) {
//		while(evt_manager.GetEventQueueSize()) {
//			evt_manager.CallNext();
//		}
//	}
	

	return 0;
}