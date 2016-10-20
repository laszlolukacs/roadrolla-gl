#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "ParametricSurface.h"

class Ellipsoid : public ParametricSurface
{
private:
	float _paramA, _paramB, _paramC;
public:
	Ellipsoid();
	Ellipsoid(float paramA, float paramB, float paramC);

	Vector* position(float u, float v) override;
	Vector* normal(float u, float v) override;

	Vector r(float u, float v)
	{
		Vector result;
		result.x = _paramA * cosf(u) * cosf(v);
		result.y = _paramB * cosf(u) * sinf(v);
		result.z = _paramC * sinf(u);
		return result;
	}

	Vector n(float u, float v)
	{
		Vector result;
		Vector rDerivedU(_paramA * -sinf(u) * cosf(v), _paramB * -sinf(u) * sinf(v), _paramC * cosf(u));
		Vector rDerivedV(_paramA * cosf(u) * -sinf(v), _paramB * cosf(u) * cosf(v), 0.0f);
		result = rDerivedU % rDerivedV;
		return result;
	}
};
#endif
