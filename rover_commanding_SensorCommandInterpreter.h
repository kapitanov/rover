#pragma once

#include "rover_commanding_CommandInterpreter.h"
#include "rover_chassic.h"

namespace rover
{
	namespace commanding
	{
		class SensorCommandInterpreter : public CommandInterpreter
		{
		public:
			SensorCommandInterpreter(rover::chassic::RangingSensor& rangingSensor);

			virtual bool handle(const Command& command);

		private:
			rover::chassic::RangingSensor& _rangingSensor;
		};
	}
}