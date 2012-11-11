#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_CameraMountCommandInterpreter.h"
#include "rover_telemetry.h"

namespace rover
{
	namespace commanding
	{
		CameraMountCommandInterpreter::CameraMountCommandInterpreter(rover::chassic::CameraMount& cameraMount)
			: _cameraMount(cameraMount)
		{ }

		bool CameraMountCommandInterpreter::handle(const Command& command)
		{
			if(command.compareModule("CM"))
			{
				// CAMERA MOUNT
				if(command.compareAction("PR"))
				{
					// PAN RESET
					_cameraMount.panAbsolute(90);
					return true;
				}
				else if(command.compareAction("P+"))
				{
					// PAN+10
					_cameraMount.panRelaltive(10);
					return true;
				}
				else if(command.compareAction("P-"))
				{
					// PAN-10
					_cameraMount.panRelaltive(-10);
					return true;
				}
				else if(command.compareAction("TR"))
				{
					// TILT RESET
					_cameraMount.tiltAbsolute(90);
					return true;
				}
				else if(command.compareAction("T+"))
				{
					// TILT+10
					_cameraMount.tiltRelative(10);
					return true;
				}
				else if(command.compareAction("T-"))
				{
					// TILT-10
					_cameraMount.tiltRelative(-10);
					return true;
				}
				else
				{
					rover::telemetry::Logger::debug("Wrong CAMERAMOUNT command");
				}
			}

			return false;
		}
	}
}