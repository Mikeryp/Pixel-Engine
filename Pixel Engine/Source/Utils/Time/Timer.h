#pragma once
#include"Timepoint.h"

namespace Pixel {
	namespace Time {
		
		class Timer
		{
			Timepoint t;

			float time_remaining;
		public:

			Timer(const float& milisecs);
			Timer();

			void Start();
			void Stop();

			void ResetTimer(const float& milisecs);

			float GetRemainingSecs() const;
			float GetRemainingMilis() const;

			bool TimeUp() const;

		};

	}
}