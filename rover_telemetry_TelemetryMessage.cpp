#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "rover_telemetry_TelemetryMessage.h"

namespace rover
{
	namespace telemetry
	{
		void TelemetryMessage::writeFromFlash(Stream& stream, const prog_uchar* buffer) const
		{
			long address = reinterpret_cast<long>(buffer);
			while(true)
			{
				char c = pgm_read_byte_far(address);
				if(c == '\0')
				{
					return;
				}

				stream.print(c);
				address++;
			}
		}
	}
}