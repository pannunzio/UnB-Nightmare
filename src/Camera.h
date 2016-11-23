#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vec2.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Defines.h"
#include "Rect.h"


/******
    Camera Defines
******/
#define CAMERA_NORMAL_SPEED 5

#define CAMERA_LAYER_TOP -130
#define CAMERA_LAYER_MIDDLE 80
#define CAMERA_LAYER_BOTTON 120

class Camera {
public:
	Camera();
	~Camera();
	static void Update(float dt);
	static void MoveToFloor(int positionY);
	static void MoveX(float valor);

    static void SetXYWH(float x, float y, float w, float h);
	static void SetX(float x);
	static void SetY(float y);
	static void SetWidth(float w);
	static void SetHeight(float h);

	static void SetSpeed(float modifyer);

    static int GetLayer();
    static float GetX();
	static float GetY();
	static float GetWidth();
	static float GetHeight();


	void Is(std::string type);

	static Vec2 speed;

private:
	static Rect pos;
	static int layer;
	static float lastY;
};

#endif
