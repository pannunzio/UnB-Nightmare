#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include "../src/Sprite.h"
#include "../src/Text.h"
#include "../src/Camera.h"
#include "../src/InputManager.h"

#define BG_MENU "img/menuProvisorio.png"
#define MENU_MIN_t 0

#define MENU_TYPE   "Menu"

#define MENU_TEXT_FONT          "font/ComicNeue-Angular_Bold_Oblique.otf"
#define MENU_TEXT_FONT_SIZE     35
#define BUTTON_SELECTED         "img/buttonselected.png"
#define BUTTON_NOT_SELECTED     "img/buttonnotselected.png"
#define BUTTON_OFFSET_Y         5

class Menu: public GameObject
{
public:
    Menu();
    Menu(float posX, float posY, int newLineSpace);
    virtual ~Menu();
    void Update(float dt);
    void Render();
    bool IsDead();
    void NotifyCollision(GameObject* other);
    bool Is(std::string type);

    int GetLayer();
    int GetSublayer();
    bool GetSelection();
    int GetSelectedOption();
    void AddMenuOption(string newOpt);
    void RemoveMenuOption(int option);
    void SetPosition(float posX, float posY, int newLineSpace);


protected:

private:
    int newLineSpace;
    int currentOption;
    int lastOption;
    int selectedOption;
    Sprite buttonSelected;
    std::vector<Text*> options;
    std::vector<Sprite> buttons;

    bool gotInput;
    void HandleInputs();


};

#endif // MENU_H
