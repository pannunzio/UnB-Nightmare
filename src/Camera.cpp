#include "Camera.h"

Rect Camera::pos = Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
Vec2 Camera::speed = Vec2(CAMERA_NORMAL_SPEED,2);

int Camera::layer = LAYER_MIDDLE;
float Camera::lastY = 0;

Camera::Camera() {
}

Camera::~Camera() {

}

void Camera::Update(float dt){
    //move a camera no eixo Y
    switch(layer){
        case LAYER_TOP://se esta na layer 3
            if(pos.y > CAMERA_LAYER_TOP){//e a camera ainda nao está na origem
                lastY = pos.y;
                pos.y = pos.y - speed.y*dt*100;//continua descendo a camera
            }else if(pos.y < CAMERA_LAYER_TOP){
                pos.y = lastY = CAMERA_LAYER_TOP;//garante que vai ficar exatamente em 0
            }
            break;
        case LAYER_MIDDLE:
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
        case LAYER_BOTTON:
            if(pos.y < CAMERA_LAYER_BOTTON){
                lastY = pos.y;
                pos.y = pos.y + speed.y*dt*100;
            }else if(pos.y > CAMERA_LAYER_BOTTON){
                pos.y = lastY = CAMERA_LAYER_BOTTON;
            }
    }
}

void Camera::MoveX(float valor){
    pos.x += speed.x*valor;
}

void Camera::SetSpeed(float newSpeed){
    speed.x = newSpeed;
}

void Camera::MoveToFloor(int newLayer){
    layer = newLayer;
}

void Camera::SetXYWH(float x, float y, float w, float h){
    pos.x = x;
    pos.y = y;
    pos.w = w;
    pos.h = h;
}

void Camera::SetX(float x){
    pos.x = x;
}

void Camera::SetY(float y){
    pos.y = y;
}

void Camera::SetWidth(float w){
    pos.w = w;
}

void Camera::SetHeight(float h){
    pos.h = h;
}

int Camera::GetLayer(){
    return layer;
}

float Camera::GetX(){
    return pos.x;
}

float Camera::GetY(){
    return pos.y;
}

float Camera::GetWidth(){
    return pos.w;
}

float Camera::GetHeight(){
    return pos.h;
}
