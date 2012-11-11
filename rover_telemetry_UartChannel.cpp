#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_telemetry_UartChannel.h"

namespace rover
{
	namespace telemetry
	{
		UartChannel::UartChannel(int speed)
			: _speed(speed)
		{ }
				
		void UartChannel::initialize()
		{
			Serial.begin(_speed);
		}

		void UartChannel::write(const TelemetryMessage& message)
		{
			message.write(Serial);
			Serial.print('\n');
		}
	}
}