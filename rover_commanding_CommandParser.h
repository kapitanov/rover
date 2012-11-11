#pragma once

#include "rover_commanding_Command.h"

namespace rover
{
	namespace commanding
	{
		class CommandParser
		{
		public:
			bool parseCommand(const String& commandText, Command& command) const;
		};
	}
}