/*
 * Music.h
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#include "SDL_mixer.h"
#include <iostream>
#include <unordered_map>
#include <string>

using std::string;

class Music {
public:
	Music();
	~Music();
	Music(std::string music);
	void Play(int times);
	void Stop();
	void Open(std::string file);
	bool IsOpen();
	Mix_Music* GetMusic();

    string GetCurrentTrack();

	void SetVolume(int newVolume);
private:
	Mix_Music* music;
    string currentTrack;
};

#endif /* MUSIC_H_ */
