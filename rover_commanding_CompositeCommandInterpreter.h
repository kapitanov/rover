#pragma once

#include "rover_commanding_commandinterpreter.h"

namespace rover
{
	namespace commanding
	{
		class CompositeCommandInterpreter : public CommandInterpreter
		{
		public:
			CompositeCommandInterpreter(CommandInterpreter** interpreters, const size_t count);

			virtual bool handle(const Command& command);

		private:
			CommandInterpreter** const _interpreters;
			const size_t _count;
		};
	}
}