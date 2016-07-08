/*
 * Music.cpp
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#include "Music.h"
#include "Resources.h"

Music::Music(){
	music = nullptr;
}
Music::Music(std::string file){
	music = nullptr;
	Open(file);
	Mix_VolumeMusic(9);
}
Music::~Music(){
	music = nullptr;

}

void Music::Open(std::string file){
//    if(!this->IsOpen()){
        music = Resources::GetMusic(file);
        Mix_VolumeMusic(9);
        if(!music)
            std::cout << "error na musica. SDL_error: " << Mix_GetError() << std::endl;
//    }
}

void Music::Play(int times){
	Mix_PlayMusic(music,times);
}

void Music::Stop(){
	//milisec
	Mix_FadeOutMusic(1000);
}

bool Music::IsOpen(){
	return music;
}

void Music::SetVolume(int newVolume){
    Mix_VolumeMusic(newVolume);
}
