#ifndef MUSIC_H
#define MUSIC_H

#include "SDL.h"
#include "SDL_mixer.h"

#include <iostream>
#include <string>

#include "Resources.h"

using std::cout;
using std::endl;
using std::string;

class Music{
public:
    Music();
    Music(string file);

    void Play(int times);
    void Stop();
    void Open(string file);
    bool IsOpen();
    bool IsPlaying();

private:
    Mix_Music* music;
};

#endif // MUSIC_H
