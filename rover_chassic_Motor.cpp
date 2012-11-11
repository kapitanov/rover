#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "rover_chassic_Motor.h"

namespace rover
{
	namespace chassic
	{
		Motor::Motor(int pin1, int pin2)
			: _pin1(pin1),
			  _pin2(pin2)
		{
			pinMode(pin1, OUTPUT);
			pinMode(pin2, OUTPUT);
		}

		void Motor::stop()
		{
			writeState(0, 0);
		}
		
		void Motor::forward(MotorSpeed speed)
		{
			writeState(static_cast<int>(speed), 0);
		}
		
		void Motor::backward(MotorSpeed speed)
		{
			writeState(0, static_cast<int>(speed));
		}

		void Motor::brake()
		{
			writeState(255, 255);
		}

		void Motor::execute(MotorCommand command, MotorSpeed speed)
		{
			switch (command)
			{
			case rover::chassic::MOTOR_FORWARD:
				forward(speed);
				break;
			case rover::chassic::MOTOR_BACKWARD:
				backward(speed);
				break;
			case rover::chassic::MOTOR_STOP:
				stop();
				break;
			case rover::chassic::MOTOR_BRAKE:
				brake();
				break;
			default:
				break;
			}
		}

		void Motor::writeState(int state1, int state2)
		{
			analogWrite(_pin1, state1);
			analogWrite(_pin2, state2);

			//digitalWrite(_pin1, state1);
			//digitalWrite(_pin2, state2);
		}
	}
}