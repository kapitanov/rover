#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_ChassicCommandInterpreter.h"
#include "rover_telemetry.h"

namespace rover
{
	namespace commanding
	{
		ChassicCommandInterpreter::ChassicCommandInterpreter(rover::chassic::MobilePlatform& platform)
			: _platform(platform)
		{ }

		bool ChassicCommandInterpreter::handle(const Command& command)
		{
			if(command.compareModule("CH"))
			{
				// CHASSIC
				if(command.compareAction("MV"))
				{
					// MOVE
					if(command.compareArgument1("FW"))
					{
						// FORWARD
						_platform.move(rover::chassic::MOVE_FORWARD, getMotorSpeed(command, rover::chassic::SPEED_75));
						return true;
					}

					if(command.compareArgument1("BW"))
					{
						// FORWARD
						_platform.move(rover::chassic::MOVE_BACKWARD, getMotorSpeed(command, rover::chassic::SPEED_75));
						return true;
					}

					rover::telemetry::Logger::debug("Wrong CHASSIC MOVE command");
				}
				else if(command.compareAction("RT"))
				{
					// ROTATE
					if(command.compareArgument1("TL"))
					{
						// LEFT
						_platform.rotate(rover::chassic::ROTATE_LEFT, getMotorSpeed(command, rover::chassic::SPEED_75));
						return true;
					}

					if(command.compareArgument1("TR"))
					{
						// FORWARD
						_platform.rotate(rover::chassic::ROTATE_RIGHT, getMotorSpeed(command, rover::chassic::SPEED_75));
						return true;
					}

					rover::telemetry::Logger::debug("Wrong CHASSIC ROTATE command");
				}
				else if(command.compareAction("ST"))
				{
					// STOP
					_platform.stop();
					return true;
				}
				else if(command.compareAction("BR"))
				{
					// BRAKE
					_platform.brake();
					return true;
				}
				else
				{
					rover::telemetry::Logger::debug("Wrong CHASSIC command");					
				}

				return false;
			}
		}

		rover::chassic::MotorSpeed ChassicCommandInterpreter::getMotorSpeed(const Command& command, rover::chassic::MotorSpeed defaultSpeed)
		{
			if(command.compareArgument2("FF"))
			{
				return rover::chassic::SPEED_100;
			}

			if(command.compareArgument2("C0"))
			{
				return rover::chassic::SPEED_75;
			}

			if(command.compareArgument2("80"))
			{
				return rover::chassic::SPEED_50;
			}

			if(command.compareArgument2("40"))
			{
				return rover::chassic::SPEED_25;
			}

			if(command.compareArgument2("20"))
			{
				return rover::chassic::SPEED_12;
			}

			return defaultSpeed;
		}
	}
}