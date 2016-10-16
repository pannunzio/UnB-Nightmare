#include "Hud.h"

Hud::Hud(){
    this->coffeeAmmo = "";
    this->clock = "";
}

Hud::~Hud(){
}

void Hud::InitHud(){
    cout << "enter INIT HUD" << endl;

    this->clockText.OpenText("font/ComicNeue_Bold.otf", 40, BLENDED, "CLOCK TEXT", TEXT_WHITE, 800, 17);
    this->coffeeText.OpenText("font/ComicNeue_Bold.otf", 40, BLENDED, "COFFEE TEXT", TEXT_WHITE, 300, 17);

    cout << "exit INIT HUD" << endl;
}

void Hud::Update(float dt){
    this->clockText.SetText(this->clock);
    this->coffeeText.SetText(this->coffeeAmmo);
}

void Hud::Render(){
    this->clockText.Render(75, 0);
    this->coffeeText.Render(75, 0);
}

void Hud::SetCoffeeAmmo(int coffeeAmmo){
    std::stringstream newCoffeeAmmo;
    newCoffeeAmmo << "Coffee: " << coffeeAmmo;
    this->coffeeAmmo = newCoffeeAmmo.str();
}

void Hud::SetClock(string clock){
    this->clock = clock;
}
