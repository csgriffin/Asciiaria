#pragma once
#include <string>

namespace df {
	class Frame
	{
	private:
		int width;
		int height;
		std::string frame_str;
	public:
		Frame();
		Frame(int new_width, int new_height, std::string new_frame_str);
		void setWidth(int new_width);
		int getWidth() const;
		void setHeight(int new_height);
		int getHeight() const;
		void setString(std::string new_frame_str);
		std::string getString() const;
	};
}

