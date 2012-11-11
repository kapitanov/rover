#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "rover_chassic_RangingSensor.h"

namespace rover
{
	namespace chassic
	{
		RangingSensor::RangingSensor(int triggerPin, int echoPin)
			: _triggerPin(triggerPin), _echoPin(echoPin)
		{
		}

		void RangingSensor::initialize() const
		{
			pinMode(_triggerPin, OUTPUT);
			pinMode(_echoPin, INPUT);
		}

		RangingSensorResponse RangingSensor::measure(unsigned int& distance) const
		{
			digitalWrite(_triggerPin, LOW);
			delayMicroseconds(2); 
			digitalWrite(_triggerPin, HIGH);
			delayMicroseconds(10);
			digitalWrite(_triggerPin, LOW);

			unsigned int pulseDuration = pulseIn(_echoPin, HIGH);

			distance = pulseDuration / 29 / 2;
			
			return RS_SUCCESS;
		}
	}
}