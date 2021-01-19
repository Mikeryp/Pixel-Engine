#pragma once
#include<ctime>
#define GetTime() (clock() / (float)CLOCKS_PER_SEC)

namespace PX {
	class FPS_Counter
	{
	private:
		float lastFrameTime;
		float currentFrameTime;
	public:

	public:
		FPS_Counter() : lastFrameTime(0), currentFrameTime(0) {}
		~FPS_Counter() {}

		double GetFPS() const
		{
			return 1.0 / (double)(currentFrameTime - lastFrameTime);
		}

		void Update()
		{
			this->lastFrameTime = currentFrameTime;
			this->currentFrameTime = (GetTime());
		}
	};

}

#undef GetTime()
