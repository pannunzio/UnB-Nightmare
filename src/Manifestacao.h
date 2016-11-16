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
    Manifestacao(float layerHeight);
    ~Manifestacao();

	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	int GetLayer();
    int GetSublayer();

    // 1 = subsolo , 2 = terreo , 3 = mesaniggno
	int layer;
	 // 0 = nao colide com nada, 1 = baixo, 2 = meio ,3 = topo, 4 = todos
	int subLayer;

private:
    bool isCollidingWithPlayer;
};

#endif // MANIFESTACAO_H
