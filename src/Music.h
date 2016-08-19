#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL_mixer.h>

using std::string;
using std::unordered_map;
using std::iterator;
using std::cout;
using std::endl;

class Music
{
    public:
        Music ();
        Music (string file);
        void Play (int times);
        void Stop ();
        void Open (string file);
        bool IsOpen ();
        static void Clear ();

        void SetVolume (int volume);
        void VolumeUpdate (int increment);

    protected:
        /* vazio */
    private:
        int volume;
        string file;
        Mix_Music* music;
        static unordered_map<string, Mix_Music*> assetTable;
};

#endif



//#ifndef MUSIC_H_
//#define MUSIC_H_
//
//#include "SDL_mixer.h"
//#include <iostream>
//#include <unordered_map>
//
//class Music {
//public:
//	Music();
//	Music(std::string music);
//	~Music();
//
//	void Open(std::string file);
//	bool IsOpen();
//
//	void Play(int times);
//	void Stop();
//
//	void SetVolume(int newVolume);
//
//private:
//	Mix_Music* music;
//
//};
//
//#endif
