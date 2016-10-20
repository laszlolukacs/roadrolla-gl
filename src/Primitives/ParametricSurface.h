#ifndef PARAMETRIC_SURFACE_H
#define PARAMETRIC_SURFACE_H

#include "../Primitive.h"
#include "../Vector.h"

class ParametricSurface : Primitive
{
private:
	void renderVertexPositionNormalTexture(float u, float v, int i, int j) const;

protected:
	int _normalBufferLength;
	Vector** _normalBuffer;

	float _uMin, _uMax, _uStep;
	float _vMin, _vMax, _vStep;

	int _uLength, _vLength;

public:
	float lightX, lightY;
	ParametricSurface();
	ParametricSurface(float uMin, float uMax, float uStep, float vMin, float vMax, float vStep);
	virtual ~ParametricSurface();

	virtual Vector* position(float u, float v) = 0;
	virtual Vector* normal(float u, float v) = 0;

	virtual void tesselate() override;
	virtual void render() override;
};

#endif