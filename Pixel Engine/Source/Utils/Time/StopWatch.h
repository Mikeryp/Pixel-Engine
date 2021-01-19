#pragma once
#include"TimeFuncs.h"
#include"Timepoint.h"

namespace Pixel {
	namespace Time {

		class Stopwatch
		{
			Timepoint start;

			float time_passed;
		public:
			Stopwatch();

			void Pause();
			void Resume();

			void Reset();

			float GetTimeElapsedMilis();
			float GetTimeElapsedSecs();
		};

	}
}
