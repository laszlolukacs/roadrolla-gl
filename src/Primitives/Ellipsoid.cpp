#include "Ellipsoid.h"

Ellipsoid::Ellipsoid()
{
}

Ellipsoid::Ellipsoid(float paramA, float paramB, float paramC) : ParametricSurface(-1.57079632f, 1.57079632f, 0.19634954f, -3.1415926535f, 3.1415926535f, 0.39269908f), _paramA(paramA), _paramB(paramB), _paramC(paramC)
{
}

Vector* Ellipsoid::position(float u, float v)
{
	Vector* result = new Vector;
	result->x = _paramA * cosf(u) * cosf(v);
	result->y = _paramB * cosf(u) * sinf(v);
	result->z = _paramC * sinf(u);
	return result;
}

Vector* Ellipsoid::normal(float u, float v)
{
	Vector rDerivedU(_paramA * -sinf(u) * cosf(v), _paramB * -sinf(u) * sinf(v), _paramC * cosf(u));
	Vector rDerivedV(_paramA * cosf(u) * -sinf(v), _paramB * cosf(u) * cosf(v), 0.0f);
	Vector* result = new Vector(rDerivedU % rDerivedV);
	return result;
}
