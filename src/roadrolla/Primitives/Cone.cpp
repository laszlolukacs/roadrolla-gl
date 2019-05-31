#include "Cone.h"

Cone::Cone()
{
}

Cone::Cone(float paramA, float paramB, float radius, float height, float resolution)
	: ParametricSurface(0.0f, height, height / (8.0f * resolution), false, 0.0f, 6.2832f, 1.5708f / (2.0f * resolution), true),
	_paramA(paramA), _paramB(paramB), _radius(radius), _height(height), _resolution(resolution)
{
}

Vector* Cone::position(float u, float v)
{
	Vector* result = new Vector();
	float coneDivider = 1.0f - ((u + (_height / 2.0f)) / _height);
	if (coneDivider > 0.0f)
	{
		result->x = _paramA + _radius * coneDivider * cosf(v);
		result->y = 1.0f * u;
		result->z = _paramB + _radius * coneDivider * sinf(v);
	}

	return result;
}

Vector* Cone::normal(float u, float v)
{
	float coneDivider = 1.0f - ((u + (_height / 2.0f)) / _height);
	if (coneDivider != 0.0f)
	{
		Vector rDerivedU(0.0f, 1.0f, 0.0f);
		Vector rDerivedV(_radius * coneDivider * -sinf(v), 0.0f, _radius * coneDivider * cosf(v));
		return new Vector(rDerivedU % rDerivedV);
	}

	return new Vector(0.0f, 0.0f, 0.0f);
}
