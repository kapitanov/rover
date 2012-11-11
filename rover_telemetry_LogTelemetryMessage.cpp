#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "rover_telemetry_LogTelemetryMessage.h"

namespace rover
{
	namespace telemetry
	{
		const prog_uchar LOG_HEADER[] PROGMEM = { "LOG|\0" };

		const prog_uchar TYPE_DEBUG[] PROGMEM = { "DEBUG|\0" };
		const prog_uchar TYPE_INFO[] PROGMEM = { "INFO|\0" };
		const prog_uchar TYPE_WARN[] PROGMEM = { "WARN|\0" };
		const prog_uchar TYPE_ERROR[] PROGMEM = { "ERROR|\0" };

		LogTelemetryMessage::LogTelemetryMessage(LogSeverity severity, const String& message)
			: _severity(severity),
			  _message(message)
		{ }
			
		void LogTelemetryMessage::write(Stream& stream) const
		{
			const prog_uchar* severityText;

			switch (_severity)
			{
			case LOG_DEBUG:
				severityText = TYPE_DEBUG;
				break;
			case LOG_INFO:
				severityText = TYPE_INFO;
				break;
			case LOG_WARN:
				severityText = TYPE_WARN;
				break;
			case LOG_ERROR:
				severityText = TYPE_ERROR;
				break;
			default:
				break;
			}

			writeFromFlash(stream, LOG_HEADER);
			writeFromFlash(stream, severityText);
			stream.print(_message);
		}
	}
}