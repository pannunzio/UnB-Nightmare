#include "Sprite.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Resources.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
        #define DEBUG_ONLY(x) do{x;}while(0);
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
        #define DEBUG_ONLY(x) //do{;}while(0)
#endif //DEBUG

Sprite::Sprite(){
    DEBUG_PRINT("Sprite vazio construido")
	this->scaleX = scaleY = 1;
	this->height = 0;
	this->width = 0;
	this->texture = nullptr;
	this->frameCount = 1;
	this->frameTime = 0;
	this->currentFrame = 1;
	this->timeElapsed = 0;
	this->times = 0;
	this->fadingIn = false;
	this->fadingOut = false;
	this->fadingToValue = false;
	this->fadingToggle = false;
	this->fadeModifyer = 1;
	this->fadeCounter = 1;
	this->fadeValue = 0;
	this->actualAlpha = SDL_ALPHA_OPAQUE;
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
	this->file = file;
	this->fadingIn = false;
	this->fadingOut = false;
	this->fadingToValue = false;
	this->fadingToggle = false;
	this->fadeValue = 0;
	this->fadeModifyer = 1;
	this->fadeCounter = 1;
	this->actualAlpha = SDL_ALPHA_OPAQUE;
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
    this->file = file;
    this->fadingIn = false;
	this->fadingOut = false;
	this->fadingToValue = false;
	this->fadingToggle = false;
	this->fadeValue = 0;
	this->fadeModifyer = 1;
	this->fadeCounter = 1;
	this->actualAlpha = SDL_ALPHA_OPAQUE;
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
		std::cout<< "[TESTE 2]Error ao renderizar" << __PRETTY_FUNCTION__ << SDL_GetError() << std::endl;

}
void Sprite::RenderFlipped(int x,int y){
	this->dstRect.x = x;
	this->dstRect.y = y;
	this->dstRect.w = this->clipRect.w * this->scaleX;
	this->dstRect.h = this->clipRect.h * this->scaleY;

	if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &this->dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL) != 0)
			cout<< "[TESTE]Error ao renderizar " << __PRETTY_FUNCTION__ << SDL_GetError() << endl;
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

void Sprite::Load(string file){
    if(file == "") this->Open(this->file);
    else{
        this->file = file;
        this->Open(file);
    }
}

void Sprite::Open(string file){
    this->file = file;
	this->texture = Resources::GetImage(file);

	if(SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height) != 0)
		std::cout << "Error ao iniciar query do open:  " << SDL_GetError() << std::endl;

    if(SDL_GetTextureAlphaMod(this->texture, &this->actualAlpha) < 0)
        SDL_GetError();

	SetClip((this->width/this->frameCount) * (this->currentFrame - 1), 0, this->width/this->frameCount, this->height);
}

int Sprite::GetHeight(){
	return this->height * this->scaleY;
}

int Sprite::GetWidth(){
	return (this->width * this->scaleX)/this->frameCount;
}

string Sprite::GetFile(){
    return this->file;
}

