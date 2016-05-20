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

}
Music::~Music(){

}

void Music::Open(std::string file){

	music = Resources::GetMusic(file);
	if(!music)
		std::cout << "error na musica" << std::endl;

}

void Music::Play(int times){
	Mix_PlayMusic(music,times);
}

void Music::Stop(){
	//milisec
	Mix_FadeOutMusic(1*1000);
}

bool Music::IsOpen(){
	return music;
}

