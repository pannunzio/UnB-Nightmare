#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vec2.h"
#include "GameObject.h"


/******
    Camera Defines
******/
#define DELTA_ACCEPT 10


class Camera {
public:
	Camera();
	~Camera();
	static void Update(float dt);
	static void Pause(){pause = true;};
	static void Resume(){pause = false;};

	void Is(std::string type);

	static Vec2 pos;
	static Vec2 speed;

private:
	static int layer;
	static bool pause;

};

#endif
