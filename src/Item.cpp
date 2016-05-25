#include "Item.h"
#include "Player.h"

Item::Item(int layer, int subLayer, std::string item)
{
    //ctor
    this->layer = layer;
    this->subLayer = subLayer;
    this->speed = Vec2(CAMERA_NORMAL_SPEED,2);
    beingUsed = 0;
    //box.Centralize(Player::player->box.x - Camera::pos.x+1200,Player::player->box.y - Camera::pos.y+80,bg.GetWidth(),bg.GetHeight());

    if(subLayer==SUBLAYER_BOTTON){
        box.Centralize(1355,305,bg.GetWidth(),bg.GetHeight());
        std::cout << "BOTTON";
    }
    if(subLayer==SUBLAYER_TOP){
        box.Centralize(1355,265,bg.GetWidth(),bg.GetHeight());
        std::cout << "  TOP";
    }
    if(subLayer==SUBLAYER_MIDDLE){
        box.Centralize(1355,285,bg.GetWidth(),bg.GetHeight());
        std::cout << "MIDDLE";
    }
    if(item == "COFFEE"){
        itemType = COFFEE;
        bg= Sprite("img/cafe.png");
    }
    if(item == "SKATE"){
        itemType = SKATE;
        bg= Sprite("img/coffee.png");
    }
    if(item == "OUTRO"){
        itemType = OUTRO;
        bg= Sprite("img/coffee.png");
    }

    //std::cout << "Item Construido" << std::endl;

}

void Item::Update(float dt){
    int X, W;
    bg.Update(dt);
	if(Player::player->GetSpeed() <= CAMERA_NORMAL_SPEED)
			box.x = box.x - speed.x*dt*100 ;//- 0.1*(Player::GetInstance().GetSpeed() - MAXSPEED)*speed.x*dt*100;
    if(Player::player->GetSpeed() > CAMERA_NORMAL_SPEED){
        if(Player::player->IsRightPosition())
            box.x = box.x - Player::player->GetSpeed()*dt*100 ;
        else
            box.x = box.x - speed.x*dt*100;
    }
	X = Player::player->box.x - Camera::pos.x;
	W = Player::player->box.w / 2;
    if(Player::player->layer == layer && Player::player->subLayer==subLayer){
        if((box.x<(X+W))&&(box.x>(X-W)))
            beingUsed = 2;
    }

//    if(Player::player->layer -layer ==1){
//        if (box.y<545-subLayer*20)
//            box.y = box.y+ speed.y*dt*100;
//    }else if(Player::player->layer -layer ==2){
//        if (box.y<765-subLayer*20)
//            box.y = box.y + speed.y*dt*100;
//    }
//    else if(Player::player->layer -layer ==-1){
//        if (box.y>65-subLayer*20)
//            box.y = box.y - speed.y*dt*100;
//    }
//    else if(Player::player->layer -layer ==-2){
//        if (box.y>-135-subLayer*20)
//            box.y = box.y - speed.y*dt*100;
//    }else if(Player::player->layer -layer ==0){
//        if (box.y>314-subLayer*20)
//            box.y = box.y - speed.y*dt*100;
//        if (box.y<316-subLayer*20)
//            box.y = box.y + speed.y*dt*100;
//    }
    if(Player::player->layer==3){
        if(layer==2){
            if (box.y<545-subLayer*20)
                box.y = box.y+ speed.y*dt*100;
        }else if(layer==1){
            if (box.y<815-subLayer*20)
                box.y = box.y+ speed.y*dt*100;
        }else if(layer==3){
            if (box.y>284-subLayer*20)
                box.y = box.y - speed.y*dt*100;
            if (box.y<286-subLayer*20)
                box.y = box.y + speed.y*dt*100;
        }

    }else if(Player::player->layer==2){
        if(layer==2){
            if (box.y>324-subLayer*20)
                box.y = box.y - speed.y*dt*100;
            if (box.y<326-subLayer*20)
                box.y = box.y + speed.y*dt*100;
        } else if(layer==1){
            if (box.y<585-subLayer*20)
                box.y = box.y+ speed.y*dt*100;
        }else if(layer==3){
            if (box.y>65-subLayer*20)
                box.y = box.y- speed.y*dt*100;
        }
    }else if(Player::player->layer==1){
        if(layer==2){
            if (box.y>65-subLayer*20)
                box.y = box.y - speed.y*dt*100;
        } else if(layer==1){
            if (box.y>324-subLayer*20)
                box.y = box.y - speed.y*dt*100;
            if (box.y<326-subLayer*20)
                box.y = box.y + speed.y*dt*100;
        }else if(layer==3){
            if (box.y>-155-subLayer*20)
                box.y = box.y- speed.y*dt*100;
        }
    }

	//std::cout << "ITEM: " <<box.x << "|||"<<box.y << std::endl;
}

void Item::Render(){
    bg.Render(box.x , box.y);
}

void Item::Use(){}

bool Item::IsDead(){
    if(beingUsed==2||box.x<-100)
        return true;
    return false;
}

void Item::NotifyCollision(GameObject* other){
//    if(other->Is("Player")){
//        if(other->subLayer==subLayer){
//            beingUsed = 2;
//            std::cout << "ITEM: " <<other->subLayer<< "|||"<<subLayer << std::endl;
//        }
//        std::cout << "ITEM: " <<other->subLayer<< "|||"<<subLayer << std::endl;
//    }

}

//void Item::SpawnRandom(GameObject* target){}

bool Item::Is(std::string type){
    if(type == "Item")
        return true;
    return false;
}
