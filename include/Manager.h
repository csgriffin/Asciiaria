#pragma once
#include <string>
#include "Event.h"

namespace df {

	class Manager
	{

	private:
		std::string type;
		bool is_started;

	protected:
		void setType(std::string type);

	public:
		Manager();
		virtual ~Manager();

		std::string getType() const;

		virtual int startUp();

		virtual void shutDown();

		bool isStarted() const;

		int onEvent(const Event *p_event) const;
	};

}
