#pragma once
#include<string>
#include "gorilla\ga.h"
#include "gorilla\gau.h"

#include"Playable.h"

namespace PX {
	namespace Audio {

		class Sound : public Playable
		{
			ga_Sound* sound;

		public:
			Sound();
			Sound(const std::string& path);
			~Sound();

			virtual void create(const std::string& path) override;
			virtual void SetLoop(const bool& loop) override;
		};

	}
}
