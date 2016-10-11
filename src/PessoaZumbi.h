#ifndef PESSOAZUMBI_H
#define PESSOAZUMBI_H

#include "GameObject.h"
#include "Obstacle.h"
#include "Player.h"
#include "Camera.h"
#include "Defines.h"

using std::string;
using std::cout;
using std::endl;

class PessoaZumbi: public Obstacle{
public:
    PessoaZumbi();
    ~PessoaZumbi();

    void Render();
	void NotifyCollision(GameObject* other);
	bool Is(string type);
	int GetLayer();
    int GetSublayer();

    // 1 = subsolo , 2 = terreo , 3 = mesaniggno
	int layer;
	 // 0 = nao colide com nada, 1 = baixo, 2 = meio ,3 = topo, 4 = todos
	int subLayer;

private:
    void GetSprite();
    void GetZombieSound();
    void ChangeSprite();
};

#endif // PESSOAZUMBI_H
