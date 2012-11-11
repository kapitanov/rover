#pragma once

#include "rover_telemetry_TelemetryMessage.h"

namespace rover
{
	namespace telemetry
	{
		class DistanceTelemetryMessage : public TelemetryMessage
		{
		public:
			DistanceTelemetryMessage(const unsigned int distance);
			virtual ~DistanceTelemetryMessage() { }

			virtual void write(Stream& stream) const;

		private:
			const unsigned int _distance;
		};
	}
}