#include "ParametricSurface.h"

ParametricSurface::ParametricSurface()
{
}

ParametricSurface::ParametricSurface(float uMin, float uMax, float uStep, float vMin, float vMax, float vStep) : _uMin(uMin), _uMax(uMax), _uStep(uStep), _vMin(vMin), _vMax(vMax), _vStep(vStep)
{
}

void ParametricSurface::tesselate()
{
	Vector rVec, nVec, rVecShadow;

	for (float u = _uMin; u < _uMax; u += _uStep)
	{
		for (float v = _vMin; v < _vMax; v += _vStep)
		{
			rVec = r(u, v);
			nVec = n(u, v);
			//glTexCoord2f(u, v);
			//glNormal3f(nVec.x, nVec.y, nVec.z);
			//glVertex3f(rVec.x, rVec.y, rVec.z);

			rVec = r(u + _uStep, v);
			nVec = n(u + _uStep, v);
			//glTexCoord2f(u + _uStep, v);
			//glNormal3f(nVec.x, nVec.y, nVec.z);
			//glVertex3f(rVec.x, rVec.y, rVec.z);

			rVec = r(u + _uStep, v + _vStep);
			nVec = n(u + _uStep, v);
			//glTexCoord2f(u + _uStep, v + _vStep);
			//glNormal3f(nVec.x, nVec.y, nVec.z);
			//glVertex3f(rVec.x, rVec.y, rVec.z);

			rVec = r(u, v + _vStep);
			nVec = n(u + _uStep, v);
		}
	}
}

void ParametricSurface::render()
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
