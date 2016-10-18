#include "Hud.h"

Hud::Hud() : coffeeSprite(COFFEE_ICON_FILE){
    cout << "enter HUD constructor" << endl;
    this->coffeeAmmo = "";
    this->clock = "";
    this->remainingDistance = "teste";
    cout << "exit HUD constructor" << endl;
}

Hud::~Hud(){
    cout << "destroy HUD" << endl;
}

void Hud::InitHud(){
    cout << "enter INIT HUD" << endl;
    this->coffeeText = new Text(COFFEE_TEXT_FILE, COFFEE_FONT_SIZE, BLENDED, COFFEE_INIT_TEXT, TEXT_MAGENTA, COFFEE_POS_X, COFFEE_POS_Y);

    this->clockText = new Text("font/ComicNeue_Bold.otf", 40, BLENDED, "CLOCK TEXT", TEXT_WHITE, 800, 17);
    this->distanceText = new Text("font/ComicNeue_Bold.otf", 40, BLENDED, "DISTANCE TEXT", TEXT_WHITE, 300, 200);

    cout << "exit INIT HUD" << endl;
}

void Hud::Update(float dt){
    this->clockText->SetText(this->clock);
    this->coffeeText->SetText(this->coffeeAmmo);
//    this->distanceText->SetText(this->remainingDistance);
}

void Hud::Render(){
    this->coffeeSprite.Render(15, 15);
    this->coffeeText->Render(0, 0);

    this->clockText->Render(75, 0);
    this->distanceText->Render(75, 0);
}

void Hud::SetCoffeeAmmo(int coffeeAmmo){
    std::stringstream newCoffeeAmmo;
    if (coffeeAmmo < 99)
        newCoffeeAmmo << "0";
    if (coffeeAmmo < 9)
        newCoffeeAmmo << "0";
    newCoffeeAmmo << coffeeAmmo;
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
