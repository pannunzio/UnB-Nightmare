#ifndef PESSOAZUMBI_H
#define PESSOAZUMBI_H

#include "GameObject.h"
#include "Obstacle.h"
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

private:
    void GetSprite();
    void GetZombieSound();
    void ChangeSprite();
};

#endif // PESSOAZUMBI_H
