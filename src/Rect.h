#ifndef RECT_H_
#define RECT_H_

#include <cmath>
#include <iostream>

#include "Vec2.h"

class Rect {
public:
    Rect();
	Rect(float xx, float yy, int ww, int hh);
	~Rect();

	Vec2 CenterPos();
	Vec2 GetCenter() const;
	float Distance(Rect rect1, Rect rect2);
	bool IsInside(float x, float y);
	void Print();
	void Centralize(float x, float y, float w, float h);

	float x,y,w,h;
	float rotation;

	Rect& operator=(const Vec2& vetor);
	Rect operator+(const Vec2& vetor);
	Rect operator-(const Vec2& vetor);
	Rect operator*(const Vec2& vetor);
	Rect operator/(const Vec2& vetor);
};

#endif
