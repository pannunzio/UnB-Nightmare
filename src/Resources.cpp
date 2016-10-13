#include "Resources.h"
#include "Game.h"
#include <sstream>

std::unordered_map<string, SDL_Texture*> Resources::imageTable;
std::unordered_map<string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<string, TTF_Font*> Resources::fontTable;

SDL_Texture* Resources::GetImage(string file){
    std::unordered_map<string, SDL_Texture*>::const_iterator indice = imageTable.find(file);

    if (indice == imageTable.end()){
        SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        imageTable.emplace(file, texture);
        return texture;
    } else {
        return indice->second;
    }
    return nullptr;
};

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

void Resources::ClearImages(){
    imageTable.clear();
}

void Resources::ClearSound(){
    for(std::unordered_map<string, Mix_Chunk*>::const_iterator index = soundTable.begin(); index != soundTable.end(); index++){
            Mix_FreeChunk(index->second);
    }
    soundTable.clear();
}

void Resources::ClearFonts(){
    for(std::unordered_map<string, TTF_Font*>::const_iterator index = fontTable.begin(); index != fontTable.end(); index++){
            TTF_CloseFont(index->second);
    }
    fontTable.clear();
}

void Resources::PrintLoadedFonts(){
    int cont = 0;
    cout << endl << "\t*********** LOADED FONTS *************" << endl;
    for(std::unordered_map<string, TTF_Font*>::const_iterator index = fontTable.begin(); index != fontTable.end(); index++){
        cout << cont << " - " << index->first << endl;
        cont++;
    }
    cout << endl;
}

void Resources::PrintLoadedSounds(){
    int cont = 0;
    cout << endl << "\t*********** LOADED SOUNDS *************" << endl;
    for(std::unordered_map<string, Mix_Chunk*>::const_iterator index = soundTable.begin(); index != soundTable.end(); index++){
        cout << cont << " - " << index->first << endl;
        cont++;
    }
    cout << endl;
}

void Resources::PrintLoadedImages(){
    int cont = 0;
    cout << endl << "\t*********** LOADED IMAGES *************" << endl;
    for(std::unordered_map<string, SDL_Texture*>::const_iterator index = imageTable.begin(); index != imageTable.end(); index++){
        cout << cont << " - " << index->first << endl;
        cont++;
    }
    cout << endl;
}

void Resources::PrintAllLoadedResources(){
    int cont = 0;
    cout << endl << "\t*********** ALL LOADED ITEMS *************" << endl;
    cout << endl << "\t ---> LOADED IMAGES" << endl;
    for(std::unordered_map<string, SDL_Texture*>::const_iterator index = imageTable.begin(); index != imageTable.end(); index++){
        cout << cont << " - " << index->first << endl;
        cont++;
    }
    cont = 0;
    cout << endl << "\t ---> LOADED SOUNDS" << endl;
    for(std::unordered_map<string, Mix_Chunk*>::const_iterator index = soundTable.begin(); index != soundTable.end(); index++){
        cout << cont << " - " << index->first << endl;
        cont++;
    }
    cont = 0;
    cout << endl << "\t ---> LOADED FONTS" << endl;
    for(std::unordered_map<string, TTF_Font*>::const_iterator index = fontTable.begin(); index != fontTable.end(); index++){
        cout << cont << " - " << index->first << endl;
        cont++;
    }
}
