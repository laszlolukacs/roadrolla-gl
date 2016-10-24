#ifndef PARAMETRIC_SURFACE_H
#define PARAMETRIC_SURFACE_H

#include "../Primitive.h"
#include "../Vector.h"

class ParametricSurface : Primitive
{
protected:
	int _normalBufferLength;
	Vector** _normalBuffer;

	float _uMin, _uMax, _uStep;
	float _vMin, _vMax, _vStep;
	int _uLength, _vLength;

	void renderVertexPositionNormalTexture(float u, float v, int i, int j) const;

public:
	ParametricSurface();
	ParametricSurface(float uMin, float uMax, float uStep, float vMin, float vMax, float vStep);

	virtual Vector* position(float u, float v) = 0;
	virtual Vector* normal(float u, float v) = 0;

	virtual void tesselate() override;
	virtual void render() override;

	virtual ~ParametricSurface();
};

#endif