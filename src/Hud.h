#ifndef HUD_H
#define HUD_H

#include "Resources.h"
#include "Sprite.h"
#include "Text.h"
#include "Clock.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#define HUD_BG_FILE         "img/spritehud.png"

#define CLOCK_INIT_TEXT     "0:00"
#define CLOCK_TEXT_FILE     "font/digitaldream.ttf"
#define CLOCK_POS_X         825
#define CLOCK_POS_Y         45
#define CLOCK_FONT_SIZE     30
#define CLOCK_FILE          "img/clock_HUD.png"

#define COFFEE_INIT_TEXT    "000"
#define COFFEE_TEXT_FILE    "font/Sketch_College.ttf"
#define COFFEE_POS_X        100
#define COFFEE_POS_Y        37
#define COFFEE_FONT_SIZE    50
#define COFFEE_FILE         "img/coffee_HUD.png"

#define SPRITE_MARGIN_RIGHT     15
#define SPRITE_MARGIN_LEFT      1009
#define SPRITE_MARGIN_SUPERIOR  15

using std::cout;
using std::endl;
using std::string;

class Hud{
public:
    Hud();
    ~Hud();

    void InitHud();

    void Update(float dt);
    void Render();

    void SetCoffeeAmmo(int coffeeAmmo);
    void SetClock(string clock);
    void SetDistanceRun(float distance);

private:
	string coffeeAmmo;
	string clock;

	//distancia em percentual percorrido pelo player
	float distanceRun;
	string distanciaProvisoria;

	Text* clockText;
	Text* coffeeText;
	Text* distanceText;

    Sprite coffeeSprite;
    Sprite clockSprite;
};

#endif // HUD_H
