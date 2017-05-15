#include "Cylinder.h"

Cylinder::Cylinder()
{
}

Cylinder::Cylinder(float radius, float height, float fineness) :
	ParametricSurface(0.0f, height, height / fineness, -3.1416f, 3.1416f, 0.3927f),
	_radius(radius), _height(height), _resolution(fineness)
{
}

Vector* Cylinder::position(float u, float v)
{
	Vector* result = new Vector;
	result->x = _radius * cosf(v);
	result->y = _resolution * u;
	result->z = _radius * sinf(v);
	return result;
}

Vector* Cylinder::normal(float u, float v)
{
	Vector rDerivedV(_radius * -sinf(v), 0.0f, _radius * cosf(v));
	Vector rDerivedU(0.0f, _resolution, 0.0f);
	Vector* result = new Vector(rDerivedU % rDerivedV);
	return result;
}
