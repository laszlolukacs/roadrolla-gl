#ifndef PLANE_H
#define PLANE_H

#include "ParametricSurface.h"

class Plane : public ParametricSurface
{
private:
	float _height, _resolution;
public:
	Plane();
	Plane(float width, float depth, float height, float resolution);

	Vector* position(float u, float v) override;
	Vector* normal(float u, float v) override;
};

#endif