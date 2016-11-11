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

	virtual void Build() = 0;
	virtual Vector GetPosition() { return _position; }
	virtual float GetBoundingRadius() { return _boundingRadius; }
	virtual void SetShadowMode(bool isShadowMode) { _isShadowMode = isShadowMode; }
	virtual void SetAcceleration(Vector acceleration) { _acceleration = acceleration; }
	virtual void SetVelocity(Vector velocity) { _velocity = velocity; }
	virtual void SetPosition(Vector position) { _position = position; }
	virtual void Update(float deltaT) = 0;
	virtual void SetTransformations_gl() = 0;
	virtual void TesselateAndRender_gl() = 0;

	virtual ~Actor() {}
};

#endif

