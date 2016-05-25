/*
 * Resources.cpp
 *
 *  Created on: 23 de mar de 2016
 *      Author: Caio
 */

#include "Resources.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include <string>
#include <sstream>
// inicializando
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;
std::unordered_map<int, Text*> Resources::numbersTable;

Resources::Resources() {

}
//*********************************************************************//
//Função: Resources::GetImage(string file)**********************************************//
//Retorno: SDL_Texture*******************************************************//
//Parametros: string file**************************************************//
//Descrição: procura se imagem ja esta no tablemap, caso nao, insere***************************************//
//****************************************************************//
SDL_Texture* Resources::GetImage(std::string file){

	auto busca = imageTable.find(file);
	if(busca != imageTable.end()){
		return busca->second;
	}
	SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
	if(!renderer)
			std::cout << "renderer bugado" << std::endl;
	SDL_Texture* texture = IMG_LoadTexture(renderer,file.c_str()); // precisa ser const char
	if(!texture)
		std::cout << "Error ao carregar texture do resources" << std::endl;
	imageTable.emplace(file,texture);
	return texture;
}
//*********************************************************************//
//Função: Resources::ClearImages()************************************//
//Retorno: void******************************************************//
//Parametros: void**************************************************//
//Descrição: destroi texture por texture***************************//
//****************************************************************//
void Resources::ClearImages(){
	for (std::unordered_map<std::string, SDL_Texture*>::iterator it = imageTable.begin(); it != imageTable.end(); ++it)
		SDL_DestroyTexture(it->second);
	imageTable.clear();
}
Resources::~Resources() {

}



void Resources::ClearMusic(){
	for (std::unordered_map<std::string, Mix_Music*>::iterator it = musicTable.begin(); it != musicTable.end(); ++it)
		Mix_FreeMusic(it->second);
	musicTable.clear();

}

Mix_Music* Resources::GetMusic(std::string file) {
	auto busca = musicTable.find(file);
	if(busca != musicTable.end()){
		return busca->second;
	}

	Mix_Music* music = Mix_LoadMUS(file.c_str()); // precisa ser const char
	if(!music)
		std::cout << "Error ao carregar texture do resources" << std::endl;
	musicTable.emplace(file,music);
	return music;
}

void Resources::ClearSound(){
	for (std::unordered_map<std::string, Mix_Chunk*>::iterator it = soundTable.begin(); it != soundTable.end(); ++it)
		Mix_FreeChunk(it->second);
	soundTable.clear();

}

Mix_Chunk* Resources::GetSound(std::string file) {
	auto busca = soundTable.find(file);
	if(busca != soundTable.end()){
		return busca->second;
	}
	Mix_Chunk* sound = Mix_LoadWAV(file.c_str()); // precisa ser const char
	if(!sound)
		std::cout << "Error ao carregar sound do resources" << std::endl;
	soundTable.emplace(file,sound);
	return sound;
}


void Resources::ClearFont(){
	for (std::unordered_map<std::string, TTF_Font*>::iterator it = fontTable.begin(); it != fontTable.end(); ++it)
	   TTF_CloseFont(it->second);
	fontTable.clear();

}

TTF_Font* Resources::GetFont(std::string file, int fontSize) {
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

Text* Resources::GetNumber(int number){
    std::unordered_map<int, Text*>::const_iterator indice = numbersTable.find(number);
    if (indice == numbersTable.end()){
        std::stringstream numero;
        numero << number;
        Text* text = new Text("font/Sketch College.ttf", 40, BLENDED, numero.str(), TEXT_WHITE, 980, 20);
        numbersTable.emplace(number, text);
        return text;
    } else {
        return indice->second;
    }
    return nullptr;
}

void Resources::ClearNumber(){
    numbersTable.clear();
}
