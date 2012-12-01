#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_SystemCommandInterpreter.h"
#include "rover_telemetry.h"
#include "rover_Util.h"

namespace rover
{
	namespace commanding
	{
		bool SystemCommandInterpreter::handle(const Command& command)
		{
			if(command.compareModule("SS"))
			{
				// RESET
				if(command.compareAction("RS"))
				{
					// SOFT RESET
					if(command.compareArgument1("ST"))
					{
						rover::Util::softReset();
						return true;
					}
				}
				else
				{
					rover::telemetry::Logger::debug("Wrong SYSTEM command");
				}
			}

			return false;
		}
	}
}