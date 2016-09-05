#ifndef SOUND_H_
#define SOUND_H_

#include <iostream>
#include <SDL_mixer.h>

class Sound {
public:
	Sound();
	Sound(int channel);
	Sound(std::string file);
	Sound(std::string file, int channel);
	~Sound();

	void Play(int times);
	void Stop();
	void Stop(int numSeconds);
	void Open(std::string file);

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
