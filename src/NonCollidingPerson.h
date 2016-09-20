#ifndef NONCOLLIDINGPERSON_H
#define NONCOLLIDINGPERSON_H

#include "GameObject.h"
#include "Obstacle.h"
#include "Sprite.h"

using std::cout;
using std::endl;

enum Type{
    PELADO
};

class NonCollidingPerson: public Obstacle{
public:
    NonCollidingPerson();
    ~NonCollidingPerson();

    void Render();
	void NotifyCollision(GameObject* other);
	bool Is(string type);
	int GetLayer();
    int GetSublayer();

	int layer;
	int subLayer;

private:
    Type type;
};

#endif // NONCOLLIDINGPERSON_H
