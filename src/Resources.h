#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

using std::pair;
using std::string;

class Resources{
public:
    static SDL_Texture* GetImage(string file);
    static Mix_Chunk* GetSound(string file);
    static TTF_Font* GetFont(string file, int fontSize);

    static void ClearImages();
    static void ClearSound();
    static void ClearFonts();

    static void PrintLoadedFonts();
    static void PrintLoadedSounds();
    static void PrintLoadedImages();
    static void PrintAllLoadedResources();

private:
    static std::unordered_map<string, SDL_Texture*> imageTable;
    static std::unordered_map<string, Mix_Chunk*> soundTable;
    static std::unordered_map<string, TTF_Font*> fontTable;
};

#endif
