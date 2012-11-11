#pragma once

#include "rover_chassic_Motor.h"
#include "rover_chassic_MobilePlatformConfig.h"

namespace rover
{
	namespace chassic
	{
		enum Rotation { ROTATE_LEFT, ROTATE_RIGHT };
		enum Movement { MOVE_FORWARD, MOVE_BACKWARD };

		enum MobilePlatformState
		{
			MPS_STOPPED,
			MPS_MOVING_FORWARD,
			MPS_MOVING_BACKWARD,
			MPS_ROTATING_LEFT,
			MPS_ROTATING_RIGHT
		};

		class MobilePlatform
		{
		public:

			MobilePlatform(MobilePlatformConfig config);

			void stop();

			void move(Movement movement, MotorSpeed speed = SPEED_50);
			void rotate(Rotation rotation, MotorSpeed speed = SPEED_75);

			void brake();

			MobilePlatformState state() const;

		private:
			Motor _leftMotor;
			Motor _rightMotor;

			MobilePlatformState _state;
						
			void runMotorCommand(MotorCommand leftMotorCommand, MotorCommand rightMotorCommand, MotorSpeed speed);
			void state(MobilePlatformState state);
		};
	}
}
