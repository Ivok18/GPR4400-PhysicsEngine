#include "Vector.h";

Vector::Vector()
{
	x = 0;
	y = 0;
}
Vector::Vector(float _x, float _y)
{
	x = _x;
	y = _y;
}
Vector::~Vector()
{

}

float Vector::GetX()
{
	return x;
}
float Vector::GetY()
{
	return y;
}
void Vector::SetX(float x)
{
	this->x = x;
}
void Vector::SetY(float y)
{
	this->y = y;
}

void Vector::Print()
{
	std::cout << "X pos: " << x << std::endl;
	std::cout << "Y pos: " << y << std::endl << std::endl;
}
float Vector::SqrtMagnitude()
{
	float sqrtMagnitude = x * x + y * y;
	return sqrtMagnitude;
}
float Vector::Magnitude()
{
	float magnitude = std::sqrtf(SqrtMagnitude());
	return magnitude;
}
Vector Vector::Normalized()
{
	float normalizeX = x / std::abs(Magnitude());
	float normalizeY = y / std::abs(Magnitude());
	Vector normalizedVector(normalizeX, normalizeY);
	return normalizedVector;
}

Vector Vector::operator + (Vector& other)
{
	Vector result(x + other.x, y + other.y);
	return result;
}
Vector Vector::operator += (Vector& other)
{
	x += other.x;
	y += other.y;

	return Vector(x, y);

}

Vector Vector::operator - (Vector& other)
{
	Vector result(x - other.x, y - other.y);
	return result;
}
Vector Vector::operator -= (Vector& other)
{
	x -= other.x;
	y -= other.y;

	return Vector(x, y);
}

float Vector::operator * (Vector& other)
{
	Vector vectorNormalized1 = Vector(x, y).Normalized();
	Vector vectorNormalized2 = other.Normalized();
	return vectorNormalized1.x * vectorNormalized2.x + vectorNormalized1.y * vectorNormalized2.y;
}
Vector Vector::operator * (float multiplier)
{
	return Vector(x * multiplier, y * multiplier);
}
Vector Vector::operator *= (float multiplier)
{
	x *= multiplier;
	y *= multiplier;

	return Vector(x, y);
}

float Vector::operator / (Vector& other)
{
	Vector myVector(x, y);
	return 1.f / (myVector * other);
}
Vector Vector::operator / (float divisor)
{
	Vector result;
	if (divisor != 0) 
	{
		result = Vector(x / divisor, y / divisor);
	}

	return result;
	
}
Vector Vector::operator /= (float divisor)
{
	Vector result;
	if (divisor == 0)
	{
		x /= divisor;
		y /= divisor;
		result = Vector(x, y);
	}

	return result;

}




