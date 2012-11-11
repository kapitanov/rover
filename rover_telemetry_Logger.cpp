#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_telemetry_Logger.h"
#include "rover_telemetry_Channel.h"
#include "rover_telemetry_LogTelemetryMessage.h"

namespace rover
{
	namespace telemetry
	{
		void Logger::debug(const char* message)
		{
			write(LOG_DEBUG, message);
		}

		void Logger::info(const char* message)
		{
			write(LOG_INFO, message);
		}

		void Logger::warn(const char* message)
		{
			write(LOG_WARN, message);
		}

		void Logger::error(const char* message)
		{
			write(LOG_ERROR, message);
		}

		void Logger::debug(const String& message)
		{
			write(LOG_DEBUG, message);
		}

		void Logger::info(const String& message)
		{
			write(LOG_INFO, message);
		}

		void Logger::warn(const String& message)
		{
			write(LOG_WARN, message);
		}

		void Logger::error(const String& message)
		{
			write(LOG_ERROR, message);
		}
		
		void Logger::write(LogSeverity severity, const char* message)
		{
			Channel->write(rover::telemetry::LogTelemetryMessage(severity, String(message)));
		}

		void Logger::write(LogSeverity severity, const String& message)
		{
			Channel->write(rover::telemetry::LogTelemetryMessage(severity, message));
		}
	}
}