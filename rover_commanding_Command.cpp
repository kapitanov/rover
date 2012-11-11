#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_Command.h"

namespace rover
{
	namespace commanding
	{
		bool Command::compareModule(const char value[2]) const
		{
			return compare(_module, value);
		}

		bool Command::compareAction(const char value[2]) const
		{
			return compare(_action, value);
		}

		bool Command::compareArgument1(const char value[2]) const
		{
			return compare(_argument1, value);
		}

		bool Command::compareArgument2(const char value[2]) const
		{
			return compare(_argument2, value);
		}

		bool Command::compareArgument3(const char value[2]) const
		{
			return compare(_argument3, value);
		}

		const char* Command::module() const 
		{ 
			return _module; 
		}

		const char* Command::action() const 
		{ 
			return _action;
		}

		const char* Command::argument1() const
		{
			return _argument1; 
		}

		const char* Command::argument2() const 
		{
			return _argument2;
		}

		const char* Command::argument3() const 
		{ 
			return _argument3; 
		}

		bool Command::compare(const char comparable[2], const char comparand[2])
		{
			return comparable[0] == comparand[0] && comparable[1] == comparand[1];
		}
	}
}