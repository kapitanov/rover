#pragma once

#include "rover_telemetry_TelemetryMessage.h"
#include "rover_telemetry_LogSeverity.h"

namespace rover
{
	namespace telemetry
	{
		class CmdReplyTelemetryMessage : public TelemetryMessage
		{
		public:
			CmdReplyTelemetryMessage(bool ok);
			virtual ~CmdReplyTelemetryMessage() { }

			virtual void write(Stream& stream) const;

		private:
			bool _ok;
		};
	}
}