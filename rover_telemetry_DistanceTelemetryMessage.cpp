#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "rover_telemetry_DistanceTelemetryMessage.h"

namespace rover
{
	namespace telemetry
	{
		const prog_uchar LOG_HEADER[] PROGMEM = { "DISTANCE|\0" };
		const prog_uchar LOG_FOOTER[] PROGMEM = { "SM\0" };

		DistanceTelemetryMessage::DistanceTelemetryMessage(const unsigned int distance)
			: _distance(distance)
		{ }
			
		void DistanceTelemetryMessage::write(Stream& stream) const
		{
			writeFromFlash(stream, LOG_HEADER);
			stream.print(_distance);
			writeFromFlash(stream, LOG_FOOTER);
		}
	}
}