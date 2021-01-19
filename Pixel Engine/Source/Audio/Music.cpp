#include "Music.h"
#include"AudioManager.h"

namespace PX {
	namespace Audio {

		Music::Music()
		{
			this->handle = nullptr;
		}

		Music::Music(const std::string& file)
		{
			this->handle = AudioManager::StreamMusic(file, this->loop);
			gau_sample_source_loop_clear(this->loop);
		}

		Music::~Music()
		{
			ga_handle_destroy(this->handle);
		}

		void Music::create(const std::string& file)
		{
			this->handle = AudioManager::StreamMusic(file, this->loop);
			gau_sample_source_loop_clear(this->loop);
		}

		void Music::SetLoop(const bool& loop)
		{
			if (loop)
				gau_sample_source_loop_set(this->loop, -1, 0);
			else
				gau_sample_source_loop_clear(this->loop);

		}

		void Music::SetLoopPoints(const int& trigger, const int& target)
		{
			gau_sample_source_loop_set(this->loop, trigger, target); 
		}

	}
}