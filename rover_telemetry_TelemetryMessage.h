#pragma once

class Stream;

#include <avr/pgmspace.h>

namespace rover
{
	namespace telemetry
	{
		class TelemetryMessage
		{
		public:
			virtual ~TelemetryMessage() { }

			virtual void write(Stream& stream) const = 0;

		protected:
			void writeFromFlash(Stream& stream, const prog_uchar* buffer) const;
		};
	}
}