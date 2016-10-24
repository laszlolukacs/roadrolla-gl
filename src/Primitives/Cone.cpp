#include "Cone.h"

Cone::Cone()
{
}

Cone::Cone(float paramA, float paramB, float radius, float height, float resolution) : ParametricSurface(-3.1415926535f, 3.1415926535f, 0.39269908f, -(height / 2.0f), (height / 2.0f), height / resolution), _paramA(paramA), _paramB(paramB), _radius(radius), _height(height), _resolution(resolution)
{
}

Vector* Cone::position(float u, float v)
{
	Vector* result = new Vector();
	float coneDivider = 1.0f - ((v + (_height / 2.0f)) / _height);
	if (coneDivider > 0.0f)
	{
		result->x = _paramA + _radius * coneDivider * cosf(u);
		result->y = _resolution * v;
		result->z = _paramB + _radius * coneDivider * sinf(u);
	}

	return result;
}

Vector* Cone::normal(float u, float v)
{
	float coneDivider = 1.0f - ((v + (_height / 2.0f)) / _height);
	if (coneDivider != 0.0f)
	{
		Vector rDerivedU(_radius * coneDivider * -(sinf(u)), 0.0f, _radius * coneDivider * cosf(u));
		Vector rDerivedV(0.0f, _resolution, 0.0f);
		return new Vector(rDerivedU % rDerivedV);
	}

	return new Vector(0.0f, 0.0f, 0.0f);
}
