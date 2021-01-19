#include"StopWatch.h"
#include<cmath>

namespace Pixel {
	namespace Time {

		float ToMilis(const float&);


		Stopwatch::Stopwatch()
			:
			start(-1),
			time_passed(0)
		{}

		void Stopwatch::Pause()
		{
			this->time_passed = std::clock() - this->start.point;
			this->start.point = -this->start.point;
		}

		void Stopwatch::Resume()
		{
			this->start = std::clock();
		}

		float Stopwatch::GetTimeElapsedMilis()
		{
			return ToMilis(this->time_passed + (std::clock() - this->start));
		}

		float Stopwatch::GetTimeElapsedSecs()
		{
			return ToMilis(this->time_passed + (std::clock() - this->start)) / 1000.0f;
		}

		void Stopwatch::Reset()
		{
			this->time_passed = 0;
			this->start = -abs(this->start.point);
		}

	}
}