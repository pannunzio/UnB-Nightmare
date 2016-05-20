/*
 * InputManager.h
 *
 *  Created on: 24 de mar de 2016
 *      Author: Caio
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#define W_KEY SDLK_w
#define S_KEY SDLK_s
#define A_KEY SDLK_a
#define D_KEY SDLK_d

#define SPACE_BAR_KEY SDLK_SPACE
#define DOWN_ARROW_KEY SDLK_DOWN
#define LEFT_ARROW_KEY SDLK_LEFT
#define UP_ARROW_KEY SDLK_UP
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define ESCAPE_KEY SDLK_ESCAPE



#include <map>

class InputManager {
public:
	void Update();

	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	bool IsKeyUp(int key);

	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	bool IsMouseUp(int button);

	int GetMouseX();
	int GetMouseY();

	bool QuitRequested();

	static InputManager& GetInstance();
	~InputManager();


private:
	InputManager();
	bool keyState[416];
	int keyUpdate[416];

	bool mouseState[6];
	int mouseUpdate[6];

	int updateCounter;

	bool quitRequested;

	int mouseX;
	int mouseY;
};

#endif /* INPUTMANAGER_H_ */
