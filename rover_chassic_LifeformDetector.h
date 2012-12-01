#pragma once

namespace rover
{
	namespace chassic
	{
		enum LifeformDetectorResponse { LFD_NOTHING_DETECTED, LFD_LIFEFORM_DETECTED };

		class LifeformDetector
		{
		public:
			LifeformDetector(int detectorPin);

			void initialize() const;

			LifeformDetectorResponse detect();
			
		private:
			const int _detectorPin;

			enum LifeformDetectorState { LDS_IDLE, LDS_DETECTED, LDS_NOT_DETECTED };

			LifeformDetectorState _state;

			LifeformDetectorResponse detectInternal() const;
		};
	}
}
