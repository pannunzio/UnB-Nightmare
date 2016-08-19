#include "Music.h"
#include "Resources.h"

const int ms = 100;

Music::Music() {
    music = NULL;
    volume = MIX_MAX_VOLUME;
    VolumeUpdate(volume);
}

Music::Music(string file) {
    Open(file);
}

void Music::Play (int times) {
    //se times == -1, a musica repete infinitamente
    int erro = Mix_PlayMusic(music, times);
    if(erro == -1){//se houve um erro
        cout << endl << "Erro em Music::Play(): Mix_PlayMusic() retornou -1" << endl;
        cout << SDL_GetError() << endl;
    }
}

void Music::Stop () {
    Mix_FadeOutMusic(ms);
}

void Music::Open (string file) {
//    if (IsOpen()){
//        Clear();
//    }

    Resources::GetMusic(file);

//    if (assetTable.find(file) != assetTable.end()){
//            music = assetTable.find(file)->second;
//    } else {
//
//        music = Mix_LoadMUS( file.c_str() );
//
//        if(music == NULL){
//            cout << endl << "Erro em Music::Open(): Mix_LoadMUS() retornou NULL" << endl;
//            cout << SDL_GetError() << endl;
//        }
//
//        assetTable.emplace(file, music);
//
//        #ifdef DEBUG
//        cout << "Music: " << file << " carregado - ";
//        cout << "MusicTableSize: " << assetTable.size() << endl;
//        #endif // DEBUG
//    }
}

bool Music::IsOpen () {
    if(music != NULL)
        return true;
    return false;
}

void Music::Clear()
{
    Resources::ClearMusic();

//    for(unordered_map<string, Mix_Music*>::iterator aux = assetTable.begin(); aux != assetTable.end(); aux++){
//            Mix_FreeMusic(aux->second);
//    }
//    assetTable.clear();
}

void Music::SetVolume(int volume) {
    this-> volume = Mix_VolumeMusic(volume);
}

void Music::VolumeUpdate (int increment) {
    if(volume + increment > MIX_MAX_VOLUME)
        volume = MIX_MAX_VOLUME;
    else if (volume + increment < 0)
        volume = 0;
    else
        this->volume = Mix_VolumeMusic( (this->volume) + increment ) + increment ;
}


//#include "Music.h"
//#include "Resources.h"
//
////Construtor 1
//Music::Music(){
//	music = nullptr;
//}
//
////Construtor 2
//Music::Music(std::string file){
//	music = nullptr;
//	Open(file);
//}
//
//Music::~Music(){
//	music = nullptr;
//}
//
//void Music::Open(std::string file){
//    music = Resources::GetMusic(file);
//    if(!music)
//        std::cout << "error na musica. SDL_error: " << Mix_GetError() << std::endl;
//}
//
//bool Music::IsOpen(){
//	return music == nullptr;
//}
//
//void Music::Play(int times){
//	Mix_PlayMusic(music,times);
//}
//
//void Music::Stop(){
//	//milisec
//	Mix_FadeOutMusic(0);
//}
//
//void Music::SetVolume(int newVolume){
//    Mix_VolumeMusic(newVolume);
//}
//
//Mix_Music* Music::GetMusic(){
//
//}
