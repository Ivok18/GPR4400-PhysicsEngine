#pragma once
#include <iostream>
#include <math.h>

class Vector 
{
protected:
	float x;
	float y;

public:
	Vector();
	Vector(float _x, float _y);
	~Vector();
	
	float GetX();
	float GetY();
	void SetX(float x);
	void SetY(float y);
	void Print();
	float Magnitude();
	float SqrtMagnitude();
	Vector Normalized();
	Vector operator + (Vector& other);
	Vector operator += (Vector& other);

	Vector operator - (Vector& other);
	Vector operator -= (Vector& other);

	float operator / (Vector& other);
	Vector operator / (float divisor);
	Vector operator /= (float divisor);

	float operator * (Vector& other);
	Vector operator * (float multiplier);
	Vector operator *= (float multiplier);
	
	
	
	
};
