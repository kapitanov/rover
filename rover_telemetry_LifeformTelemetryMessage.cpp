#include "rover_telemetry_LifeformTelemetryMessage.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "rover_telemetry_LifeformTelemetryMessage.h"

namespace rover
{
	namespace telemetry
	{
		const prog_uchar REPLY_DETECTED[] PROGMEM = { "LIFEFORM|DETECTED\0" };
		const prog_uchar REPLY_NOT_DETECTED[] PROGMEM = { "LIFEFORM|NOT_DETECTED\0" };

		LifeformTelemetryMessage::LifeformTelemetryMessage(const bool detected)
			: _detected(detected)
		{ }

		void LifeformTelemetryMessage::write(Stream& stream) const
		{
			const prog_uchar* message = _detected ? REPLY_DETECTED : REPLY_NOT_DETECTED;
			writeFromFlash(stream, message);
		}
	}
}