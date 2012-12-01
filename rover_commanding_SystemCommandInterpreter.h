#pragma once

#include "rover_commanding_CommandInterpreter.h"

namespace rover
{
	namespace commanding
	{
		class SystemCommandInterpreter : public CommandInterpreter
		{
		public:
			SystemCommandInterpreter() { }

			virtual bool handle(const Command& command);
		};
	}
}