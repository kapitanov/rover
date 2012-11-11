#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_CompositeCommandInterpreter.h"

namespace rover
{
	namespace commanding
	{
		CompositeCommandInterpreter::CompositeCommandInterpreter(
			CommandInterpreter** interpreters, 
			const size_t count)
			: _interpreters(interpreters), _count(count)
		{ }

		bool CompositeCommandInterpreter::handle(const Command& command)
		{
			for(size_t i = 0; i < _count; i++)
			{
				CommandInterpreter& interpreter = *_interpreters[i];
				if(interpreter.handle(command))
				{
					return true;
				}
			}

			return false;
		}
	}
}