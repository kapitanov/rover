#pragma once

#include "rover_telemetry_TelemetryMessage.h"

namespace rover
{
	namespace telemetry
	{
		class LifeformTelemetryMessage : public TelemetryMessage
		{
		public:
			LifeformTelemetryMessage(const bool detected);

			virtual ~LifeformTelemetryMessage() { }

			virtual void write(Stream& stream) const;

		private:
			const bool _detected;
		};
	}
}