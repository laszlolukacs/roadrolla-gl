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
	result->y = _paramB + cosf(u) * sinf(v);
	result->z = 0.0f;
	return result;
}

Vector* Circle::normal(float u, float v)
{
	Vector rDerivedU(-sinf(u) * cosf(v), -sinf(u) * cosf(v), 0.0f);
	Vector rDerivedV(cosf(u) * -sinf(v), cosf(u) * -sinf(v), 0.0f);
	Vector* result = new Vector(rDerivedU % rDerivedV);
	return result;
}