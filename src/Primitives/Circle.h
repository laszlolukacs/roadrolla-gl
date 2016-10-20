#ifndef CIRCLE_H
#define CIRCLE_H

#include "../Vector.h"
#include "ParametricSurface.h"

class Circle : public ParametricSurface
{
private:
	float _paramA, _paramB, _radius, _resolution;
public:
	Circle() {}
	Circle(float paramA_in, float paramB_in, float radius_in, float resolution_in) : ParametricSurface(-3.1415926535f, 3.1415926535f, 0.39269908f, -3.1415926535f, 3.1415926535f, 0.39269908f), _paramA(paramA_in), _paramB(paramB_in), _radius(radius_in), _resolution(resolution_in) {}

	Vector* position(float u, float v) override;
	Vector* normal(float u, float v) override;

	Vector r(float u, float v)
	{
		Vector result;
		result.x = _paramA + cosf(u) * cosf(v);
		result.y = _paramB + cosf(u) * sinf(v);
		result.z = 0.0f;
		return result;
	}

	Vector n(float u, float v)
	{
		Vector rDerivedU(-sinf(u) * cosf(v), -sinf(u) * cosf(v), 0.0f);
		Vector rDerivedV(cosf(u) * -sinf(v), cosf(u) * -sinf(v), 0.0f);
		return rDerivedU % rDerivedV;
	}
};

#endif