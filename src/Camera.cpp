#include "Camera.h"

Vec2 Camera::pos = Vec2(0,0);
Vec2 Camera::speed = Vec2(CAMERA_NORMAL_SPEED,2);

int Camera::layer = TERREO;
bool Camera::stop = false;
float Camera::lastY = 0;

Camera::Camera() {
}

Camera::~Camera() {

}

void Camera::Update(float dt){
    //move a camera no eixo Y
    switch(layer){
        case MESANINO://se esta na layer 3
            if(pos.y > 0){//e a camera ainda nao está na origem
                lastY = pos.y;
                pos.y = pos.y - speed.y*dt*100;//continua descendo a camera
            }
            break;
        case TERREO:
            if(pos.y > 220 && lastY > 220){
                lastY = pos.y;
                pos.y = pos.y - speed.y*dt*100;
            }else if(pos.y < 220 && lastY < 220){
                lastY = pos.y;
                pos.y = pos.y + speed.y*dt*100;
            }else{
                pos.y = lastY = 220;
            }
            break;
        case SUBSOLO:
            if(pos.y < 480){
                lastY = pos.y;
                pos.y = pos.y + speed.y*dt*100;
            }
    }
}

void Camera::MoveX(float valor){
    Camera::pos.x += speed.x*valor;
}

void Camera::SetSpeed(float newSpeed){
    speed.x = newSpeed;
}

void Camera::MoveToFloor(int newLayer){
    layer = newLayer;
}
