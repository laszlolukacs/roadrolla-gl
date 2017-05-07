#include "Ellipsoid.h"

Ellipsoid::Ellipsoid()
{
}

Ellipsoid::Ellipsoid(float paramA, float paramB, float paramC) :
	ParametricSurface(-1.57079632f, 1.57079632f, 0.19634954f, -3.1415926535f, 3.1415926535f, 0.39269908f), _paramA(paramA), _paramB(paramB), _paramC(paramC)
{
}

Ellipsoid::Ellipsoid(float paramA, float paramB, float paramC, float uMin, float uMax, float uStep, float vMin, float vMax, float vStep) :
	ParametricSurface(uMin, uMax, uStep, vMin, vMax, vStep), _paramA(paramA), _paramB(paramB), _paramC(paramC)
{
}

Vector* Ellipsoid::position(float u, float v)
{
	Vector* result = new Vector;
	result->x = _paramA * cosf(u) * cosf(v);
	result->y = _paramC * sinf(u);
	result->z = _paramB * cosf(u) * sinf(v);
	return result;
}

Vector* Ellipsoid::normal(float u, float v)
{
	Vector rDerivedU(_paramA * -sinf(u) * cosf(v), _paramC * cos(u), _paramB * -sinf(u) * sinf(v));
	Vector rDerivedV(_paramA * cosf(u) * -sinf(v), 0.0f, _paramB * cosf(u) * cosf(v));

	Vector* result = new Vector(rDerivedU % rDerivedV);
	return result;
}
