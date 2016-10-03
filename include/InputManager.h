#pragma once
#include "Manager.h"

namespace df {
	class InputManager :
		public Manager
	{

	private:
		InputManager();
		InputManager(InputManager const&);
		void operator=(InputManager const&);

	public:
		static InputManager &getInstance();
		int startUp();
		void shutDown();
		void getInput();
	};
}

