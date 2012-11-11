#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include "rover_commanding_CommandParser.h"
#include "rover_telemetry.h"

namespace rover
{
	namespace commanding
	{
		bool CommandParser::parseCommand(const String& commandText, Command& command) const
		{
			rover::telemetry::Logger::debug("Parsing command '" + commandText + "'");

			size_t commandTextLength = commandText.length();
			if(commandTextLength < 5)
			{
				rover::telemetry::Logger::debug("Command is too short");
				return false;
			}

			command._module[0] = commandText[0];
			command._module[1] = commandText[1];

			command._action[0] = commandText[3];
			command._action[1] = commandText[4];

			if(commandTextLength >= 8)
			{
				command._argument1[0] = commandText[6];
				command._argument1[1] = commandText[7];

				if(commandTextLength >= 11)
				{
					command._argument2[0] = commandText[9];
					command._argument2[1] = commandText[10];

					if(commandTextLength >= 14)
					{
						command._argument3[0] = commandText[12];
						command._argument3[1] = commandText[13];
					}
				}
			}

			return true;
		}
	}
}