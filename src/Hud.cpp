#include "Hud.h"

Hud::Hud() : coffeeSprite(COFFEE_FILE), clockSprite(CLOCK_FILE){
    cout << "enter HUD constructor" << endl;
    this->coffeeAmmo = "";
    this->clock = "";
    this->distanciaProvisoria = "a";
    cout << "exit HUD constructor" << endl;
}



Hud::~Hud(){
    cout << "destroy HUD" << endl;
}

void Hud::InitHud(){
    cout << "enter INIT HUD" << endl;
    this->coffeeText = new Text(COFFEE_TEXT_FILE, COFFEE_FONT_SIZE, BLENDED, COFFEE_INIT_TEXT, TEXT_MAGENTA, COFFEE_POS_X, COFFEE_POS_Y);
    this->clockText = new Text(CLOCK_TEXT_FILE, CLOCK_FONT_SIZE, BLENDED, CLOCK_INIT_TEXT, TEXT_BLACK, CLOCK_POS_X, CLOCK_POS_Y);

    this->distanceText = new Text("font/ComicNeue_Bold.otf", 40, BLENDED, "DISTANCE TEXT", TEXT_WHITE, 300, 200);

    cout << "exit INIT HUD" << endl;
}

void Hud::Update(float dt){
    this->clockText->SetText(this->clock);
    this->coffeeText->SetText(this->coffeeAmmo);
    this->distanceText->SetText(this->distanciaProvisoria);
}

void Hud::Render(){
    this->clockSprite.Render(SPRITE_MARGIN_LEFT- clockSprite.GetWidth(), SPRITE_MARGIN_SUPERIOR);
    this->coffeeSprite.Render(SPRITE_MARGIN_RIGHT, SPRITE_MARGIN_SUPERIOR);

    this->coffeeText->Render(0, 0);
    this->clockText->Render(0, 0);
    this->distanceText->Render(0, 0);
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

void Hud::SetDistanceRun(float distance){
    std::stringstream newRemainDistance;
    newRemainDistance << "Distance: " << distance << "%";
    this->distanciaProvisoria = newRemainDistance.str();
}
