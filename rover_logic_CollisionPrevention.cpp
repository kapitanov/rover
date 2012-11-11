#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rover_logic_CollisionPrevention.h"
#include "rover_telemetry.h"

#include <stdlib.h>

namespace rover
{
	namespace logic
	{
		const unsigned long PROCESSING_PERIOD = 250; // ms

		const int LOW_LIMIT = 10; // sm
		const int CRITICAL_DISTANCE = 20; // sm

		const size_t MEASURES_COUNT = 3;
		const size_t MESSAGE_LENGTH = 110;

		CollisionPrevention::CollisionPrevention(
			rover::chassic::MobilePlatform& platform,
			const rover::chassic::RangingSensor& sensor)
			: _platform(platform), 
			_sensor(sensor), 
			_isEnabled(false)
		{ }

		void CollisionPrevention::enable(bool isEnabled)
		{
			_isEnabled = isEnabled;
			if(_isEnabled)
			{
				rover::telemetry::Logger::debug("Collision prevention enabled");
			}
			else
			{
				rover::telemetry::Logger::debug("Collision prevention disabled");
			}
		}

		bool CollisionPrevention::enabled() const
		{
			return _isEnabled;
		}

		void CollisionPrevention::handleEvents()
		{
			if(!_isEnabled)
			{
				return;
			}

			if(_platform.state() != rover::chassic::MPS_MOVING_FORWARD)
			{
				return;
			}
			
			handleEventsInternal();
		}

		void CollisionPrevention::handleEventsInternal()
		{
			// помер€ем рассто€ни€

			const unsigned int WRONG_VALUE = 0xFFFF;
			unsigned int measures[MEASURES_COUNT] = { };			
			for(size_t i = 0; i < MEASURES_COUNT; i++)
			{
				unsigned int distance;
				if(_sensor.measure(distance) != rover::chassic::RS_SUCCESS)
				{
					distance = WRONG_VALUE;
					rover::telemetry::Logger::error("CollisionPrevention: sensor failure");					
				}
				measures[i] = distance;
			}

			// фильтруем левоту
			unsigned int average_distance = 0;
			unsigned int dividor = 0;
			for(size_t i = 0; i < MEASURES_COUNT; i++)
			{
				unsigned int d = measures[i];
				if(d != WRONG_VALUE)
				{
					average_distance += d;
					dividor++;
				}
			}

			if(dividor == 0)
			{
				// цикл обосралс€
				return;
			}

			average_distance /= dividor;

			unsigned int disperse_limit = average_distance / 2;
			for(size_t i = 0; i < MEASURES_COUNT; i++)
			{
				unsigned int disperse = abs(measures[i] - average_distance);
				if(disperse >= disperse_limit)
				{
					measures[i] = WRONG_VALUE;
				}
			}

			// ищем преп€тстви€
			bool obstructions[MEASURES_COUNT] = { };
			unsigned char obstructions_count = 0;
			unsigned char valid_values_count = 0;

			for(size_t i = 0; i < MEASURES_COUNT; i++)
			{
				unsigned int distance = measures[i];
				if(distance != WRONG_VALUE)
				{
					valid_values_count++;

					if(distance >= LOW_LIMIT && 
						distance <= CRITICAL_DISTANCE)
					{
						obstructions_count++;
						obstructions[i] = true;
					}
					else
					{
						obstructions[i] = false;
					}
				}
				else
				{
					obstructions[i] = false;
				}
			}

			if(valid_values_count < 2)
			{
				// обху€рились по полной
				return;
			}

			// реакци€
			
			if(obstructions_count == valid_values_count)
			{
				rover::telemetry::Logger::warn("CollisionPrevention: obstruction ahead");			
				/*_platform.stop();

				char message[MESSAGE_LENGTH] = { };
				int offset = sprintf(message, "CollisionPrevention\nv/o = %d/%d\n", valid_values_count, obstructions_count);

				for(size_t i = 0; i < MEASURES_COUNT; i++)
				{
					offset += sprintf(message + offset, "d[%d] = %d sm; o = %c\n", i, measures[i], obstructions[i] ? 'T' : 'F');
				}

				message[offset - 1] = 0;
				rover::telemetry::Logger::debug(message);
				*/
			}
		}
	}
}

