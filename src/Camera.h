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
	static void Pause(){pause = true;};
	static void Resume(){pause = false;};
	static void MoveToFloor(int positionY);
	static void SpeedModifyer(float modifyer);

	void Is(std::string type);

	static Vec2 pos;
	static Vec2 speed;
	static float speedCoef;
	enum{
        SUBSOLO = 1,
        TERREO,
        MESANINO
	};

private:
	static int layer;
	static bool pause;
	static void MoveX(float dt);

};

#endif
