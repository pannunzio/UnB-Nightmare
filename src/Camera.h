#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vec2.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Defines.h"


/******
    Camera Defines
******/


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

	static Vec2 pos;
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
