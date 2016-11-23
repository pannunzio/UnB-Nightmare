#include "Music.h"

Music::Music(){
    this->music = nullptr;
}

Music::Music(string file){
    this->Open(file);
}

void Music::Play(int times){
    if (Mix_PlayMusic(this->music, times) < 0){
        cout << "Mix_PlayMusic could not initialize! SDL_Error(): " << SDL_GetError() << endl;
    }
}

void Music::Stop(){
    Mix_FadeOutMusic(500);
}

void Music::Open(string file){
    this->music = Resources::GetMusic(file);
    if(this->music == nullptr){
        cout << "Music could not load! SDL_Error: " << SDL_GetError() << endl;
    }
}

bool Music::IsOpen(){
    return this->music != nullptr;
}

bool Music::IsPlaying(){
    return IsOpen() && Mix_PlayingMusic();
}
