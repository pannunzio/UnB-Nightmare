#include "Sprite.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Resources.h"

Sprite::Sprite(){
	this->scaleX = scaleY = 1;
	this->height = 0;
	this->width = 0;
	this->texture = nullptr;
	this->frameCount = 1;
	this->frameTime = 0;
	this->currentFrame = 1;
	this->timeElapsed = 0;
	this->times = 0;
}

Sprite::Sprite(string file){
	this->scaleX = this->scaleY = 1;
	this->texture = nullptr;
	this->height = 0;
	this->width = 0; // tem q ser baseado no tamanho da imagem

	this->frameCount = 1;
	this->frameTime = 0;
	this->currentFrame = 1;
	this->timeElapsed = 0;
	this->times = 0;
	Open(file);
}

Sprite::Sprite(string file, int frameCount, float frameTime){
	this->scaleX = this->scaleY = 1;
	this->texture = nullptr;
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	this->currentFrame = 1;
	this->height = 0;
	this->width = 0; // tem q ser baseado no tamanho da imagem
	this->times = 0;

	Open(file);
}

Sprite::~Sprite(){
	//SDL_DestroyTexture(texture);
	//cout << "Sprite destroyed" << endl;
}

void Sprite::SetClip(int x, int y, int w, int h){
	this->clipRect.x = x;
	this->clipRect.y = y;
	this->clipRect.w = w;
	this->clipRect.h = h;
}

void Sprite::Render(int x, int y){

	this->dstRect.x = x;
	this->dstRect.y = y;
	this->dstRect.w = this->clipRect.w * this->scaleX;
	this->dstRect.h = this->clipRect.h * this->scaleY;

	if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &this->dstRect) != 0)
		std::cout<< "[TESTE 2]Error ao renderizar ( Sprite::Render(int x, int y))" << std::endl;

}
void Sprite::RenderFlipped(int x,int y){
	this->dstRect.x = x;
	this->dstRect.y = y;
	this->dstRect.w = this->clipRect.w * this->scaleX;
	this->dstRect.h = this->clipRect.h * this->scaleY;

	if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &this->dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL) != 0)
			cout<< "[TESTE]Error ao renderizar ( Sprite::Render(int x, int y))" << endl;
}

void Sprite::Render(int x, int y, float angle){
	this->dstRect.x = x;
	this->dstRect.y = y;
	this->dstRect.w = this->clipRect.w*scaleX;
	this->dstRect.h = this->clipRect.h*scaleY;

	if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &this->dstRect, angle, nullptr, SDL_FLIP_NONE) != 0)
		cout<< "Error ao renderizar ( Sprite::Render(int x, int y))" << endl;
}

bool Sprite::IsOpen(){
	if(!this->texture)
		return false;
	return true;
}

void Sprite::Open(string file){
	this->texture = Resources::GetImage(file);

	if(SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height) != 0)
		std::cout << "Error ao iniciar query do open:  " << SDL_GetError() << std::endl;

	SetClip((this->width/this->frameCount) * (this->currentFrame - 1), 0, this->width/this->frameCount, this->height);
}

int Sprite::GetHeight(){
	return this->height * this->scaleY;
}

int Sprite::GetWidth(){
	return (this->width * this->scaleX)/this->frameCount;
}

void Sprite::SetScaleX(float scale){
	this->scaleX = scale;
}

void Sprite::SetScaleY(float scale){
	this->scaleY = scale;
}

void Sprite::SetScale(float scale){
	this->scaleX = this->scaleY = scale;
}

void Sprite::Update(float dt){
	this->timeElapsed += dt;

	if(this->timeElapsed > this->frameTime){
		 this->currentFrame++;
		this->timeElapsed = 0;
	}
	if(this->times == 0){
        if(this->currentFrame > this->frameCount){
            this->currentFrame = 1;
        }
    }else{
        if(this->timesCounter < this->times){
                timesCounter++;
                if(this->currentFrame > this->frameCount){
                    this->currentFrame = 1;
                }
        }else{
            if(this->currentFrame > this->frameCount){
                    this->currentFrame = this->frameCount;
            }
        }
    }
	SetFrame(this->currentFrame);
}

void Sprite::SetFrame(int frame){
	this->currentFrame = frame;
	SetClip((this->width/this->frameCount) * (this->currentFrame - 1), 0, this->width/this->frameCount, this->height);
}

void Sprite::SetFrameCount(int frameCount){
	this->frameCount = frameCount;
}

void Sprite::SetAnimationTimes(int times){
    this->times = times;
    this->timesCounter = 0;
}

void Sprite::SetFrameTime(float frameTime){
	this->frameTime = frameTime;
}
