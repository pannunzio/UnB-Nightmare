/*
 * Obstacle.cpp
 *
 *  Created on: 13 de jun de 2016
 *      Author: Caio
 */

#include "Obstacle.h"
#include "Camera.h"
#include "Defines.h"
#include "StageState.h"
#include "Game.h"
#include "Player.h"
// obstaculos normais
Obstacle::Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime)
{
	sp = Sprite(sprite,frameCount,frameTime);
	this->speed = speed;
	speed = speed + rand()%10/10;
	this->obstacleName = obstacleName;
	this->canBlock = canBlock;
	this->isDead = false;
    this->isSoundHappening = false;
	layer = rand()%3 + 1;
	subLayer = rand()%3 + 1;

	this->spriteSound = Sound(-1);
    this->captureSound = Sound(-1);

	// ou seja, vai dar respawn se passar no teste  //
	box.x = Player::player->box.x + 1200;			//
    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;

    if(obstacleName == "lixeira"){
        this->subLayer = 3;
        box.y += 15;
        captureSound.Open("audio/lixeira.wav");
    }

    if(obstacleName == "menina"){
        this->OpenXingamentoSound(rand()%11 + 1);
    }

	if(this->obstacleName == "menina" && rand()%100 < 20){
		sp = Sprite("img/meninazumbi.png",frameCount,frameTime);
		this->obstacleName = "meninaZumbi";
		this->speed = 3.5;
		this->OpenZombieSound(rand()%7+1);
		captureSound = spriteSound;
		captureSound.SetChannel(-1);
		spriteSound.Play(rand()%2+1);
	}

    if(this->obstacleName == "manifestacao" && this->subLayer == SUBLAYER_BOTTON){
    	this->sp = Sprite("img/manifest.png", 6, 0.2);
//    	spriteSound.Open("audio/manifestacao_11s.wav");
//    	spriteSound.PlayArbitraryFadeIn(1, 1);
//    	spriteSound.Play(1);
    }
	if(this->obstacleName == "cano"){
		this->sp = Sprite("img/cano.png",frameCount,frameTime);
		spriteSound.Open("audio/gotas.wav");
		spriteSound.Play(rand()%2+1);
	}

    if(Player::player->layer != this->layer){
//        spriteSound.SetVolume(8);
    }
    if(this->obstacleName == "menina" && this->speed == 0){
    	if(rand()%100 > 50)
            this->sp = Sprite("img/parado1.png", 1, 1);
        else
            this->sp = Sprite("img/parada.png", 6, 0.2);
    	this->obstacleName = "parado";
    	this->OpenXingamentoSound(rand()%11+1);
    }

	if(this->obstacleName == "menina" && rand()%100 < 50){
        sp = Sprite("img/menino.png",frameCount,frameTime);
        this->obstacleName = "menino";
        this->OpenXingamentoSound(rand()%11 + 1);
        captureSound.SetChannel(-1);
    }


//     else
//        CalculateSoundPosition();

//    spriteSound.Play(-1);
    												//
    box.y = box.y - (this->subLayer - 3)*26;		//
    ///////////////////////////////////////////////////
}

Obstacle::Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime,
		int layer, int subLayer)
{
	sp = Sprite(sprite,frameCount,frameTime);
	this->speed = speed;
	if(speed!=0)
		speed = speed + rand()%10/10;
	this->obstacleName = obstacleName;
	this->canBlock = canBlock;
	this->isDead = false;
	this->isSoundHappening = false;

	this->layer = layer;
	this->subLayer = subLayer;

	this->spriteSound = Sound(-1);
    this->captureSound = Sound(-1);


	// ou seja, vai dar respawn se passar no teste  //
	box.x = Player::player->box.x + 1200;			//
    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;
    // tem q ser tipo assim os outros tbm, dps alguem arruma ai
    box.y = box.y + sp.GetHeight();	 				//
    												//
    box.y = box.y - (this->subLayer - 3)*26;		//
    ///////////////////////////////////////////////////

    // consertar isso para pegar geral

    if(obstacleName == "menina"){
        this->OpenXingamentoSound(rand()%11 + 1);
    }

    if(obstacleName == "lixeira"){
        captureSound.Open("audio/lixeira.wav");
    }

    if(this->obstacleName == "manifestacao" && this->subLayer == SUBLAYER_BOTTON){
    	this->sp = Sprite("img/manifest.png", 6, 0.2);
    	spriteSound.Open("audio/manifestacao_11s.wav");
//    	spriteSound.PlayArbitraryFadeIn(1, 2);
    	spriteSound.Play(1);
    }
	if(this->obstacleName == "cano"){
		this->sp = Sprite("img/cano.png",frameCount,frameTime);
		this->OpenGotaSound(rand()%3 + 1);
		spriteSound.Play(rand()%2+1);
	}
	if(Player::player->layer != this->layer){
//        spriteSound.SetVolume(8);
    }
}

