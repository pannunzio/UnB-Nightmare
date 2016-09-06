#include "Defines.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"

#define DELAY 200

Vec2 Camera::pos = Vec2(0,0);
Vec2 Camera::speed = Vec2(CAMERA_NORMAL_SPEED,2);

int Camera::layer = 2;

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::Update(float dt){
        if(Player::player){
//            if(Player::player->GetSpeed() <= CAMERA_NORMAL_SPEED)
//                pos.x = pos.x + speed.x*dt*100;
           // if(Player::player->GetSpeed() > CAMERA_NORMAL_SPEED){
                cout << "Player x Camera: " << Player::player->getX() << " ; " << pos.x << endl;
                if(Player::player->IsRightPosition())
                    pos.x = Player::player->getX();//pos.x + Player::player->GetSpeed()*dt*100;
                else{
                    float diff = Player::player->getX() - pos.x;
                    if(diff + DELTA_ACCEPT > Player::player->getBaseX()){
                        pos.x += 5;
                    }
                    pos.x = pos.x + (speed.x/3)*dt*100;
                    //estranhamente, mexendo aqui ta mudando o delay da personagem
                    //não da camera, como deveria ser
                }
            //}
            layer = Player::player->layer;
        }

		// mudança de local
		// camera
		if(layer == 3)
			if(pos.y > 0)
				pos.y = pos.y - speed.y*dt*100;
		if(layer == 2 )
			if(pos.y > 220)
			pos.y = pos.y - speed.y*dt*100;
		if(layer == 2 )
			if(pos.y < 220)
			pos.y = pos.y + speed.y*dt*100;
		if(layer == 1)
			if(pos.y < 480)
				pos.y = pos.y + speed.y*dt*100;

}
