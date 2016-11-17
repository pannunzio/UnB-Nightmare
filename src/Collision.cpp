#include "Collision.h"

//#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
        #define DEBUG_ONLY(x) do{x;}while(0);
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
        #define DEBUG_ONLY(x) //do{;}while(0)
#endif //DEBUG


bool Collision::xCollision = false;
bool Collision::yCollision = false;

bool Collision::IsColliding(const Rect& a, const Rect& b){
    DEBUG_PRINT("a.x = " << a.x << "a.w = " << a.w)
    DEBUG_PRINT("b.x = " << b.x << "b.w = " << b.w)
    if(a.x < b.x){
        if(a.x + a.w >= b.x ) xCollision = true;
        else xCollision = false;
    }else{
        if(b.x + b.w >= a.x ) xCollision = true;
        else xCollision = false;
    }

    DEBUG_PRINT("a.y = " << a.y << "a.h = " << a.h)
    DEBUG_PRINT("b.y = " << b.y << "b.h = " << b.h)
    if(a.y < b.y){
        if(a.y + a.h >= b.y ) yCollision = true;
        else yCollision = false;
    }else{
        if(b.y + b.h >= a.y ) yCollision = true;
        else yCollision = false;
    }
    DEBUG_PRINT("xCollision: " << xCollision)
    DEBUG_PRINT("yCollision: " << yCollision)
    if(xCollision && yCollision) return true;
    else return false;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
