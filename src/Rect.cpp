#include "Rect.h"

Rect::Rect() {
	x = y = w = h = 0;
}

Rect::Rect(float xx, float yy, int ww, int hh){
	x = xx;
	y = yy;
	w = ww;
	h = hh;
}

Rect::~Rect() {
}

Vec2 Rect::CenterPos(){
		Vec2 centro(x + w/2.0, y + h/2.0);
		return centro;
}

Vec2 Rect::GetCenter() const{

	return Vec2(x + w/2.0, y + h/2.0);
}

void Rect::Print(){
		std::cout << std::endl << "(X,Y)(" << x << ", " << y << ")" << std::endl;
		std::cout << "   ________" << w << "________" << std::endl;
		std::cout << "   |\n   |\n   |\n " << h << "\n   |\n   |\n" << std::endl;
}

bool Rect::IsInside(float xx, float yy){
	if(xx < this->x || yy < this->y)
		return false;
	if(xx > this->x + this->w || yy > this->y + this->h)
		return false;
	return true;
}

float Rect::Distance(Rect rect1, Rect rect2){
	Vec2 center1 = rect1.CenterPos();
	Vec2 center2 = rect2.CenterPos();
	return std::abs(center1.Magnitude() - center2.Magnitude());
}

void Rect::Centralize(float x, float y, float w, float h){
	this->x = x - w/2;
	this->y = y - h/2;
	this->w = w;
	this->h = h;
}

// Operadores
Rect& Rect::operator=(const Vec2& vetor){
	this->x = vetor.x;
	this->y = vetor.y;
	return *this;
}

Rect Rect::operator+(const Vec2& vetor){
	return Rect(this->x + vetor.x, this->y + vetor.y, this->w, this->h);
}

Rect Rect::operator-(const Vec2& vetor){
	return Rect(this->x - vetor.x, this->y - vetor.y, this->w, this->h);
}

Rect Rect::operator*(const Vec2& vetor) {
	return Rect(this->x * vetor.x, this->y * vetor.y, this->w, this->h);
}

Rect Rect::operator/(const Vec2& vetor){
	return Rect(this->x / vetor.x, this->y / vetor.y, this->w, this->h);
}
