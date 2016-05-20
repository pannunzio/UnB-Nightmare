/*
 * Sound.cpp
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#include "Sound.h"
#include "Resources.h"

Sound::Sound(){
	sound = nullptr;
	channel = 0;

}

Sound::~Sound(){
	//Stop();
}
Sound::Sound(std::string file){
	sound = nullptr;
	Open(file);
	channel = 0;
}

void Sound::Play(int times){
	channel = Mix_PlayChannel(-1,sound,times);

}
void Sound::Stop(){
	Mix_HaltChannel(channel);
}
void Sound::Open(std::string file){
	sound = Resources::GetSound(file);

}
