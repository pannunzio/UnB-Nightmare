/*
 * Resources.h
 *
 *  Created on: 23 de mar de 2016
 *      Author: Caio
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_
#include<unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_TTF.h>

#include <SDL_Mixer.h>
class Resources {

public:
	Resources();
	static SDL_Texture* GetImage(std::string file);
	static void ClearImages();

	static Mix_Music* GetMusic(std::string file);
	static void ClearMusic();

	static Mix_Chunk* GetSound(std::string file);
	static void ClearSound();

	static TTF_Font* GetFont(char* file, int fontSize);
	static void ClearFont();

	~Resources();
private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;
	static std::unordered_map<std::string, TTF_Font*> fontTable;
};

#endif /* RESOURCES_H_ */
