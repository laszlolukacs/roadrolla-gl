#include "Plane.h"

Plane::Plane()
{
}

Plane::Plane(float width, float depth, float height, float resolution) :
	ParametricSurface(0.0f, width, width / resolution, false, 0.0f, depth, depth / resolution, false),
	_height(height), _resolution(resolution)
{
}

Vector* Plane::position(float u, float v)
{
	Vector* result = new Vector();
	result->x = _resolution * u;
	result->y = _height;
	result->z = _resolution * v;
	return result;
}

Vector* Plane::normal(float u, float v)
{
	Vector rDerivedU(_resolution, 0.0f, 0.0f);
	Vector rDerivedV(0.0f, 0.0f, _resolution);
	return new Vector(rDerivedU % rDerivedV);
}
