#include "Ellipsoid.h"

Ellipsoid::Ellipsoid()
{
}

Ellipsoid::Ellipsoid(float paramA, float paramB, float paramC) :
	ParametricSurface(0.0f, 6.2832f, 1.5708f / (8.0f * 1.0f), true, 0.0f, 3.1415f, 1.5708f / (8.0f * 1.0f), false), _paramA(paramA), _paramB(paramB), _paramC(paramC)
{
}

Ellipsoid::Ellipsoid(float paramA, float paramB, float paramC, float uMin, float uMax, float uStep, float vMin, float vMax, float vStep) :
	ParametricSurface(uMin, uMax, uStep, true, vMin, vMax, vStep, true), _paramA(paramA), _paramB(paramB), _paramC(paramC)
{
}

Vector* Ellipsoid::position(float u, float v)
{
	Vector* result = new Vector;
	result->x = _paramA * cosf(u) * sinf(v);
	result->y = _paramC * cosf(v);
	result->z = _paramB * sinf(u) * sinf(v);
	return result;
}

Vector* Ellipsoid::normal(float u, float v)
{
	Vector rDerivedU(_paramA * -sinf(u) * sinf(v), 0.0f, _paramB * cosf(u) * sinf(v));
	Vector rDerivedV(_paramA * cosf(u) * cosf(v), _paramC * -sinf(v), _paramB * sinf(u) * cosf(v));

	Vector* result = new Vector(rDerivedU % rDerivedV);
	return result;
}
