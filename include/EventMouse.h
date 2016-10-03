#pragma once
#include "Event.h"
#include "Vector.h"
namespace df {

	const std::string MOUSE_EVENT = "df::mouse";

	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		PRESSED,
		MOVED,
	};

	enum EventMouseButton {
		UNDEFINED_MOUSE_BUTTON = -1,
		LEFT,
		RIGHT,
		MIDDLE,
	};
	class EventMouse :
		public Event
	{
	private:
		EventMouseAction mouse_action;
		EventMouseButton mouse_button;
		Vector mouse_xy;

	public:
		EventMouse();
		void setMouseAction(EventMouseAction new_mouse_action);
		EventMouseAction getMouseAction() const;
		void setMouseButton(EventMouseButton new_mouse_button);
		EventMouseButton getMouseButton() const;
		void setMousePosition(Vector new_mouse_xy);
		Vector getMousePosition() const;
	};
}

