#ifndef ROADROLLER_H
#define ROADROLLER_H

#include "../Actor.h"
#include "../Primitives/Circle.h"
#include "../Primitives/Cylinder.h"
#include "../Primitives/Cube.h"
#include "../Textures/WheelTexture.h"

class RoadRoller : public Actor
{
private:
	float _rotateVelocity;
	float _rotateFi;
	Circle* _wheelSide;
	Cylinder *_wheel, *_exhaust;
	Cube* _chassis[4];
	WheelTexture _texture;
	Material _chassisMaterial, _wheelMaterial;

public:
	RoadRoller();
	void build() override;
	void update(float deltaT) override;
	void setTransformations() override;
	void render() override;
	~RoadRoller();
};


#endif // ROADROLLER_H

