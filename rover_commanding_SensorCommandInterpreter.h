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
			SensorCommandInterpreter(
				rover::chassic::RangingSensor& rangingSensor,
				rover::chassic::LifeformDetector& lifeformDetector);

			virtual bool handle(const Command& command);

		private:
			rover::chassic::RangingSensor& _rangingSensor;
			rover::chassic::LifeformDetector& _lifeformDetector;
		};
	}
}