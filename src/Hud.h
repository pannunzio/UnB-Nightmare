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

#define HUD_BG_FILE " "

#define NOTIFICATION_FILE " "

#define CLOCK_INIT_TIME 10
#define CLOCK_INIT_TEXT "0:00"
#define CLOCK_ICON_FILE " "

#define COFFEE_INIT_TEXT "000"
#define COFFEE_TEXT_FILE "font/Sketch_College.ttf"
#define COFFEE_ICON_FILE "img/coffee_HUD.png"
#define COFFEE_POS_X 100
#define COFFEE_POS_Y 37
#define COFFEE_FONT_SIZE 50

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
    void SetRemainingDistance(float distanceLeft);

private:
	string coffeeAmmo;
	string clock;
	string remainingDistance;

	Text* clockText;
	Text* coffeeText;
	Text* distanceText;

    Sprite coffeeSprite;
};

#endif // HUD_H
