/*
 * Sound.h
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#ifndef SOUND_H_
#define SOUND_H_

#include <iostream>
#include <SDL_mixer.h>


class Sound {
public:
	Sound();
	Sound(std::string file);
	Sound(std::string file, int channel);
	~Sound();

	void Play(int times);
	void Stop();
	void Open(std::string file);

    bool IsPlaying();

	void PlayFadein(int times, int fadeinTime);
private:
	Mix_Chunk* sound;
	int channel;

};

#endif /* SOUND_H_ */
