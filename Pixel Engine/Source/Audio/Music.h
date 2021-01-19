#pragma once
#include<string>
#include"Playable.h"

namespace PX {
	namespace Audio {

		class Music : public Playable
		{
		public:
			Music();
			Music(const std::string& file);
			~Music();

			virtual void create(const std::string& file) override;
			virtual void SetLoop(const bool& loop) override;
			void SetLoopPoints(const int& trigger, const int& target);
		};

	}
}