Obstacle::Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime, int layer)
{
	sp = Sprite(sprite,frameCount,frameTime);
	this->speed = speed;
	speed = speed + rand()%10/10;
	this->obstacleName = obstacleName;
	this->canBlock = canBlock;
	this->isDead = false;

	this->layer = layer;
	subLayer = rand()%3 + 1;

	this->spriteSound = Sound(-1);
    this->captureSound = Sound(-1);


	// ou seja, vai dar respawn se passar no teste  //
	box.x = Player::player->box.x + 1200;			//
    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;

    if(obstacleName == "lixeira"){
        subLayer = 3;
        box.y += 15;
        captureSound.Open("audio/lixeira.wav");
    }


    if(obstacleName == "menina"){
        this->OpenXingamentoSound(rand()%11 + 1);
        if(rand()%100 < 20){
            sp = Sprite("img/meninazumbi.png",frameCount,frameTime);
            this->obstacleName = "meninaZumbi";
        }
    }

    if(this->obstacleName == "manifestacao" && this->subLayer == SUBLAYER_BOTTON){
    	this->sp = Sprite("img/manifest.png", 6, 0.2);
    	spriteSound.Open("audio/manifestacao_11s.wav");
//    	spriteSound.PlayArbitraryFadeIn(1, 2);
        spriteSound.Play(1);
    }

    if(Player::player->layer != this->layer){
//        spriteSound.SetVolume(8);
    }
//    else
//        CalculateSoundPosition();
//
//    spriteSound.Play(-1);
    												//
    box.y = box.y - (this->subLayer - 3)*26;		//
    ///////////////////////////////////////////////////
}



Obstacle::~Obstacle(){

}

bool Obstacle::IsDead(){
    return this->isDead;
}
void Obstacle::Update(float dt){
	sp.Update(dt);
	box.x = box.x + speed*dt*100;

    if(box.x - Camera::pos.x +sp.GetWidth()< 0){
		this->isDead = true;


        spriteSound.Stop();
        captureSound.Stop();

    }
}
void Obstacle::Render(){
    if(this->obstacleName == "manifestacao"){
    	if(this->subLayer == SUBLAYER_BOTTON)
    		sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y - 120);
    }
    else if(this->obstacleName == "cano"){
    	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y - 250);
    }
    else if(this->obstacleName == "menino"){
        if(speed>=0)
    	 	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y - 30);
		else
			sp.RenderFlipped(box.x - Camera::pos.x, box.y - Camera::pos.y - 30);
    }
    else if(this->obstacleName == "parado"){
        if(speed>=0)
    	 	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y - 20);
		else
			sp.RenderFlipped(box.x - Camera::pos.x, box.y - Camera::pos.y - 20);
    }
    else{
    	if(speed>=0)
    		sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
		else
			sp.RenderFlipped(box.x - Camera::pos.x, box.y - Camera::pos.y);
    }

}
bool Obstacle::Is(std::string type){
	return (type == obstacleName);
}
void Obstacle::NotifyCollision(GameObject* other){
    if(other->Is("Coffee") && this->obstacleName != "manifestacao"){
    	speed = -5;
    	if(this->obstacleName == "meninaZumbi"){
    		sp = Sprite("img/menina.png", 6, 0.2);
    		//obstacleName = "menina";
    		speed = 8;
    	}

    }
    if(other->Is("Player") || other->Is("Coffee")){
        captureSound.Play(1);
    }
}

void Obstacle::OpenZombieSound(int num){
    switch (num){
    case 0:{
        spriteSound.Open("audio/Zumbi0.ogg");
        break;
    }
    case 1:{
        spriteSound.Open("audio/Zumbi2.ogg");
        break;
    }
    case 2:{
        spriteSound.Open("audio/Zumbi3.ogg");
        break;
    }
    case 3:{
        spriteSound.Open("audio/Zumbi6.ogg");
        break;
    }
    case 4:{
        spriteSound.Open("audio/Zumbi7.ogg");
        break;
    }
    case 5:{
        spriteSound.Open("audio/Zumbi8.ogg");
        break;
    }
    case 6:{
        spriteSound.Open("audio/Zumbi9.ogg");
        break;
    }
    }
}

void Obstacle::OpenXingamentoSound(int num){
    switch(num){
    case 1:{
        captureSound.Open("audio/Oxe2.wav");
        break;
    }
    case 2:{
        captureSound.Open("audio/Odoida3.wav");
        break;
    }
    case 3:{
        captureSound.Open("audio/Oxe1.wav");
        break;
    }
    case 4:{
        captureSound.Open("audio/Odoida2.wav");
        break;
    }
    case 5:{
        captureSound.Open("audio/Odoida3.wav");
        break;
    }
    case 6:{
        captureSound.Open("audio/Ai6.wav");
        break;
    }
    case 7:{
        captureSound.Open("audio/Ai5.wav");
        break;
    }case 8:{
        captureSound.Open("audio/Uh2.wav");
        break;
    }case 9:{
        captureSound.Open("audio/Ai3.wav");
        break;
    }
    case 10:{
        captureSound.Open("audio/Ai2.wav");
        break;
    }
    case 11:{
        captureSound.Open("audio/Ai1.wav");
        break;
    }
    }
}

void Obstacle::OpenGotaSound(int num){
    switch(num){
    case 1:{
        spriteSound.Open("audio/gota1.wav");
        break;
    }
    case 2:{
        spriteSound.Open("audio/gota2.wav");
        break;
    }
    case 3:{
        spriteSound.Open("audio/gota3.wav");
        break;
    }
    }
}

void Obstacle::StopSound(){
    cout << "stop sound" << endl;
    spriteSound.SetVolume(0);
    captureSound.SetVolume(0);
    spriteSound.Stop();
    captureSound.Stop();
}
