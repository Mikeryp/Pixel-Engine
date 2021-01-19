#include"Timer.h"

#include<cmath>
#include"Math_Functions.h"

namespace Pixel {
	namespace Time {

		float ToMilis(const float& t)
		{
			return (t / CLOCKS_PER_SEC) * 1000.0f;
		}
			

		Timer::Timer(const float& milisecs)
			:
			time_remaining( (milisecs / 1000)* CLOCKS_PER_SEC),
			t(-1)
		{
		}

		Timer::Timer()
			:
			time_remaining(0),
			t(-1)
		{
		}


		void Timer::Start()
		{
			this->t = std::clock();
		}

		void Timer::Stop()
		{
			this->time_remaining -= std::clock() - this->t;

			this->t = -this->t.point;
		}



		void Timer::ResetTimer(const float& milisecs)
		{
			this->time_remaining = (milisecs / 1000.0f) * CLOCKS_PER_SEC;
			this->t = -1;
		}

		float Timer::GetRemainingSecs() const
		{
			if (this->t.point < 0.0f)
				return this->time_remaining;

			return ToMilis(this->time_remaining - (std::clock() - this->t.point)) / 1000.0f;
		}

		float Timer::GetRemainingMilis() const
		{
			if (this->t.point < 0.0f)
				return this->time_remaining;

			return ToMilis(this->time_remaining - (std::clock() - this->t.point));
		}

		bool Timer::TimeUp() const
		{
			if (this->t.point < 0.0f)
				return ToMilis(this->time_remaining) <= 0.0f;

			return ToMilis(this->time_remaining - (std::clock() - this->t.point)) <= 0.0f;
		}

	}
}