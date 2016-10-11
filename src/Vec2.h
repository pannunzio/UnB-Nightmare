/*
 * Vec2.h
 *
 *  Created on: 16 de mar de 2016
 *      Author: Caio
 */

#ifndef VEC2_H_
#define VEC2_H_



#include <iostream>
#include <math.h>
#define My_PI 3.14159265

class Vec2 {
public:

	Vec2 Normalized(); // normaliza vetores
	float Magnitude(); // retorna magnitude
	float Distance(Vec2 vetor1, Vec2 vetor2); // retorna distancia entre dois vetores
	float Angle(); // retorna o angulo em relaçao 0,0
	float AngleRad(); // retorna angulo em rad
	float AngleBetween(Vec2 vetor1, Vec2 vetor2) ;// retorna o angulo entre vetores;
	float DistanceTo(Vec2 target);
	void Rotate(float angle); // rotaciona o vetor horario
	//Vec2 Rotate(Vec2 vetor, float angle);
	void SetZero();
	void Set(float xx, float yy);
	void SetX(float xx);
	void SetY(float yy);
	void Print();
	float x,y;
	Vec2();
	Vec2(float xx, float yy);
	~Vec2();

	// operadores de vetores com vetores
	Vec2& operator=(const Vec2& vetor);
	Vec2 operator+(const Vec2& vetor);
	Vec2 operator-(const Vec2& vetor);
	Vec2 operator*(const Vec2& vetor);
	Vec2 operator/(const Vec2& vetor);

	Vec2 operator*(const float& num) const;
	Vec2 operator/(const float& num) const;


};

#endif /* VEC2_H_ */
