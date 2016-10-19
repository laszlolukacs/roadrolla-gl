#include "ParametricSurface.h"

ParametricSurface::ParametricSurface() : Primitive()
{
	_normalBuffer = nullptr;
	_normalBufferLength = 0;
}

ParametricSurface::ParametricSurface(float uMin, float uMax, float uStep, float vMin, float vMax, float vStep) : Primitive(), _uMin(uMin), _uMax(uMax), _uStep(uStep), _vMin(vMin), _vMax(vMax), _vStep(vStep)
{
	_normalBuffer = nullptr;
	_normalBufferLength = 0;
}

void ParametricSurface::tesselate()
{
	int bufferLength = 0;
	_uLength = 0;
	for (float u = _uMin; u < _uMax + _uStep; u += _uStep)
	{
		_uLength++;
		_vLength = 0;
		for (float v = _vMin; v < _vMax + _vStep; v += _vStep)
		{
			_vLength++;
			bufferLength++;
		}
	}

	if (_vertexBuffer != nullptr) {
		delete[] _vertexBuffer;
	}

	_vertexBufferLength = 0;
	_vertexBuffer = new Vector*[bufferLength];

	if (_normalBuffer != nullptr) {
		delete[] _normalBuffer;
	}

	_normalBufferLength = 0;
	_normalBuffer = new Vector*[bufferLength];

	int i = 0;
	for (float u = _uMin; u < _uMax + _uStep; u += _uStep)
	{
		int j = 0;
		for (float v = _vMin; v < _vMax + _vStep; v += _vStep)
		{
			_vertexBuffer[j + (_vLength - 1) * i] = direction(u, v);
			_vertexBufferLength++;

			_normalBuffer[j + (_vLength - 1) * i] = normal(u, v);
			_normalBufferLength++;

			j++;
		}

		i++;
	}
}

void ParametricSurface::render()
{
	Vector* rVec;
	Vector* nVec;

	glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);
	int i = 0;
	for (float u = _uMin; u < _uMax; u += _uStep)
	{
		int j = 0;
		for (float v = _vMin; v < _vMax; v += _vStep)
		{
			rVec = _vertexBuffer[j + (_vLength - 2) * i];
			nVec = _normalBuffer[j + (_vLength - 2) * i];
			glTexCoord2f(u, v);
			glNormal3f(nVec->x, nVec->y, nVec->z);
			glVertex3f(rVec->x, rVec->y, rVec->z);

			rVec = _vertexBuffer[j + (_vLength - 2) * (i + 1)];
			nVec = _normalBuffer[j + (_vLength - 2) * (i + 1)];
			glTexCoord2f(u + _uStep, v);
			glNormal3f(nVec->x, nVec->y, nVec->z);
			glVertex3f(rVec->x, rVec->y, rVec->z);

			rVec = _vertexBuffer[(j + 1) + (_vLength - 2) * (i + 1)];
			nVec = _normalBuffer[(j + 1) + (_vLength - 2) * (i + 1)];
			glTexCoord2f(u + _uStep, v + _vStep);
			glNormal3f(nVec->x, nVec->y, nVec->z);
			glVertex3f(rVec->x, rVec->y, rVec->z);

			rVec = _vertexBuffer[(j + 1) + (_vLength - 2) * i];
			nVec = _normalBuffer[(j + 1) + (_vLength - 2) * i];
			glTexCoord2f(u, v + _vStep);
			glNormal3f(nVec->x, nVec->y, nVec->z);
			glVertex3f(rVec->x, rVec->y, rVec->z);

			j++;
		}

		i++;
	}

	glEnd();
}

ParametricSurface::~ParametricSurface()
{
	if (_normalBuffer != nullptr) {
		delete[] _normalBuffer;
		_normalBuffer = nullptr;
		_normalBufferLength = 0;
	}
}