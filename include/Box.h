#pragma once
#include "Vector.h"

namespace df {
	class Box
	{
	private:
		Vector corner;
		float horizontal;
		float vertical;
		
	public:
		Box();
		Box(Vector init_corner, float init_horizontal, float init_vertical);
		void setCorner(Vector new_corner);
		Vector getCorner() const;
		void setHorizontal(float new_horizontal);
		float getHorizontal() const;
		void setVertical(float new_vertical);
		float getVertical() const;
	};
}

