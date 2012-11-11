#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_telemetry.h"
#include "rover_chassic_CameraMount.h"

namespace rover
{
	namespace chassic
	{
		CameraMount::CameraMount(int panServoPin, int tiltServoPin)
			: _panServoPin(panServoPin),
			_tiltServoPin(tiltServoPin)
		{
		}

		void CameraMount::initialize()
		{
			_panServo.attach(_panServoPin);
			_tiltServo.attach(_tiltServoPin);

			panAbsolute(90);
			tiltAbsolute(90);
		}

		void CameraMount::panAbsolute(int angle)
		{
			angle = clampAngle(angle);
			setServoAngle(_panServo, angle);
			_panAngle = angle;
			rover::telemetry::Logger::debug(String("camera_mount.pan ") + angle);
		}

		void CameraMount::tiltAbsolute(int angle)
		{
			angle = clampAngle(angle);
			setServoAngle(_tiltServo, angle);
			_tiltAngle = angle;
			rover::telemetry::Logger::debug(String("camera_mount.tilt ") + angle);
		}

		void CameraMount::panRelaltive(int angle)
		{
			panAbsolute(_panAngle + angle);
		}

		void CameraMount::tiltRelative(int angle)
		{
			tiltAbsolute(_tiltAngle + angle);
		}

		int CameraMount::clampAngle(int angle)
		{
			if(angle < 0)
			{
				return 0;
			}

			if(angle > 180)
			{
				return 180;
			}

			return angle;
		}

		void CameraMount::setServoAngle(Servo& servo, int angle)
		{
			servo.write(angle);
		}
	}
}
