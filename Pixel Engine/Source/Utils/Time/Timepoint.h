#pragma once
#include<ctime>

namespace Pixel {

	namespace Time {

		struct Timepoint
		{
			time_t point;

			Timepoint()
			{
				this->point = std::clock();
			}

			Timepoint(const float& time_point)
			{
				this->point = time_point;
			}

			float GetMilisecsPassed() { return ((float)(std::clock() - this->point) / CLOCKS_PER_SEC) * 1000; }

			void operator = (const time_t& timepoint) { this->point = timepoint; }

			time_t operator + (const time_t& t) const { return this->point + t; }
			float operator + (const float& t) const { return (float)this->point + t; }

			time_t operator - (const time_t& t) const { return this->point - t; }
			float operator - (const float& t) const { return (float)this->point - t; }

			time_t operator * (const time_t& t) const { return this->point * t; }
			float operator * (const float& t) const { return (float)this->point * t; }

			time_t operator / (const time_t& t) const { return this->point / t; }
			float operator / (const float& t) const { return (float)this->point / t; }

			operator float() { return (float)this->point; }
		};  
	}
}