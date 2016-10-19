#include "Circle.h"

Vector* Circle::direction(float u, float v)
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
	Vector result = rDerivedU % rDerivedV;
	return &result;
}