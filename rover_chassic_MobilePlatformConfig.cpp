#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "rover_chassic_MobilePlatformConfig.h"

namespace rover
{
	namespace chassic
	{
		MobilePlatformConfig::MobilePlatformConfig(
			int motor1Pin1,
			int motor1Pin2,
			int motor2Pin1,
			int motor2Pin2)
		{
			motorPins[0] = motor1Pin1;
			motorPins[1] = motor1Pin2;
			motorPins[2] = motor2Pin1;
			motorPins[3] = motor2Pin2;
		}
	}
}