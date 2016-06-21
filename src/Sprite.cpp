/*
 * Sprite.cpp
 *
 *  Created on: 12 de mar de 2016
 *      Author: Caio
 */

#include "Sprite.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Resources.h"

//***************************************************//
//Função: CONSTRUTOR********************************//
//Retorno: N/A*************************************//
//Parametros(overload): string file***************//
//Descrição: constroi o spri*********************//
//**********************************************//
Sprite::Sprite(){
	scaleX = scaleY = 1;
	height = 0;
	width = 0;
	texture = nullptr;
	this->frameCount = 1;
	this->frameTime = 0;
	this->currentFrame = 1;
	this->timeElapsed = 0;
	//cout << "Sprite created" << endl;
}
Sprite::Sprite(string file){
	scaleX = scaleY = 1;
	texture = nullptr;
	height = 0; 	width = 0; // tem q ser baseado no tamanho da imagem

	this->frameCount = 1;
	this->frameTime = 0;
	this->currentFrame = 1;
	this->timeElapsed = 0;
	Open(file);
}

//*************************************************//
//Função: DESTRUTOR*******************************//
//Retorno: N/A***********************************//
//Parametros(overload): float x, float y********//
//Descrição: destroi o vec2********************//
//********************************************//
Sprite::~Sprite(){
	//SDL_DestroyTexture(texture);
	//cout << "Sprite destroyed" << endl;
}
//*********************************************************************//
//Função: Sprite::setClip(int x, int y, int w, int h)*****************//
//Retorno: void******************************************************//
//Parametros: int x, int y, int w, int h****************************//
//Descrição: seta o clip do sprite*********************************//
//****************************************************************//
void Sprite::SetClip(int x, int y, int w, int h){
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}
//****************************************************************//
//Função: Sprite::Render(int x, int y)***************************//
//Retorno: void*************************************************//
//Parametros: int x, int y*************************************//
//Descrição: renderiza o sprite*******************************//
//***********************************************************//
void Sprite::Render(int x, int y){

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w*scaleX;
	dstRect.h = clipRect.h*scaleY;

	if(SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstRect)!=0)
		std::cout<< "Error ao renderizar ( Sprite::Render(int x, int y))" << std::endl;

}
void Sprite::RenderFlipped(int x,int y){
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w*scaleX;
	dstRect.h = clipRect.h*scaleY;
	if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL)!=0)
			cout<< "Error ao renderizar ( Sprite::Render(int x, int y))" << endl;


}

void Sprite::Render(int x, int y, float angle){
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w*scaleX;
	dstRect.h = clipRect.h*scaleY;

	if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstRect, angle, nullptr, SDL_FLIP_NONE)!=0)
		cout<< "Error ao renderizar ( Sprite::Render(int x, int y))" << endl;
}



//****************************************************************//
//Função: Sprite::IsOpen()***************************************//
//Retorno: *****************************************************//
//Parametros: void*********************************************//
//Descrição: verifica se a texture do sprite ja foi alocada***//
//***********************************************************//
bool Sprite::IsOpen(){
	if(!texture)
		return false;
	return true;
}
//********************************************************************//
//Função: Sprite::Open(string file)**********************************//
//Retorno: void*****************************************************//
//Parametros: string file******************************************//
//Descrição: abre a imagem e carrega na textura*******************//
//***************************************************************//
void Sprite::Open(string file){
	texture = Resources::GetImage(file);
	if(SDL_QueryTexture(texture,NULL,NULL,&width,&height)!=0)
		std::cout << "Error ao iniciar query do open:  " << SDL_GetError() << std::endl;
	SetClip((width/frameCount)*(currentFrame-1),0,width/frameCount,height);
}
//********************************************************************//
//Função: Sprite::getHeight(),getWidth()*****************************//
//Retorno: int******************************************************//
//Parametros: void*************************************************//
//Descrição: getters para o Sprite********************************//
//***************************************************************//
int Sprite::GetHeight(){
	return height*scaleY;
}
int Sprite::GetWidth(){
	return (width*scaleX)/frameCount;
}
// trab 5
void Sprite::SetScaleX(float scale){
	scaleX = scale;
}
void Sprite::SetScaleY(float scale){
	scaleY = scale;
}
void Sprite::SetScale(float scale){
	scaleX = scaleY = scale;
}

void Sprite::Update(float dt){
	timeElapsed+=dt;
	if(timeElapsed > frameTime){
		currentFrame++;
		timeElapsed = 0;
	}
	if(currentFrame > frameCount)
		currentFrame = 1;
	SetFrame(currentFrame);
}
void Sprite::SetFrame(int frame){
	currentFrame = frame;

	SetClip((width/frameCount)*(currentFrame-1),0,width/frameCount,height);
	/*
	std::cout << "Valor frameCount" << frameCount << std::endl;
	std::cout << "Valor CurrentFrame: " << currentFrame << std::endl;
	std::cout << "valor do GetWidth" << GetWidth() << std::endl;
	std::cout << "valor de width: " << width << std::endl;
	std::cout << "Valor inicial dos pixels: " << GetWidth()*(currentFrame -1) << std::endl;
	*/
}
void Sprite::SetFrameCount(int frameCount){
	this->frameCount = frameCount;
}
void Sprite::SetFrameTime(float frameTime){
	this->frameTime = frameTime;
}
Sprite::Sprite(string file, int frameCount, float frameTime){
	scaleX = scaleY = 1;
	texture = nullptr;
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	this->currentFrame = 1;
	height = 0; 	width = 0; // tem q ser baseado no tamanho da imagem
	Open(file);
}

