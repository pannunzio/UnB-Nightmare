#include "Camera.h"

Rect Camera::pos = Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
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
            if(pos.y > CAMERA_LAYER_TOP){//e a camera ainda nao está na origem
                lastY = pos.y;
                pos.y = pos.y - speed.y*dt*100;//continua descendo a camera
            }else if(pos.y < CAMERA_LAYER_TOP){
                pos.y = lastY = CAMERA_LAYER_TOP;//garante que vai ficar exatamente em 0
            }
            break;
        case TERREO:
            if(pos.y > CAMERA_LAYER_MIDDLE && lastY > CAMERA_LAYER_MIDDLE){
                lastY = pos.y;
                pos.y = pos.y - speed.y*dt*100;
            }else if(pos.y < CAMERA_LAYER_MIDDLE && lastY < CAMERA_LAYER_MIDDLE){
                lastY = pos.y;
                pos.y = pos.y + speed.y*dt*100;
            }else{
                pos.y = lastY = CAMERA_LAYER_MIDDLE;
            }
            break;
        case SUBSOLO:
            if(pos.y < CAMERA_LAYER_BOTTON){
                lastY = pos.y;
                pos.y = pos.y + speed.y*dt*100;
            }else if(pos.y > CAMERA_LAYER_BOTTON){
                pos.y = lastY = CAMERA_LAYER_BOTTON;
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
