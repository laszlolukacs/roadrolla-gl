#include "Cylinder.h"

Cylinder::Cylinder()
{
}

Cylinder::Cylinder(float radius, float height, float fineness) :
	ParametricSurface(0.0f, height, height, false, 0.0f, 6.2832f, 1.5708f / (2.0f * fineness), true),
	_radius(radius), _height(height), _resolution(fineness)
{
}

Vector* Cylinder::position(float u, float v)
{
	Vector* result = new Vector;
	result->x = _radius * cosf(v);
	result->y = 1.0f * u;
	result->z = _radius * sinf(v);
	return result;
}

Vector* Cylinder::normal(float u, float v)
{
	Vector rDerivedU(0.0f, 1.0f, 0.0f);
	Vector rDerivedV(_radius * -sinf(v), 0.0f, _radius * cosf(v));
	Vector* result = new Vector(rDerivedU % rDerivedV);
	return result;
}
