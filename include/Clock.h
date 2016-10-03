#pragma once

namespace df {

	class Clock
	{

	private:
		long int previous_time;
	public:
		Clock();
		long int delta();
		long int split() const;
	};
}

