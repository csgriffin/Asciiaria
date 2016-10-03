#pragma once
#include "Object.h"
#include <string>
#include "Object.h"
#include "Event.h"

namespace df {

	enum ViewObjectLocation {
		UNDEFINED=-1,
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		CENTER_LEFT,
		CENTER_CENTER,
		CENTER_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT,
	};

	class ViewObject :
		public Object
	{
	private:
		std::string view_string;
		int value;
		bool draw_value;
		bool border;
		Color color;
		ViewObjectLocation location;

	public:
		ViewObject();
		virtual void draw();
		virtual int eventHandler(const Event *p_e);
		void setLocation(ViewObjectLocation new_location);
		ViewObjectLocation getLocation() const;
		void setValue(int new_value);
		int getValue() const;
		void setBorder(bool new_border);
		bool getBorder() const;
		void setColor(Color new_color);
		Color getColor() const;
		void setViewString(std::string new_view_string);
		std::string getViewString() const;
		void setDrawValue(bool new_draw_value = true);
		bool getDrawValue() const;
	};
}

