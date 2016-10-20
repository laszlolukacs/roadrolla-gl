#include "Cylinder.h"

Cylinder::Cylinder()
{
}

Cylinder::Cylinder(float paramA, float paramB, float radius, float height, float resolution) : ParametricSurface(-3.1415926535f, 3.1415926535f, 0.39269908f, 0, height, height / resolution), _paramA(paramA), _paramB(paramB), _radius(radius), _height(height), _resolution(resolution)
{
}

Vector* Cylinder::position(float u, float v)
{
	Vector* result = new Vector;
	result->x = _paramA + _radius * cosf(u);
	result->y = _paramB + _radius * sinf(u);
	result->z = _resolution * v;
	return result;
}

Vector* Cylinder::normal(float u, float v)
{
	Vector rDerivedU(_radius * -(sinf(u)), _radius * cosf(u), 0.0f);
	Vector rDerivedV(0.0f, 0.0f, _resolution);
	Vector* result = new Vector(rDerivedU % rDerivedV);
	return result;
}
