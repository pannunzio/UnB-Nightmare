#include "Camera.h"

Vec2 Camera::pos = Vec2(0,0);
Vec2 Camera::speed = Vec2(CAMERA_NORMAL_SPEED,2);

int Camera::layer = TERREO;
bool Camera::pause = false;
float Camera::speedCoef = 1;

Camera::Camera() {
}

Camera::~Camera() {

}

void Camera::Update(float dt){
        if(pause == false){
            MoveX(dt);
            //move a camera no eixo Y
            switch(layer){
                case MESANINO://se esta na layer 3
                    if(pos.y > 0){//e a camera ainda nao está na origem
                        pos.y = pos.y - speed.y*dt*100;//continua descendo a camera
                    }
                    break;
                case TERREO:
                    if(pos.y > 220){
                        pos.y = pos.y - speed.y*dt*100;
                    }else if(pos.y < 220){
                        pos.y = pos.y + speed.y*dt*100;
                    }
                    break;
                case SUBSOLO:
                    if(pos.y < 480){
                        pos.y = pos.y + speed.y*dt*100;
                    }
            }
        }
}

void Camera::MoveX(float dt){
    pos.x += speed.x*dt*speedCoef;
}

void Camera::SpeedModifyer(float modifyer){
    speedCoef = modifyer;
}

void Camera::MoveToFloor(int newLayer){
    layer = newLayer;
}
