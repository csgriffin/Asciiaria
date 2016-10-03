#pragma once
#include "Object.h"
#include "Vector.h"

namespace df {
	class TestObject :
		public Object
	{
	private:
	public:
		int moveFlag;
		TestObject();
		void draw();
		int eventHandler(const Event *p_e);
	};
}
