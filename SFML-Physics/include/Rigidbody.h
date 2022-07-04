#pragma once
#include <Vector.h>


enum class BodyType
{
	STATIC,
	DYNAMIC
};

class Rigidbody
{
protected:
	Vector _velocity;
	float _mass;
	BodyType _bodyType;

public:
	Rigidbody();
	~Rigidbody() = default;

	Vector& GetVelocity();
	void SetVelocity(Vector newVel);
	BodyType GetBodyType();
	void SetBodyType(BodyType type);
	float GetMass();
	void SetMass(float newMass);
};
