#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_LightCommandInterpreter.h"
#include "rover_telemetry.h"

namespace rover
{
	namespace commanding
	{
		LightCommandInterpreter::LightCommandInterpreter(rover::chassic::LightEmitter& frontLight)
			: _frontLight(frontLight)
		{ }

		bool LightCommandInterpreter::handle(const Command& command)
		{
			if(command.compareModule("LT"))
			{
				// LIGHT
				if(command.compareAction("FR"))
				{
					// FRONT
					if(command.compareArgument1("ON"))
					{
						_frontLight.enable();
						return true;
					}
					else if(command.compareArgument1("OF"))
					{
						_frontLight.enable(false);
						return true;
					}
					else
					{
						rover::telemetry::Logger::debug("Wrong LIGHT FRONT command");
					}
				}
				else
				{
					rover::telemetry::Logger::debug("Wrong LIGHT command");
				}				
			}

			return false;
		}
	}
}