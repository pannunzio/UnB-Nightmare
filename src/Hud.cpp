#include "Hud.h"

Hud::Hud(){
    cout << "enter HUD constructor" << endl;
    this->coffeeAmmo = "";
    this->clock = "";
    this->remainingDistance = "";
    cout << "exit HUD constructor" << endl;
}

Hud::~Hud(){
    cout << "destroy HUD" << endl;
}

void Hud::InitHud(){
    cout << "enter INIT HUD" << endl;

    this->clockText = new Text("font/ComicNeue_Bold.otf", 40, BLENDED, "CLOCK TEXT", TEXT_WHITE, 800, 17);
    this->coffeeText = new Text("font/ComicNeue_Bold.otf", 40, BLENDED, "COFFEE TEXT", TEXT_WHITE, 300, 17);
    this->distanceText = new Text("font/ComicNeue_Bold.otf", 40, BLENDED, "DISTANCE TEXT", TEXT_WHITE, 300, 200);

    cout << "exit INIT HUD" << endl;
}

void Hud::Update(float dt){
    this->clockText->SetText(this->clock);
    this->coffeeText->SetText(this->coffeeAmmo);
}

void Hud::Render(){
    this->clockText->Render(75, 0);
    this->coffeeText->Render(75, 0);
    this->distanceText->Render(75, 0);
}

void Hud::SetCoffeeAmmo(int coffeeAmmo){
    std::stringstream newCoffeeAmmo;
    newCoffeeAmmo << "Coffee: " << coffeeAmmo;
    this->coffeeAmmo = newCoffeeAmmo.str();
}

void Hud::SetClock(string clock){
    this->clock = clock;
}

void Hud::SetRemainingDistance(float distanceLeft){
    std::stringstream newRemainDistance;
    newRemainDistance << "Distance Left: " << distanceLeft;
    this->remainingDistance = newRemainDistance.str();
}
