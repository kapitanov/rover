#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_chassic_LightEmitter.h"
#include "rover_telemetry.h"

namespace rover
{
	namespace chassic
	{
		LightEmitter::LightEmitter(const int pin)
			: _pin(pin), _isEnabled(false)
		{
			pinMode(_pin, OUTPUT);
			digitalWrite(_pin, 0);
		}

		bool LightEmitter::enabled() const
		{
			return _isEnabled;
		}

		void LightEmitter::enable(bool isEnabled)
		{
			if(isEnabled != _isEnabled)
			{
				_isEnabled = isEnabled;
				digitalWrite(_pin, _isEnabled ? 1 : 0);

				rover::telemetry::Logger::debug(_isEnabled ? "LightEmitter: on" : "LightEmitter: off");
			}
		}
	}
}