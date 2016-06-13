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
	~Sound();

	void Play(int times);
	void Stop();
	void Open(std::string file);
private:
	Mix_Chunk* sound;
	int channel;

};

#endif /* SOUND_H_ */
