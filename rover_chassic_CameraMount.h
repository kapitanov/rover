#pragma once

#include "servo.h"

namespace rover
{
	namespace chassic
	{
		class CameraMount
		{
		public:
			CameraMount(int panServoPin, int tiltServoPin);

			void initialize();

			void panAbsolute(int angle);
			void tiltAbsolute(int angle);

			void panRelaltive(int angle);
			void tiltRelative(int angle);

		private:
			int _panServoPin;
			int _tiltServoPin;

			int _panAngle;
			int _tiltAngle;

			Servo _panServo;
			Servo _tiltServo;

			int clampAngle(int angle);
			void setServoAngle(Servo& servo, int angle);
		};
	}
}
