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

Sound::Sound(std::string file, int channel){
	sound = nullptr;
	Open(file);
	channel = channel;
}

Sound::Sound(int channel){
	sound = nullptr;
	channel = channel;
}

void Sound::Play(int times){
//    if(channel != 0)
//        Mix_PlayChannel(channel, sound, times);
//    else
        channel = Mix_PlayChannel(-1,sound,times);

}
void Sound::Stop(){
	Mix_FadeOutChannel(channel, 1000);
}
void Sound::Stop(int numSeconds){
	Mix_FadeOutChannel(channel, numSeconds*1000);
}
void Sound::Open(std::string file){
	sound = Resources::GetSound(file);
}

void Sound::SetVolume(int volume){
    Mix_Volume(channel, volume);
}

void Sound::StereoPanning(int left, int right){
    Mix_SetPanning(channel, left, right);
}

void Sound::SoundPosition(int angle, int distance){
    Mix_SetPosition(channel, angle, distance);
}

void Sound::SetDistance(int dist){
    Mix_SetDistance(channel, dist);
}

void Sound::SetChannel(int channel){
    this->channel = channel;
}

void Sound::PlayArbitraryFadeIn(int times, int numSeconds){
    std::cout << "arb fadein" << std::endl;
    if(channel != 0 && !IsPlaying(channel))
       Mix_FadeInChannelTimed(channel, sound, times, 1000*numSeconds, 10000);
    else
        channel = Mix_FadeInChannelTimed(-1, sound, times, 1000*numSeconds, 10000);
}

bool Sound::IsPlaying(){
    return  Mix_Playing(channel);
}

bool Sound::IsPlaying(int someChannel){
    return  Mix_Playing(someChannel);
}
//
//void Sound::PlayFadein(int times, int fadeinTime){
//    channel = Mix_FadeInChannel(-1, this->sound, times, fadeinTime);
//}
