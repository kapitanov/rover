#pragma once

#include "rover_commanding_CommandInterpreter.h"
#include "rover_chassic.h"

namespace rover
{
	namespace commanding
	{
		class ChassicCommandInterpreter : public CommandInterpreter
		{
		public:
			ChassicCommandInterpreter(rover::chassic::MobilePlatform& platform);

			virtual bool handle(const Command& command);

		private:
			rover::chassic::MobilePlatform& _platform;

			static rover::chassic::MotorSpeed getMotorSpeed(const Command& command, rover::chassic::MotorSpeed defaultSpeed);
		};
	}
}