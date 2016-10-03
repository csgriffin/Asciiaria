#pragma once
#include <string>
#include "Frame.h"
#include "Color.h"

namespace df {
	class Sprite
	{
	private:
		int width;
		int height;
		int max_frame_count;
		int frame_count;
		Color color;
		Frame *frame;
		std::string label;
		Sprite();
	public:
		~Sprite();
		Sprite(int max_frames);
		void setWidth(int new_width);
		int getWidth() const;
		void setHeight(int new_height);
		int getHeight() const;
		void setColor(Color new_color);
		Color getColor() const;
		int getFrameCount() const;
		int addFrame(Frame new_frame);
		Frame getFrame(int frame_number) const;
		void setLabel(std::string new_label);
		std::string getLabel() const;
	};
}

