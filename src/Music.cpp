#include "Music.h"
#include "Resources.h"

//Construtor 1
Music::Music(){
	music = nullptr;
}

//Construtor 2
Music::Music(std::string file){
	music = nullptr;
	Open(file);
}

Music::~Music(){
	Mix_FreeMusic(music);
	Resources::ClearMusic();
}

void Music::Open(std::string file){
    if(IsOpen())
        Mix_FreeMusic(music);

    music = Resources::GetMusic(file);

    if(!music)
        std::cout << "error na musica. SDL_error: " << Mix_GetError() << std::endl;
}

bool Music::IsOpen(){
	return music != nullptr;
}

void Music::Play(int times){
	Mix_PlayMusic(music,times);
}

void Music::Stop(){
	//milisec
	Mix_FadeOutMusic(0);
}

void Music::SetVolume(int newVolume){
    Mix_VolumeMusic(newVolume);
}
