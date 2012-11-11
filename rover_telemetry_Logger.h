#pragma once

#include "rover_telemetry_Channel.h"
#include "rover_telemetry_LogSeverity.h"

namespace rover
{
	namespace telemetry
	{
		class Logger
		{
		public:
			static void debug(const char* message);
			static void info(const char* message);
			static void warn(const char* message);
			static void error(const char* message);

			static void debug(const String& message);
			static void info(const String& message);
			static void warn(const String& message);
			static void error(const String& message);
									
		private:
			static void write(LogSeverity severity, const String& message);
			static void write(LogSeverity severity, const char* message);
		};
	}
}