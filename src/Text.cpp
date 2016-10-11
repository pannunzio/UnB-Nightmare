#include "Text.h"
Text::Text(){

}

Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x, int y){
	this->box.x = x;
	this->box.y = y;

	this->fontSize = fontSize;
	this->style = style;
	this->text = text;
	this->color = color;
	this->texture = nullptr;
//	fontFile = std::to_string(fontSize) + fontFile;
	this->font = Resources::GetFont(fontFile, fontSize);
	this->fontFile = fontFile;

	RemakeTexture();
}

Text::~Text(){
	if(this->texture)
		SDL_DestroyTexture(this->texture);
}

void Text::Render(int cameraX, int cameraY){
	SDL_Rect dstRect;
	dstRect.x = this->box.x - cameraX;
	dstRect.y = this->box.y - cameraY;
	dstRect.w = this->box.w;
	dstRect.h = this->box.h;

	if(this->texture)
		SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, NULL, &dstRect);
}

void Text::SetPos(int x, int y, bool centerX, bool centerY){
	if(centerX)
		this->box.x = x - this->box.w/2.0; // arrumar calculo do centro
	else
		this->box.x = x;
	if(centerY)
		this->box.y = y - this->box.h/2.0;
	else
		this->box.y = y;

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
	this->font = Resources::GetFont(fontFile, fontSize);

	SDL_DestroyTexture(this->texture);
	SDL_Surface* surface;

	if(this->style == SOLID)
		surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
	if(this->style == SHADED)
		surface = TTF_RenderText_Shaded(this->font, this->text.c_str(), this->color, TEXT_BLACK);
	if(this->style == BLENDED)
		surface = TTF_RenderText_Blended(this->font, this->text.c_str(), this->color);

	this->texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	SDL_QueryTexture(this->texture, nullptr, nullptr, &surface->w, &surface->h);

    this->box.w = surface->w;
    this->box.h = surface->h;

	SDL_FreeSurface(surface);
}
