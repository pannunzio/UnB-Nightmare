#ifndef TEXT_H_
#define TEXT_H_

#include <SDL_ttf.h>
#include <iostream>

#include "Rect.h"
#include "Resources.h"
#include "Game.h"
#include <string>


#define TEXT_BLACK SDL_Color{0,0,0}
#define TEXT_WHITE SDL_Color{255,255,255}

#define TEXT_RED SDL_Color{255,0,0}
#define TEXT_GREEN SDL_Color{0,255,0}
#define TEXT_BLUE SDL_Color{0,0,255}

enum TextStyle{
    SOLID,
    SHADED,
    BLENDED
};

class Text {
public:
	Text();
	Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x= 0, int y=0);
	~Text();

	void Render(int cameraX = 0, int cameraY =0);
	void SetPos(int x, int y, bool centerX = false, bool centerY = false);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontSize(int fontSize);
	void SetText(std::string text);

private:
	void RemakeTexture();

	std::string fontFile;
	std::string text;

	TTF_Font* font;
	SDL_Texture* texture;
	TextStyle style;
	SDL_Color color;

	int fontSize;
	Rect box;
};

#endif
