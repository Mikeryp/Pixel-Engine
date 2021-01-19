#include"AudioManager.h"

namespace PX {
	namespace Audio {

		// Returns the extension of the file requested to be played.
		std::string GetExtension(const std::string& file)
		{
			return file.substr(file.size() - 3, 3);
		}



		gau_Manager* AudioManager::manager;
		ga_Mixer* AudioManager::mixer;
		ga_StreamManager* AudioManager::stream_manager;
		ga_Device* AudioManager::device;

		std::map<std::string, std::pair<ga_Sound*, char>> AudioManager::audio;


		void AudioManager::Init()
		{
			gc_initialize(0);

			AudioManager::manager = gau_manager_create();
			AudioManager::mixer = gau_manager_mixer(AudioManager::manager);
			AudioManager::device = gau_manager_device(AudioManager::manager);
			AudioManager::stream_manager = gau_manager_streamManager(AudioManager::manager);
		}

		void AudioManager::Update()
		{
			gau_manager_update(AudioManager::manager);
		}

		ga_Sound* AudioManager::RequestSound(const std::string& file)
		{
			// If the sound already exists, increase the reference count.
			if (AudioManager::audio.find(file) != AudioManager::audio.end())
			{
				AudioManager::audio[file].second++;
				return AudioManager::audio[file].first;
			}

			// If the audio doesnt exist, load the sound.
			AudioManager::audio[file] = std::make_pair(gau_load_sound_file(file.c_str(), GetExtension(file).c_str()), 1);
			return AudioManager::audio[file].first;
		}

		ga_Handle* AudioManager::StreamMusic(const std::string& file,gau_SampleSourceLoop*& loop_handler)
		{
			ga_Handle* handle = gau_create_handle_buffered_file(AudioManager::mixer, AudioManager::stream_manager, file.c_str(), GetExtension(file).c_str(), 0, 0, &loop_handler);
			return handle;
		}

		void AudioManager::FreeSound(const std::string& file)
		{
			// Decrease the reference count.
			if (--AudioManager::audio[file].second <= 0)
			{
				// If the reference count is 0, no handles for this audio are in use.
				// freeing the audio.
				ga_sound_release(AudioManager::audio[file].first);
				AudioManager::audio.erase(file);
			}
		}

		void AudioManager::CleanUp()
		{
			gau_manager_destroy(AudioManager::manager);
			gc_shutdown();
		}
	}
}