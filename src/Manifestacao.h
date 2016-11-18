#ifndef MANIFESTACAO_H
#define MANIFESTACAO_H

#include "Obstacle.h"
#include "Player.h"
#include "Camera.h"

#define MANIFESTACAO_SPRITE     "img/manifest.png"
#define MANIFESTACAO_FRAMES     6
#define MANIFESTACAO_FTIME      0.2

#define MANIFESTACAO_SOUND      "audio/manifestacao_11s.wav"

class Manifestacao: public Obstacle{
public:
    Manifestacao();
    ~Manifestacao();

	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	int GetLayer();
    int GetSublayer();

private:
    bool isCollidingWithPlayer;
};

#endif // MANIFESTACAO_H
