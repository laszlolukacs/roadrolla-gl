#ifndef CYLINDER_H
#define CYLINDER_H

#include "ParametricSurface.h"

class Cylinder : public ParametricSurface
{
private:
	float _paramA, _paramB, _radius, _height, _resolution;
public:
	Cylinder();
	Cylinder(float paramA, float paramB, float radius, float height, float resolution);

	Vector* position(float u, float v) override;
	Vector* normal(float u, float v) override;
};

#endif