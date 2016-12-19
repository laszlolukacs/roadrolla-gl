#ifndef CIRCLE_H
#define CIRCLE_H

#include "../Vector.h"
#include "ParametricSurface.h"

class Circle : public ParametricSurface
{
private:
	float _paramA, _paramB, _radius, _resolution;

public:
	Circle();
	Circle(float paramA, float paramB, float radius, float resolution);

	Vector* position(float u, float v) override;
	Vector* normal(float u, float v) override;
};

#endif