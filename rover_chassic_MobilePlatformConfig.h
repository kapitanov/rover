#pragma once

namespace rover
{
	namespace chassic
	{
		struct MobilePlatformConfig
		{
		public:
			MobilePlatformConfig(
				int motor1Pin1,
				int motor1Pin2,
				int motor2Pin1,
				int motor2Pin2);

			int motorPins[4];
		};
	}
}