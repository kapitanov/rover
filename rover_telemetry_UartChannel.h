#pragma once

#include "rover_telemetry_Channel.h"

namespace rover
{
	namespace telemetry
	{
		class UartChannel : public ChannelBase
		{
		public:
			UartChannel(int speed);

			virtual void initialize();

			virtual void write(const TelemetryMessage& message);

		private:
			int _speed;
		};
	}
}