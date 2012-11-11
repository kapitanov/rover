#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_telemetry_Channel.h"

namespace rover
{
	namespace telemetry
	{
		ChannelBase* Channel;

		void initialize(ChannelBase& channel)
		{
			Channel = &channel;
			channel.initialize();
		}
	}
}