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

	_vertexBufferLength = 0;
	_vertexBuffer = new Vector*[bufferLength];

	_normalBufferLength = 0;
	_normalBuffer = new Vector*[bufferLength];

	int i = 0;
	for (float u = _uMin; u < _uMax + _uStep; u += _uStep)
	{
		int j = 0;
		for (float v = _vMin; v < _vMax + _vStep; v += _vStep)
		{
			_vertexBuffer[j + _vLength * i] = position(u, v);
			_vertexBufferLength++;

			_normalBuffer[j + _vLength * i] = normal(u, v);
			_normalBufferLength++;

			j++;
		}

		i++;
	}
}

void ParametricSurface::render()
{
	glEnable(GL_NORMALIZE);
	glBegin(GL_TRIANGLES);
	int i = 0;
	for (float u = _uMin; u < _uMax; u += _uStep)
	{
		int j = 0;
		for (float v = _vMin; v < _vMax ; v += _vStep)
		{
			// draws the first triangle of the 'quad', { v0, v1, v2 }
			renderVertexPositionNormalTexture(u, v, i, j);
			renderVertexPositionNormalTexture(u + _uStep, v, i + 1, j);
			renderVertexPositionNormalTexture(u + _uStep, v + _vStep, i + 1, j + 1);

			// draws the second triangle of the 'quad', { v0, v2, v3}
			renderVertexPositionNormalTexture(u, v, i, j);
			renderVertexPositionNormalTexture(u + _uStep, v + _vStep, i + 1, j + 1);
			renderVertexPositionNormalTexture(u, v + _vStep, i, j + 1);

			j++;
		}

		i++;
	}

	glEnd();
}

void ParametricSurface::renderVertexPositionNormalTexture(float u, float v, int i, int j) const
{
	Vector* vertex = _vertexBuffer[j + _vLength * i];
	Vector* normal = _normalBuffer[j + _vLength * i];

	glTexCoord2f(u, v);
	glNormal3f(normal->x, normal->y, normal->z);
	glVertex3f(vertex->x, vertex->y, vertex->z);
}

ParametricSurface::~ParametricSurface()
{
	if (_normalBuffer != nullptr) {
		delete[] _normalBuffer;
		_normalBuffer = nullptr;
		_normalBufferLength = 0;
	}
}