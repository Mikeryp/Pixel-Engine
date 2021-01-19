/*
	@Info :- Audio Manager and Mixer for handling audio resources.
*/

#pragma once

#include<map>
#include<gorilla\ga.h>
#include<gorilla\gau.h>

namespace PX {
	namespace Audio {

		class AudioManager
		{
			static gau_Manager* manager;
			static ga_Mixer* mixer;
			static ga_StreamManager* stream_manager;
			static ga_Device* device;

			static std::map<std::string, std::pair<ga_Sound*, char>> audio;

		public:
			AudioManager() = delete;
			~AudioManager() = delete;

			static void Init();
			static void Update();
			static ga_Sound* RequestSound(const std::string& file);
			static ga_Handle* StreamMusic(const std::string& file, gau_SampleSourceLoop*& loop_handler);
			static void FreeSound(const std::string& file);
			static void CleanUp();

			static ga_StreamManager* GetStreamManager() { return AudioManager::stream_manager; }
			static ga_Mixer* GetMixer() { return AudioManager::mixer; }
		};

	}
}
