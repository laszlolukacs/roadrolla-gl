#ifndef CHICKEN_H
#define CHICKEN_H

#include "../Actor.h"
#include "../Primitives/Ellipsoid.h"
#include "../Primitives/Cylinder.h"
#include "../Primitives/Cone.h"

class Chicken : public Actor
{
private:
	bool _isAlive;
	bool _isMoving;

	Ellipsoid *_body, *_head, *_eye, *_knee;
	Cylinder *_neck, *_upperLeg;
	Cone *_beak, *_mohawk;

	Material _eyeMaterial;
	Material _bodyMaterial;
	Material _limbMaterial;

public:
	Chicken();

	void build() override;

	bool isAlive()
	{
		return _isAlive;
	}

	bool isMoving()
	{
		return _isMoving;
	}

	void setPosition(Vector position) override
	{
		_position = position;
	}

	void setTransformations() override;

	void setIsMoving(bool isMoving) { _isMoving = isMoving; }

	void setStillAlive(bool isStillAlive) { _isAlive = isStillAlive; }

	void update(float deltaT) override;

	void render() override;

	~Chicken();
};

#endif // CHICKEN_H