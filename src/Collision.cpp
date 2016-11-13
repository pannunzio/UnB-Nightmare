#include "Collision.h"

bool Collision::xCollision = false;
bool Collision::yCollision = false;

bool Collision::IsColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB){
    if(a.x < b.x){
        if(a.x + a.w > b.x ) xCollision = true;
        else xCollision = false;
    }else{
        if(b.x + b.w > a.x ) xCollision = true;
        else xCollision = false;
    }
    if(a.y < b.y){
        if(a.y + a.h > b.y ) yCollision = true;
        else yCollision = false;
    }else{
        if(b.y + b.h > a.y ) yCollision = true;
        else yCollision = false;
    }
    if(xCollision && yCollision) return true;
    else return false;
}
