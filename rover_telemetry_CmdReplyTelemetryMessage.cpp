#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "rover_telemetry_CmdReplyTelemetryMessage.h"

namespace rover
{
	namespace telemetry
	{
		const prog_uchar REPLY_SUCCESS[] PROGMEM = { "CMD_REPLY|OK\0" };
		const prog_uchar REPLY_FAILURE[] PROGMEM = { "CMD_REPLY|ERROR\0" };

		CmdReplyTelemetryMessage::CmdReplyTelemetryMessage(bool ok)
			: _ok(ok)
		{ }

		void CmdReplyTelemetryMessage::write(Stream& stream) const
		{
			const prog_uchar* message = _ok ? REPLY_SUCCESS : REPLY_FAILURE;
			writeFromFlash(stream, message);
		}
	}
}