#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_CommandInterpreter.h"
#include "rover_commanding_CommandParser.h"

namespace rover
{
	namespace commanding
	{
		class CommandReader
		{
		public:
			CommandReader(Stream& stream, CommandInterpreter& interpreter);

			void handleEvents();
			
		private:
			Stream& _stream;
			CommandInterpreter& _interpreter;
			const CommandParser _parser;
			
			static const size_t BUFFER_SIZE = 32;
			char _buffer[BUFFER_SIZE];
			size_t _index;
			
			bool _canReceiveCommands;

			void clearBuffer();
			void handleCommand();
			void handleCommandCore();
		};
	}
}