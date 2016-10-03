#pragma once

#include <stdio.h>
#include "Manager.h"

namespace df {

	const std::string LOGFILE_NAME = "dragonfly.log";

	class LogManager :
		public Manager
	{

	private:
		LogManager();
		LogManager(LogManager const&);
		void operator=(LogManager const&);
		bool do_flush;
		FILE *p_f;

	public:
		~LogManager();

		static LogManager &getInstance();

		int startUp();

		void shutDown();

		void setFlush(bool do_flush = true);

		int writeLog(const char *fmt, ...) const;
	};
}

