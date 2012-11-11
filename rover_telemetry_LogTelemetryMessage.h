#pragma once

#include "rover_telemetry_TelemetryMessage.h"
#include "rover_telemetry_LogSeverity.h"

class String;

namespace rover
{
	namespace telemetry
	{
		class LogTelemetryMessage : public TelemetryMessage
		{
		public:
			LogTelemetryMessage(LogSeverity severity, const String& message);
			virtual ~LogTelemetryMessage() { }

			virtual void write(Stream& stream) const;

		private:
			const LogSeverity _severity;
			const String& _message;
		};
	}
}