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
		SensorCommandInterpreter::SensorCommandInterpreter(
			rover::chassic::RangingSensor& rangingSensor,
			rover::chassic::LifeformDetector& lifeformDetector)
			: _rangingSensor(rangingSensor),
			  _lifeformDetector(lifeformDetector)
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
					default:
						rover::telemetry::Logger::error("Unknown RangingSensorResponse");
						break;
					}

					return true;
				}
				else if(command.compareAction("LF"))
				{
					// LIFEFORM DETECTOR
					rover::chassic::LifeformDetectorResponse response = _lifeformDetector.detect();
					switch (response)
					{
					case rover::chassic::LFD_LIFEFORM_DETECTED:
						rover::telemetry::Channel->write(rover::telemetry::LifeformTelemetryMessage(true));
						break;
					case rover::chassic::LFD_NOTHING_DETECTED:
						rover::telemetry::Channel->write(rover::telemetry::LifeformTelemetryMessage(false));
						break;
					default:
						rover::telemetry::Logger::error("Unknown LifeformDetectorResponse");
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