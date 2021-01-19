#pragma once
#include<ctime>

namespace Pixel {
	namespace Time {
		namespace Time_Literals {

			float operator "" s(long double sec);
			float operator "" m(long double micro);

		}

		float getTimeMilis();

	}
}
