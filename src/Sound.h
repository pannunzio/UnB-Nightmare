#ifndef SOUND_H_
#define SOUND_H_

#include <iostream>
#include <SDL_mixer.h>
#include "Resources.h"

#define SOUND_ALL_CHANNELS    -1
#define SOUND_NO_CHANNEL      -2
#define SOUND_PLAY_INFINITY   -1
#define SOUND_FIRST_FREE_CHANNEL -1

#define SOUND_CHANNEL_1 1
#define SOUND_CHANNEL_2 2
#define SOUND_CHANNEL_3 3
#define SOUND_CHANNEL_4 4
#define SOUND_CHANNEL_5 5
#define SOUND_CHANNEL_6 6
#define SOUND_CHANNEL_7 7
#define SOUND_CHANNEL_8 8

class Sound {
public:
	Sound();
	Sound(int channel);
//	Sound(std::string file);
	Sound(std::string file, int channel);
	~Sound();

	void Play(int times);
	void Stop(int numSeconds = 0);
	void Open(std::string file, int channel);

	void SetVolume(int volume);
	void StereoPanning(int left, int right);
	void SoundPosition(int angle, int distance);
	void SetDistance(int dist);

    void SetChannel(int channel);

	void PlayArbitraryFadeIn(int times, int numSeconds);

	bool IsPlaying();
	bool IsPlaying(int channel);

private:
	Mix_Chunk* sound;
	int channel;

};

#endif
