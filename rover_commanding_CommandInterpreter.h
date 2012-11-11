#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_Command.h"

namespace rover
{
	namespace commanding
	{
		class CommandInterpreter
		{
		public:
			virtual ~CommandInterpreter() { }

			virtual bool handle(const Command& command) = 0;
		};
	}
}