#pragma once

namespace rover
{
	namespace chassic
	{
		enum RangingSensorResponse { RS_SUCCESS, RS_ERROR };

		class RangingSensor
		{
		public:
			RangingSensor(int triggerPin, int echoPin);

			void initialize() const;

			RangingSensorResponse measure(unsigned int& distance) const;
			
		private:
			const int _triggerPin;
			const int _echoPin;
		};
	}
}
