#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "rover_chassic_LifeformDetector.h"
#include "rover_telemetry.h"

namespace rover
{
	namespace chassic
	{
		LifeformDetector::LifeformDetector(int detectorPin)
			: _detectorPin(detectorPin),
			  _state(LDS_IDLE)
		{ }

		void LifeformDetector::initialize() const
		{
			pinMode(_detectorPin, INPUT);
		}

		LifeformDetectorResponse LifeformDetector::detect()
		{
			LifeformDetectorResponse response = detectInternal();

			LifeformDetectorState state;
			switch (response)
			{
			case rover::chassic::LFD_NOTHING_DETECTED:
				state = LDS_NOT_DETECTED;
				break;
			case rover::chassic::LFD_LIFEFORM_DETECTED:
				state = LDS_DETECTED;
				break;
			}

			if(_state != state)
			{
				rover::telemetry::Logger::debug(
					state == LDS_DETECTED
					? "LifeformDetector: detected lifeform"
					: "LifeformDetector: nothing detected");
				_state = state;
			}
			
			return response;
		}

		LifeformDetectorResponse LifeformDetector::detectInternal() const
		{
			int value = digitalRead(_detectorPin);
			
			if(value == HIGH)
			{
				rover::telemetry::Logger::debug(String("LifeformDetector: ") + value);
				return LFD_LIFEFORM_DETECTED;
			}

			return LFD_NOTHING_DETECTED;
		}
	}
}