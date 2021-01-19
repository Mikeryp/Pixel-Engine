#include<string>

#include"Sound.h"
#include"AudioManager.h"

namespace PX {
	namespace Audio {

		Sound::Sound()
		{
			this->sound = nullptr;
			this->handle = nullptr;
		}

		Sound::Sound(const std::string& file)
		{
			this->sound = AudioManager::RequestSound(file);
			this->handle = gau_create_handle_sound(AudioManager::GetMixer(), this->sound, &gau_on_finish_destroy, 0, &this->loop);
			gau_sample_source_loop_clear(this->loop);
		}

		Sound::~Sound()
		{
			ga_handle_destroy(this->handle);
			ga_sound_release(this->sound);
		}

		
		void Sound::create(const std::string& path)
		{
			this->sound = AudioManager::RequestSound(path);
			this->handle = gau_create_handle_sound(AudioManager::GetMixer(), this->sound, &gau_on_finish_destroy, 0, &this->loop);
			gau_sample_source_loop_clear(this->loop);
		}

		void Sound::SetLoop(const bool& loop)
		{
			if (loop)
				gau_sample_source_loop_set(this->loop, -1, 0);
			else
				gau_sample_source_loop_clear(this->loop);
		}

	}
}