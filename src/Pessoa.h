#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>

#include "GameObject.h"
#include "Obstacle.h"
#include "Camera.h"

#define MENINA_FILE     "img/menina.png"
#define MENINA_FRAMES   6
#define MENINA_FTIME    0.2

#define MENINO_FILE     "img/menino.png"
#define MENINO_FRAMES   6
#define MENINO_FTIME    0.2

#define OBST_HEIGHT_L3 230
#define OBST_HEIGHT_L2 485
#define OBST_HEIGHT_L1 772


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
private:
    void GetXingamentoSound();
    void GetSprite();
    bool isParada;
    enum{
        MENINA,
        MENINO
    };
};

#endif // PESSOA_H
