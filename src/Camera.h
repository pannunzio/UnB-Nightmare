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
	static void Resume(){stop = false;};
	static void MoveToFloor(int positionY);
	static void SetSpeed(float modifyer);
	static void MoveX(float valor);

	void Is(std::string type);

	static Rect pos;
	static Vec2 speed;
	enum{
        SUBSOLO = 1,
        TERREO,
        MESANINO
	};

private:
	static int layer;
	static bool stop;
	static float lastY;
};

#endif
