#pragma once

namespace rover
{
	namespace commanding
	{
		class Command
		{
		public:
			bool compareModule(const char value[2]) const;
			bool compareAction(const char value[2]) const;
			bool compareArgument1(const char value[2]) const;
			bool compareArgument2(const char value[2]) const;
			bool compareArgument3(const char value[2]) const;

			const char* module() const;
			const char* action() const;
			const char* argument1() const;
			const char* argument2() const;
			const char* argument3() const;

		private:
			friend class CommandParser;

			char _module[2];
			char _action[2];
		    char _argument1[2];
			char _argument2[2];
			char _argument3[2];

			static bool compare(const char comparable[2], const char comparand[2]);
		};
	}
}