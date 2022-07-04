#include "..\include\Rigidbody.h"

Rigidbody::Rigidbody()
{
	_velocity = Vector(0, 0);
	_mass = 1;
	_bodyType = BodyType::DYNAMIC;
}

Vector& Rigidbody::GetVelocity()
{
	return _velocity;
}

void Rigidbody::SetVelocity(Vector newVel)
{
	_velocity = newVel;
}

BodyType Rigidbody::GetBodyType()
{
	return _bodyType;
}

void Rigidbody::SetBodyType(BodyType type)
{
	_bodyType = type;
}

float Rigidbody::GetMass()
{
	return _mass;
}

void Rigidbody::SetMass(float newMass)
{
	_mass = newMass;
}


