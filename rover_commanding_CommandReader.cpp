#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_commanding_CommandReader.h"
#include "rover_telemetry.h"

namespace rover
{
	namespace commanding
	{
		CommandReader::CommandReader(Stream& stream, CommandInterpreter& interpreter) 
			: _stream(stream), _interpreter(interpreter), _index(0), _canReceiveCommands(false), _parser()
		{ }

		void CommandReader::handleEvents()
		{
			if(!_canReceiveCommands)
			{
				_canReceiveCommands = true;
				clearBuffer();
			}
			
			while(_stream.available() > 0)
			{
				if(_index >= BUFFER_SIZE)
				{
					handleCommand();
				}

				char item = _stream.read();
				if(item == '\n')
				{
					handleCommand();
					break;
				}

				_buffer[_index] = item;
				_index++;
			}
		}

		void CommandReader::handleCommand()
		{
			handleCommandCore();

			clearBuffer();
		}
		
		void CommandReader::handleCommandCore()
		{
			String commandText(_buffer);
			rover::telemetry::Logger::debug("command received");

			Command command;
			if(_parser.parseCommand(commandText, command))
			{
				if(_interpreter.handle(command))
				{
					rover::telemetry::Channel->write(rover::telemetry::CmdReplyTelemetryMessage(true));
					return;
				}
				else
				{
					rover::telemetry::Logger::warn("unknown command");
				}				
			}
			else
			{				
				rover::telemetry::Logger::warn("wrong command format");
			}

			rover::telemetry::Channel->write(rover::telemetry::CmdReplyTelemetryMessage(false));
		}

		void CommandReader::clearBuffer()
		{
			for(size_t i = 0; i < BUFFER_SIZE; i++)
			{
				_buffer[i] = '\0';
			}

			_index = 0;
			
			if(_canReceiveCommands)
			{
				rover::telemetry::Logger::info("ready to receive command");
			}
		}
	}
}