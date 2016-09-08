#ifndef PESSOA_H
#define PESSOA_H

#include "GameObject.h"
#include "Obstacle.h"

using std::cout;
using std::endl;
using std::string;

class Pessoa: public Obstacle{
public:
    Pessoa();
    ~Pessoa();

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
    void GetXingamentoSound();
    void GetSprite();
    bool isParada;
};

#endif // PESSOA_H
