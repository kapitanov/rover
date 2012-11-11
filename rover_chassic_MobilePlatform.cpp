#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_chassic_MobilePlatform.h"
#include "rover_telemetry.h"

namespace rover
{
	namespace chassic
	{
		MobilePlatform::MobilePlatform (MobilePlatformConfig config)
			: _leftMotor(config.motorPins[0], config.motorPins[1]),
		      _rightMotor(config.motorPins[2], config.motorPins[3]),
			  _state(MPS_STOPPED)
		{ }

		void MobilePlatform::stop()
		{
			_leftMotor.stop();
			_rightMotor.stop();
			state(MPS_STOPPED);
		}

		void MobilePlatform::move(Movement movement, MotorSpeed speed)
		{
			switch (movement)
			{
			case rover::chassic::MOVE_FORWARD:
				runMotorCommand(MOTOR_FORWARD, MOTOR_FORWARD, speed);
				state(MPS_MOVING_FORWARD);
				break;
			case rover::chassic::MOVE_BACKWARD:
				runMotorCommand(MOTOR_BACKWARD, MOTOR_BACKWARD, speed);
				state(MPS_MOVING_BACKWARD);
				break;
			}
		}

		void MobilePlatform::rotate(Rotation rotation, MotorSpeed speed)
		{
			switch (rotation)
			{
			case rover::chassic::ROTATE_LEFT:
				runMotorCommand(MOTOR_BACKWARD, MOTOR_FORWARD, speed);
				state(MPS_ROTATING_LEFT);
				break;
			case rover::chassic::ROTATE_RIGHT:
				runMotorCommand(MOTOR_FORWARD, MOTOR_BACKWARD, speed);
				state(MPS_ROTATING_RIGHT);
				break;
			}
		}

		void MobilePlatform::brake()
		{
			_leftMotor.brake();
			_rightMotor.brake();
			state(MPS_STOPPED);
		}

		MobilePlatformState MobilePlatform::state() const
		{
			return _state;
		}

		void MobilePlatform::runMotorCommand(MotorCommand leftMotorCommand, MotorCommand rightMotorCommand, MotorSpeed speed)
		{
			_leftMotor.execute(leftMotorCommand, speed);
			_rightMotor.execute(rightMotorCommand, speed);
		}

		void MobilePlatform::state(MobilePlatformState state)
		{
			if(_state != state)
			{
				_state = state;
				const char* message = NULL;

				switch (_state)
				{
				case rover::chassic::MPS_STOPPED:
					message = "MobilePlatform.state = MPS_STOPPED";
					break;
				case rover::chassic::MPS_MOVING_FORWARD:
					message = "MobilePlatform.state = MPS_MOVING_FORWARD";
					break;
				case rover::chassic::MPS_MOVING_BACKWARD:
					message = "MobilePlatform.state = MPS_MOVING_BACKWARD";
					break;
				case rover::chassic::MPS_ROTATING_LEFT:
					message = "MobilePlatform.state = MPS_ROTATING_LEFT";
					break;
				case rover::chassic::MPS_ROTATING_RIGHT:
					message = "MobilePlatform.state = MPS_ROTATING_RIGHT";
					break;
				default:
					break;
				}

				if(message != NULL)
				{
					rover::telemetry::Logger::debug(message);
				}
			}
		}
	}
}