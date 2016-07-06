#ifndef POMBO_H
#define POMBO_H

#include "GameObject.h"
#include "Sprite.h"

using std::cout;
using std::endl;

class Pombo: public GameObject{
public:
    Pombo();
    ~Pombo();

    void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);
private:
    Sprite pombo;
    Sprite sombra;
};

#endif // POMBO_H
