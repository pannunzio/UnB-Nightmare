/*
 * Text.cpp
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#include "Text.h"
#include "Resources.h"
#include "Game.h"
#include <iostream>
#include <string>
//Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x, int y){
Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x, int y){
	box.x = x;
	box.y = y;

	this->fontSize = fontSize;
	this->style = style;
	this->text = text;
	this->color = color;
	texture = nullptr;
//	fontFile = std::to_string(fontSize) + fontFile;
	font = Resources::GetFont(fontFile, fontSize);
	this->fontFile = fontFile;

	RemakeTexture();


}

Text::Text(){

}
Text::~Text(){
	if(texture)
		SDL_DestroyTexture(texture);
}


void Text::Render(int cameraX, int cameraY){

	SDL_Rect dstRect;
	dstRect.x = box.x - cameraX;
	dstRect.y = box.y - cameraY;
	dstRect.w = box.w;
	dstRect.h = box.h;




	if(texture)
		SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, NULL, &dstRect);


}

void Text::SetPos(int x, int y, bool centerX, bool centerY){

	if(centerX)
		box.x = x - box.w/2.0; // arrumar calculo do centro
	else
		box.x = x;
	if(centerY)
		box.y = y - box.h/2.0;
	else
		box.y = y;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color){
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style){
	this->style = style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize){
	this->fontSize = fontSize;
//	std::string str_fontSize = to_string(fontSize);
//	fontFile[0] = str_fontSize[0];
//	fontFile[1] = str_fontSize[1];
	RemakeTexture();
}

void Text::SetText(std::string text){
    this->text = text;
    RemakeTexture();
}

void Text::RemakeTexture(){

	font = Resources::GetFont(fontFile, fontSize);
	SDL_DestroyTexture(texture);
	SDL_Surface* surface;
	if(style == SOLID)
		surface = TTF_RenderText_Solid(font,text.c_str(),color);
	if(style == SHADED)
		surface = TTF_RenderText_Shaded(font,text.c_str(),color, TEXT_BLACK);
	if(style == BLENDED)
		surface = TTF_RenderText_Blended(font,text.c_str(),color);

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	SDL_QueryTexture(this->texture, nullptr, nullptr, &surface->w, &surface->h);
    this->box.w = surface->w;
    this->box.h = surface->h;
	SDL_FreeSurface(surface);

//	box.Print();
}
