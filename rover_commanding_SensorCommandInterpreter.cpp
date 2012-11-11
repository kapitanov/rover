#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_SensorCommandInterpreter.h"
#include "rover_telemetry.h"

namespace rover
{
	namespace commanding
	{		
		SensorCommandInterpreter::SensorCommandInterpreter(rover::chassic::RangingSensor& rangingSensor)
			: _rangingSensor(rangingSensor)
		{ }

		bool SensorCommandInterpreter::handle(const Command& command)
		{
			if(command.compareModule("SN"))
			{
				// SENSOR
				if(command.compareAction("RS"))
				{
					// RANGING SENSOR
					unsigned int distance;
					rover::chassic::RangingSensorResponse response = _rangingSensor.measure(distance);
					switch (response)
					{
					case rover::chassic::RS_SUCCESS:
						rover::telemetry::Channel->write(rover::telemetry::DistanceTelemetryMessage(distance));
						break;
					case rover::chassic::RS_ERROR:
						rover::telemetry::Logger::error("Ranging sensor error");
						break;
					}
					return true;
				}
				else
				{
					rover::telemetry::Logger::debug("Wrong SENSOR command");
				}				
			}

			return false;
		}
	}
}