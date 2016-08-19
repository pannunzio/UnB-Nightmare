#include "Resources.h"
#include "Game.h"
#include <sstream>

//using std::make_shared;

std::unordered_map<string, SDL_Texture*> Resources::imageTable;
std::unordered_map<string, Mix_Music*> Resources::musicTable;
std::unordered_map<string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<string, TTF_Font*> Resources::fontTable;
//std::unordered_map<string, shared_ptr<SDL_Texture*>> Resources::imageTable;

SDL_Texture* Resources::GetImage(string file){
    std::unordered_map<string, SDL_Texture*>::const_iterator indice = imageTable.find(file);
//    std::unordered_map<string, shared_ptr<SDL_Texture*>>::const_iterator indice = imageTable.find(file);
    if (indice == imageTable.end()){
        SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
//        shared_ptr<SDL_Texture*> texture = make_shared<SDL_Texture*> (IMG_LoadTexture(Game::GetInstance().GetRenderer(), file));
        imageTable.emplace(file, texture);
        return texture;
    } else {
        return indice->second;
    }
    return nullptr;
};

void Resources::ClearImages(){
    imageTable.clear();
};

Mix_Music* Resources::GetMusic(string file){
    std::unordered_map<string, Mix_Music*>::const_iterator indice = musicTable.find(file);
    if (indice == musicTable.end()){
        Mix_Music* music = Mix_LoadMUS(file.c_str());
        musicTable.emplace(file, music);
        return music;
    } else {
        return indice->second;
    }
    return nullptr;
}

void Resources::ClearMusic(){
    for(std::unordered_map<string, Mix_Music*>::const_iterator index = musicTable.begin(); index != musicTable.end(); index++){
            Mix_FreeMusic(index->second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file){
    std::unordered_map<string, Mix_Chunk*>::const_iterator indice = soundTable.find(file);
    if (indice == soundTable.end()){
        Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
        soundTable.emplace(file, chunk);
        return chunk;
    } else {
        return indice->second;
    }
    return nullptr;
}

void Resources::ClearSound(){
    for(std::unordered_map<string, Mix_Chunk*>::const_iterator index = soundTable.begin(); index != soundTable.end(); index++){
            Mix_FreeChunk(index->second);
    }
    soundTable.clear();
}

TTF_Font* Resources::GetFont(string file, int fontSize){
    std::stringstream chave;
    chave << file << fontSize;
    std::unordered_map<string, TTF_Font*>::const_iterator indice = fontTable.find(chave.str());

    if (indice == fontTable.end()){
        TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
        fontTable.emplace(chave.str(), font);
        return font;
    } else {
        return indice->second;
    }
    return nullptr;
}

void Resources::ClearFonts(){
    for(std::unordered_map<string, TTF_Font*>::const_iterator index = fontTable.begin(); index != fontTable.end(); index++){
            TTF_CloseFont(index->second);
    }
    fontTable.clear();
}
