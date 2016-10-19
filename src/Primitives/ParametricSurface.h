#ifndef PARAMETRIC_SURFACE_H
#define PARAMETRIC_SURFACE_H

#include "../Primitive.h"
#include "../Vector.h"
#include "../Material.h"

class ParametricSurface : Primitive
{
protected:
	int _normalBufferLength;
	Vector** _normalBuffer;
	float _uMin, _uMax, _uStep;
	float _vMin, _vMax, _vStep;
	int _uLength, _vLength;
	bool _hasShadow;
public:
	float lightX, lightY;
	ParametricSurface();
	ParametricSurface(float uMin, float uMax, float uStep, float vMin, float vMax, float vStep);
	virtual ~ParametricSurface();

	virtual Vector* direction(float u, float v) = 0;
	virtual Vector* normal(float u, float v) = 0;

	virtual Vector r(float u, float v) = 0;
	virtual Vector n(float u, float v) = 0;

	virtual void tesselate() override;
	virtual void render() override;

	virtual void TesselateAndRender_gl()
	{
		Vector rVec, nVec, rVecShadow;

		glEnable(GL_NORMALIZE);
		glBegin(GL_QUADS);
		for (float u = _uMin; u < _uMax; u += _uStep)
		{
			for (float v = _vMin; v < _vMax; v += _vStep)
			{
				rVec = r(u, v);
				nVec = n(u, v);
				glTexCoord2f(u, v);
				glNormal3f(nVec.x, nVec.y, nVec.z);
				glVertex3f(rVec.x, rVec.y, rVec.z);

				rVec = r(u + _uStep, v);
				nVec = n(u + _uStep, v);
				glTexCoord2f(u + _uStep, v);
				glNormal3f(nVec.x, nVec.y, nVec.z);
				glVertex3f(rVec.x, rVec.y, rVec.z);

				rVec = r(u + _uStep, v + _vStep);
				nVec = n(u + _uStep, v);
				glTexCoord2f(u + _uStep, v + _vStep);
				glNormal3f(nVec.x, nVec.y, nVec.z);
				glVertex3f(rVec.x, rVec.y, rVec.z);

				rVec = r(u, v + _vStep);
				nVec = n(u + _uStep, v);
				glTexCoord2f(u, v + _vStep);
				glNormal3f(nVec.x, nVec.y, nVec.z);
				glVertex3f(rVec.x, rVec.y, rVec.z);
			}
		}
		glEnd();
	}
};

#endif