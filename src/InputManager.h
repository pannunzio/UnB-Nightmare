#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "SDL.h"
#include <iostream>
#include <vector>
#include <unordered_map>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDLK_BUTTON_LEFT

#define MOUSE_STATE_SIZE 6;

using std::vector;

class InputManager {
public:
    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    bool QuitRequested();

    int GetMouseX();
    int GetMouseY();

    static InputManager& GetInstance();

private:
    InputManager();
    ~InputManager();

    vector<bool> mouseState;
    vector<int> mouseUpdate;

//    bool* keyState[416];
//    int* keyUpdate[416];
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;

    int updateCounter;

    int mouseX;
    int mouseY;
};


#endif
