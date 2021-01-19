#include"TimeFuncs.h"

namespace Pixel {
	namespace Time {
		namespace Time_Literals {

			float operator "" s(long double secs)
			{
				return secs * 1000;
			}
			
			float operator"" m(long double micros)
			{
				return micros / 1000;
			}
		}

		float getTimeMilis() { return (std::clock() / CLOCKS_PER_SEC) * 1000; }
	}
}