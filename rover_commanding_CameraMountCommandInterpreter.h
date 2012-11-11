#pragma once

#include "rover_commanding_CommandInterpreter.h"
#include "rover_chassic.h"

namespace rover
{
	namespace commanding
	{
		class CameraMountCommandInterpreter : public CommandInterpreter
		{
		public:
			CameraMountCommandInterpreter(rover::chassic::CameraMount& cameraMount);

			virtual bool handle(const Command& command);

		private:
			rover::chassic::CameraMount& _cameraMount;
		};
	}
}