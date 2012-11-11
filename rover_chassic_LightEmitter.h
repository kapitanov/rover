#pragma once

namespace rover
{
	namespace chassic
	{
		class LightEmitter
		{
		public:
			LightEmitter(const int pin);

			bool enabled() const;
			void enable(bool isEnabled = true);

		private:
			const int _pin;
			bool _isEnabled;
		};
	}
}

