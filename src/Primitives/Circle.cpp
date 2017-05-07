#include "Circle.h"

Circle::Circle()
{
}

Circle::Circle(float paramA, float paramB, float radius, float resolution) : ParametricSurface(-3.1415926535f, 3.1415926535f, 0.39269908f, -3.1415926535f, 3.1415926535f, 0.39269908f), _paramA(paramA), _paramB(paramB), _radius(radius), _resolution(resolution)
{
}

Vector* Circle::position(float u, float v)
{
	Vector* result = new Vector();
	result->x = _paramA + cosf(u) * cosf(v);
	result->y = 0.0f;
	result->z = _paramB + cosf(u) * sinf(v);
	return result;
}

Vector* Circle::normal(float u, float v)
{
	Vector rDerivedU(-sinf(u) * cosf(v), 0.0f, -sinf(u) * cosf(v));
	Vector rDerivedV(cosf(u) * -sinf(v), 0.0f, cosf(u) * -sinf(v));
	Vector* result = new Vector(rDerivedU % rDerivedV);
	return result;
}