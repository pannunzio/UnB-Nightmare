#include <math.h>
#define M_PI 3.14159265
#include "Vec2.h"

#include <iostream>

Vec2::Vec2() {
	x = y = 0;

}

Vec2::~Vec2() {

}

Vec2::Vec2(float xx,float yy){
	x = xx;
	y = yy;
}

void Vec2::SetZero(){
	x = y = 0;
}

Vec2 Vec2::Normalized(){
	Vec2 p(x,y);
	Vec2 norm(x/p.Magnitude(),y/p.Magnitude());
	return norm;
}

float Vec2::Magnitude(){
	return sqrt(x*x + y*y);
}

float Vec2::Distance(Vec2 vetor1, Vec2 vetor2){
	float xx = (vetor1.x - vetor2.x)*(vetor1.x - vetor1.x);
	float yy = (vetor1.y - vetor2.y)*(vetor2.x - vetor2.y);
	Vec2 dist(xx, yy);
	return dist.Magnitude();
}

float Vec2::Angle(){
	float angle = atan2(y,x);
	angle = angle*180/M_PI;
	return angle; // retorna anguglo
};

float Vec2::AngleRad(){
	float angle = atan2(y,x);
	return angle; // retorna anguglo
};

void Vec2::Rotate(float angle){
	angle = angle/180.0 * M_PI;
	// convetido para radianos
	float tempx, tempy;
	tempx = x * cos(angle) - y * sin(angle);
	tempy = x * sin(angle) + y * cos(angle);
	x = tempx;
	y = tempy;
}
//Vec2 Vec2::Rotate(Vec2 vetor, float angle){
//	vetor.Rotate(angle);
//	return vetor;
//}

void Vec2::Print()
{
//	std::cout << "Vector Value(x,y) :  " << x << ", " << y << std::endl;
}

void Vec2::Set(float xx, float yy){
	x = xx;
	y = yy;

}
void Vec2::SetX(float xx){
	x = xx;

}
void Vec2::SetY(float yy){

	y = yy;

}

// Operadores
Vec2& Vec2::operator=(const Vec2& vetor){
	x = vetor.x;
	y = vetor.y;
	return *this;
}
Vec2 Vec2::operator+(const Vec2& vetor){
	return Vec2(x + vetor.x, y + vetor.y);
}

Vec2 Vec2::operator-(const Vec2& vetor){
	return Vec2(x - vetor.x, y - vetor.y);
}

Vec2 Vec2::operator*(const Vec2& vetor){
	return Vec2(x * vetor.x, y * vetor.y);
}

Vec2 Vec2::operator/(const Vec2& vetor){
	return Vec2(x / vetor.x, y / vetor.y);
}

Vec2 Vec2::operator*(const float& num) const{
	return Vec2(x * num, y * num);
}

Vec2 Vec2::operator/(const float& num) const{
	return Vec2(x / num, y / num);
}

float Vec2::DistanceTo(Vec2 target){
	// preguica de usar o abs
	float xx = (x - target.x)*(x - target.x);
	float yy = (y - target.y)*(y - target.y);
	Vec2 dist(xx, yy);
	return dist.Magnitude();
}
