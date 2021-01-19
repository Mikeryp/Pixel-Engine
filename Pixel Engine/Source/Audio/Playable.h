#pragma once
#include<gorilla/ga.h>
#include<gorilla/gau.h>

#include<cmath>

#define SAMPLES_PER_SEC 44100

namespace PX {
	namespace Audio {

		class AudioManager;


		class Playable
		{
		protected:
			ga_Handle* handle;
			gau_SampleSourceLoop* loop;

		protected:
			Playable() = default;
			virtual ~Playable() { ga_handle_destroy(this->handle); }

		public:

			virtual void SetLoop(const bool& loop) = 0;
			virtual void create(const std::string& path) = 0;

			virtual void stop() {
				ga_handle_seek(this->handle, 0);
				ga_handle_stop(this->handle);
			}

			virtual void play() { ga_handle_play(this->handle); }
			virtual void pause() { ga_handle_stop(handle); }
			virtual void SetGain(const float& gain) { ga_handle_setParamf(handle, GA_HANDLE_PARAM_GAIN, gain); }
			virtual void SetPitch(const float& pitch) { ga_handle_setParamf(handle, GA_HANDLE_PARAM_PITCH, pitch); }
			virtual void SetPan(const float& pan) { ga_handle_setParamf(handle, GA_HANDLE_PARAM_PAN, pan); }
			virtual void seek(const float& secs) { ga_handle_seek(this->handle, floor(secs * SAMPLES_PER_SEC)); }
		};

	}
}