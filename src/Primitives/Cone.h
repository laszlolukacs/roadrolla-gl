#ifndef CONE_H
#define CONE_H

#include "ParametricSurface.h"

class Cone : public ParametricSurface
{
private:
	float _paramA, _paramB, _radius, _height, _resolution;

public:
	Cone();
	Cone(float paramA, float paramB, float radius, float height, float resolution);

	Vector* position(float u, float v) override;
	Vector* normal(float u, float v) override;
};

#endif
