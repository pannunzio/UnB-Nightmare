/*
 * Rect.h
 *
 *  Created on: 16 de mar de 2016
 *      Author: Caio
 */

#ifndef RECT_H_
#define RECT_H_

#include "Vec2.h"
#include <cmath>
class Rect {
public:
	Vec2 CenterPos();
	Vec2 GetCenter() const;
	float Distance(Rect rect1, Rect rect2);
	bool IsInside(float x, float y);
	void Print();
	void Centralize(float x, float y, float w, float h);

	Rect(float xx, float yy, int ww, int hh);
	Rect();
	~Rect();
	float x,y,w,h;

	Rect& operator=(const Vec2& vetor);
	Rect operator+(const Vec2& vetor);
	Rect operator-(const Vec2& vetor);
	Rect operator*(const Vec2& vetor);
	Rect operator/(const Vec2& vetor);
};

#endif /* RECT_H_ */
