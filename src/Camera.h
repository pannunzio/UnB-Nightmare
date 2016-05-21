/*
 * Camera.h
 *
 *  Created on: 25 de mar de 2016
 *      Author: Caio
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vec2.h"
#include "GameObject.h"

class Camera {
public:
	Camera();
	~Camera();
	static void Update(float dt);

	void Is(std::string type);

	static Vec2 pos;
	static Vec2 speed;


private:
	static int layer;

};

#endif /* CAMERA_H_ */
