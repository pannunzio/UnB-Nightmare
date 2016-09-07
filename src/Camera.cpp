#include "Defines.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"


Vec2 Camera::pos = Vec2(0,0);
Vec2 Camera::speed = Vec2(CAMERA_NORMAL_SPEED,2);

int Camera::layer = 2;

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::Update(float dt){
        if(Player::player){
            //cout << "incremento: " << (speed.x*dt*100) << endl;
            float diff = Player::player->getX() - pos.x;
            if(Player::player->isInPosition()){
                pos.x += (speed.x*dt*100);
            }else if(diff < Player::player->getBaseX()){
                pos.x += (speed.x*dt*100)/3;
            }else if(diff > Player::player->getBaseX()){
                pos.x += (speed.x*dt*100)*5/2;
            }
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
