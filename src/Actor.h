#ifndef ACTOR_H
#define ACTOR_H

#include "Vector.h"
#include "Material.h"

class Actor
{
protected:
	bool _isShadowMode;
	float _boundingRadius;
	Vector _acceleration;
	Vector _velocity;
	Vector _position;
	Material _material;

public:
	Actor() {}

	virtual void build() = 0;
	virtual Vector getPosition() { return _position; }
	virtual float getBoundingRadius() { return _boundingRadius; }
	virtual void setShadowMode(bool isShadowMode) { _isShadowMode = isShadowMode; }
	virtual void setAcceleration(Vector acceleration) { _acceleration = acceleration; }
	virtual void setVelocity(Vector velocity) { _velocity = velocity; }
	virtual void setPosition(Vector position) { _position = position; }
	virtual void update(float deltaT) = 0;
	virtual void setTransformations() = 0;
	virtual void render() = 0;

	virtual ~Actor() {}
};

#endif

