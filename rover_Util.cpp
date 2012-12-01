#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_util.h"

namespace rover
{
	typedef void (*ResetFunc)();

	static ResetFunc _NativeReset = 0;

	void Util::softReset()
	{
		_NativeReset();
	}
}
