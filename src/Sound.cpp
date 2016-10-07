#include "Sound.h"
#include "Resources.h"

Sound::Sound(){
	this->sound = nullptr;
	this->channel = -5;
}

Sound::Sound(int channel){
	this->sound = nullptr;
	this->channel = channel;
}

//Sound::Sound(std::string file){
//	this->sound = nullptr;
//	Open(file);
//	this->channel = 0;
//}

Sound::Sound(std::string file, int channel){
	this->sound = nullptr;
	this->channel = channel;
	Open(file, this->channel);
}

Sound::~Sound(){
	//Stop();
}

void Sound::Play(int times){
    this->channel = Mix_PlayChannel(this->channel, this->sound, times);
}

void Sound::Stop(){
	Mix_FadeOutChannel(this->channel, 500);
}

void Sound::Stop(int numSeconds){
	Mix_FadeOutChannel(this->channel, numSeconds * 1000);
}

void Sound::Open(std::string file, int channel){
	this->sound = Resources::GetSound(file);
	this->channel = channel;
}

void Sound::SetVolume(int volume){
    Mix_Volume(this->channel, volume);
}

void Sound::StereoPanning(int left, int right){
    Mix_SetPanning(this->channel, left, right);
}

void Sound::SoundPosition(int angle, int distance){
    Mix_SetPosition(this->channel, angle, distance);
}

void Sound::SetDistance(int dist){
    Mix_SetDistance(this->channel, dist);
}

void Sound::SetChannel(int channel){
    this->channel = channel;
}

void Sound::PlayArbitraryFadeIn(int times, int numSeconds){
//    std::cout << "arb fadein" << std::endl;
    if(this->channel != 0 && !this->IsPlaying(this->channel))
       Mix_FadeInChannelTimed(this->channel, this->sound, times, 1000 * numSeconds, 10000);
    else
        this->channel = Mix_FadeInChannelTimed(-1, this->sound, times, 1000 * numSeconds, 10000);
}

bool Sound::IsPlaying(){
    return  Mix_Playing(channel);
}

bool Sound::IsPlaying(int someChannel){
    return  Mix_Playing(someChannel);
}
