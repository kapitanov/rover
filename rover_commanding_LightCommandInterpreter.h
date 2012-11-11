#pragma once

#include "rover_commanding_CommandInterpreter.h"
#include "rover_chassic.h"

namespace rover
{
	namespace commanding
	{
		class LightCommandInterpreter : public CommandInterpreter
		{
		public:
			LightCommandInterpreter(rover::chassic::LightEmitter& frontLight);

			virtual bool handle(const Command& command);

		private:
			rover::chassic::LightEmitter& _frontLight;
		};
	}
}

