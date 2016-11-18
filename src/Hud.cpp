#include "Hud.h"

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

Hud::Hud(): bgSprite(HUD_BG_FILE),
            sliderSprite(HUD_SLIDER_FILE){

    DEBUG_PRINT("enter HUD constructor")

    this->coffeeAmmo = "c";
    this->clock = "b";
    this->distanciaProvisoria = "a";
    this->distanceRun = 0;
    this->ballon = Sprite(BALLON_STAIRS, BALLON_STAIRS_FRAMES, BALLON_STAIRS_FTIME);

    DEBUG_PRINT("exit HUD constructor")
}

Hud::~Hud(){
    DEBUG_PRINT("destroy HUD  ")
}

void Hud::InitHud(){
    DEBUG_PRINT("enter INIT HUD")

    this->coffeeText = new Text(COFFEE_TEXT_FILE, COFFEE_FONT_SIZE, TextStyle::BLENDED, COFFEE_INIT_TEXT, TEXT_MAGENTA, COFFEE_POS_X, COFFEE_POS_Y);
    this->clockText = new Text(CLOCK_TEXT_FILE, CLOCK_FONT_SIZE, TextStyle::BLENDED, CLOCK_INIT_TEXT, TEXT_BLACK, CLOCK_POS_X, CLOCK_POS_Y);

//    this->distanceText = new Text("font/ComicNeue_Bold.otf", 40, BLENDED, "DISTANCE TEXT", TEXT_WHITE, 300, 200);

    DEBUG_PRINT("exit INIT HUD")
}

void Hud::Update(float dt){
    this->clockText->SetText(this->clock);
    this->coffeeText->SetText(this->coffeeAmmo);
    if(this->showBallon) this->ballon.Update(dt);
//    this->distanceText->SetText(this->distanciaProvisoria);
}

void Hud::Render(){
    this->bgSprite.Render(SPRITE_MARGIN_RIGHT, SPRITE_MARGIN_SUPERIOR);
    this->sliderSprite.Render(SLIDER_POS_X + this->distanceRun, SLIDER_POS_Y);

    this->coffeeText->Render(0, 0);
    this->clockText->Render(0, 0);
    if(this->showBallon) this->ballon.Render(this->ballonX + BALLON_POS_X, this->ballonY - BALLON_POS_Y);
//    this->distanceText->Render(0, 0);
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

    this->distanceRun = (SLIDER_DELTA_X/100.0) * distance;

    newRemainDistance << "Distance: " << distance << "%";
    this->distanciaProvisoria = newRemainDistance.str();
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
