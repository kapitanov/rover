#pragma once

namespace rover
{
	namespace chassic
	{
		enum MotorCommand 
		{ 
			MOTOR_FORWARD, 
			MOTOR_BACKWARD, 
			MOTOR_STOP, 
			MOTOR_BRAKE 
		};

		enum MotorSpeed
		{ 
			SPEED_100 = 255, 
			SPEED_75 = 191, 
			SPEED_50 = 17, 
			SPEED_25 = 64,
			SPEED_12 = 32,
		};

		class Motor
		{
		public:
			Motor(int pin1, int pin2);

			void stop();			
			void forward(MotorSpeed speed = SPEED_100);			
			void backward(MotorSpeed speed = SPEED_100);
			void brake();

			void execute(MotorCommand command, MotorSpeed speed = SPEED_100);

		private:
			int _pin1;
			int _pin2;

			void writeState(int state1, int state2);
		};
	}
}