void Sprite::SetFile(string file){
    this->file = file;
    DEBUG_PRINT("this->file: " << this->file)
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

	if(this->fadingToValue)
        this->_fadeToValue();
    if(this->fadingToggle)
        this->_fadeToggle();
	if(this->fadingIn || this->fadingOut)
        this->_fade();
    DEBUG_PRINT("************************************")
    DEBUG_PRINT("file: " << this->file)
    DEBUG_PRINT("fadeCounter: " << this->fadeCounter )
    DEBUG_PRINT("fadeValue: " << this->fadeValue )
    DEBUG_PRINT("fadeModifyer: " << this->fadeModifyer )
    DEBUG_PRINT("fadingIn: " << this->fadingIn )
    DEBUG_PRINT("fadingOut: " << this->fadingOut )
    DEBUG_PRINT("fadingToValue: " << this->fadingToValue )
    DEBUG_PRINT("fadingToggle: " << this->fadingToggle )
    DEBUG_PRINT("actualAlpha: " << (int)this->actualAlpha )

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

bool Sprite::IsAnimationFinished(){
    if(this->timesCounter == this->times &&
       this->currentFrame == this->frameCount)
       return true;
    else return false;
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

void Sprite::SetAlpha(int alpha){
    if(alpha > SDL_ALPHA_OPAQUE) alpha = SDL_ALPHA_OPAQUE;
    if(alpha < SDL_ALPHA_TRANSPARENT) alpha = SDL_ALPHA_TRANSPARENT;
    this->fadeValue = alpha;
    if(SDL_SetTextureAlphaMod(this->texture, alpha) < 0)
        SDL_GetError();
}

int Sprite::GetAlpha(){
    return this->actualAlpha;
}

void Sprite::FadeToValue(int fadeValue){
    if(fadeValue > SDL_ALPHA_OPAQUE) this->fadeValue = SDL_ALPHA_OPAQUE;
    else if(fadeValue < SDL_ALPHA_TRANSPARENT) this->fadeValue = SDL_ALPHA_TRANSPARENT;
    else this->fadeValue = fadeValue;

    this->fadingToValue = true;
}

void Sprite::_fadeToValue(){
    if(this->actualAlpha == this->fadeValue){
        this->fadingIn = false;
        this->fadingOut = false;
        this->fadingToValue = false;
    }else if(this->actualAlpha > this->fadeValue){
        this->fadingOut = true;
        this->fadingIn = false;
    }else if(this->actualAlpha < this->fadeValue){
        this->fadingOut = false;
        this->fadingIn = true;
    }
}

void Sprite::FadeIn(int increment){
    if(!this->fadingIn && this->actualAlpha != this->fadeValue)
    if(this->fadingOut) this->fadingOut = false;
    this->fadingIn = true;
    if(!this->fadingToValue) this->fadeValue = SDL_ALPHA_OPAQUE;

    if(increment > SDL_ALPHA_OPAQUE) this->fadeModifyer = SDL_ALPHA_OPAQUE;
    else if(increment < 1) this->fadeModifyer = 1;
    else this->fadeModifyer = increment;
}

void Sprite::FadeOut(int decrement){
    if(this->fadingIn) this->fadingIn = false;
    this->fadingOut = true;
    if(!this->fadingToValue) this->fadeValue = 0;

    if(decrement > SDL_ALPHA_OPAQUE) this->fadeModifyer = SDL_ALPHA_OPAQUE;
    else if(decrement < 1) this->fadeModifyer = 1;
    else this->fadeModifyer = decrement;
}

void Sprite::FadeToggle(bool onOff, int slow){
    //se o toggle estava desligado e acabei de ligar
    if(!this->fadingToggle && onOff){//liga
        this->fadingToggle = true;
        if(this->fadingIn) this->fadingIn = false;
        if(this->fadingOut) this->fadingOut = false;

        if(slow > SDL_ALPHA_OPAQUE) this->fadeModifyer = SDL_ALPHA_OPAQUE;
        else if(slow < 1) this->fadeModifyer = 1;
        else this->fadeModifyer = slow;

    //se estava ligado e acabei de desligar
    }else if(this->fadingToggle  && !onOff){//desliga
        this->fadingToggle = false;
        this->fadeModifyer = 1;
        if(this->fadingIn) this->fadingIn = true;//sempre termina com o sprite "aceso"
        if(this->fadingOut) this->fadingOut = false;
    }
}

void Sprite::_fadeToggle(){
    if(this->actualAlpha == SDL_ALPHA_OPAQUE ){
        this->fadingOut = true;
        this->fadingIn = false;
    }else if(this->actualAlpha == SDL_ALPHA_TRANSPARENT){
        this->fadingIn = true;
        this->fadingOut = false;
    }
}

void Sprite::_fade(){
    if(SDL_GetTextureAlphaMod(this->texture, &(actualAlpha) ) < 0)
        SDL_GetError();
    if(SDL_SetTextureAlphaMod(this->texture, _fadeSpeed() ) < 0)
        SDL_GetError();
}

uint8_t Sprite::_fadeSpeed(){
    if(this->fadeCounter < this->fadeModifyer) this->fadeCounter++;
    else{
            this->fadeCounter = 1;
            if(this->fadingIn){
                if(this->actualAlpha + this->fadeModifyer <= SDL_ALPHA_OPAQUE) return (this->actualAlpha + this->fadeModifyer);
                else{
                    this->fadingIn = false;
                    if(!this->fadingToggle) this->fadeModifyer = 1;
                    return this->actualAlpha;
                }
            }
            else if(this->fadingOut){
                if(this->actualAlpha - this->fadeModifyer >= SDL_ALPHA_TRANSPARENT) return (this->actualAlpha - this->fadeModifyer);
                else{
                    this->fadingOut = false;
                    this->fadeModifyer = 1;
                    return this->actualAlpha;
                }
            }
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
