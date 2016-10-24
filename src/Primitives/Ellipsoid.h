#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "ParametricSurface.h"

class Ellipsoid : public ParametricSurface
{
private:
	float _paramA, _paramB, _paramC;

public:
	Ellipsoid();
	Ellipsoid(float paramA, float paramB, float paramC);

	Vector* position(float u, float v) override;
	Vector* normal(float u, float v) override;
};

#endif
