#pragma once

#include "rover_telemetry_TelemetryMessage.h"

namespace rover
{
	namespace telemetry
	{
		class ChannelBase
		{
		public:
			virtual ~ChannelBase() { }
			
			virtual void initialize() = 0;
			virtual void write(const TelemetryMessage& message) = 0;
		};
	
		void initialize(ChannelBase& channel);

		extern ChannelBase* Channel;
	}
}