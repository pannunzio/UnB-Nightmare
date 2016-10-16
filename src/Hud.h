#ifndef HUD_H
#define HUD_H

#include "Resources.h"
#include "Sprite.h"
#include "Text.h"
#include "Clock.h"

#include <string>
#include <sstream>

#define HUD_BG_FILE " "

#define NOTIFICATION_FILE " "

#define CLOCK_INIT_TIME 10
#define CLOCK_INIT_TEXT "0:00"
#define CLOCK_ICON_FILE " "

#define COFFEE_AMOUNT_INIT 0
#define COFFEE_INIT_TEXT "0"
#define COFFEE_ICON_FILE " "

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

private:
	string coffeeAmmo;
	string clock;

	Text clockText;
//	Text clockText2;
	Text coffeeText;
};

#endif // HUD_H
