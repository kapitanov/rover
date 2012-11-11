#pragma once

#include "rover_chassic.h"

namespace rover
{
	namespace logic
	{
		class CollisionPrevention
		{
		public:
			CollisionPrevention(
				rover::chassic::MobilePlatform& platform,
				const rover::chassic::RangingSensor& sensor);

			void enable(bool isEnabled = true);

			bool enabled() const;

			void handleEvents();

		private:
			rover::chassic::MobilePlatform& _platform;
			const rover::chassic::RangingSensor& _sensor;			
			bool _isEnabled;

			void handleEventsInternal();
		};
	}
}

