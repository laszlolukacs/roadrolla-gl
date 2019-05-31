#include "ParametricSurface.h"

ParametricSurface::ParametricSurface() : Primitive()
{
	_normals = nullptr;
	_normalsLength = 0;

	_uMin = 0.0f;
	_uMax = 1.0f;
	_uStep = 0.5f;
	_uLoop = false;
	_uLength = 0;

	_vMin = 0.0f;
	_vMax = 1.0f;
	_vStep = 0.5f;
	_vLoop = false;
	_vLength = 0;
}

ParametricSurface::ParametricSurface(float uMin, float uMax, float uStep, bool uLoop, float vMin, float vMax, float vStep, bool vLoop)
	: Primitive(), _uMin(uMin), _uMax(uMax), _uStep(uStep), _uLoop(uLoop), _vMin(vMin), _vMax(vMax), _vStep(vStep), _vLoop(vLoop)
{
	_normals = nullptr;
	_normalsLength = 0;

	_uLength = 0;
	_vLength = 0;
}

void ParametricSurface::tesselate()
{
	float uMax, vMax;
	_uLoop ? uMax = _uMax : uMax = _uMax + _uStep;
	_vLoop ? vMax = _vMax : vMax = _vMax + _vStep;
	int numberOfVertices = getNumberOfVertices(_uMin, uMax, _uStep, _vMin, vMax, _vStep);

	_verticesLength = 0;
	_vertices = new Vector*[numberOfVertices];

	_normalsLength = 0;
	_normals = new Vector*[numberOfVertices];

	int i = 0;
	for (float u = _uMin; u < uMax; u += _uStep)
	{
		int j = 0;
		for (float v = _vMin; v < vMax; v += _vStep)
		{
			_vertices[j + _vLength * i] = position(u, v);
			_verticesLength++;

			_normals[j + _vLength * i] = normal(u, v);
			_normalsLength++;

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
		for (float v = _vMin; v < _vMax; v += _vStep)
		{
			// vertices of a 'quad':
			// v0 = i, j
			// v1 = i+1, j
			// v2 = i+1, j+1
			// v3 = i, j+1

			// draws the first triangle of the 'quad', { v0, v1, v3 }
			renderVertexPositionNormalTexture(u, v, i, j);
			renderVertexPositionNormalTexture(u + _uStep, v, i + 1, j);
			renderVertexPositionNormalTexture(u, v + _vStep, i, j + 1);

			//// draws the second triangle of the 'quad', { v1, v2, v3}
			renderVertexPositionNormalTexture(u + _uStep, v, i + 1, j);
			renderVertexPositionNormalTexture(u + _uStep, v + _vStep, i + 1, j + 1);
			renderVertexPositionNormalTexture(u, v + _vStep, i, j + 1);

			j++;
		}

		i++;
	}

	glEnd();
}

int ParametricSurface::getNumberOfVertices(float uMin, float uMax, float uStep, float vMin, float vMax, float vStep)
{
	int numberOfVertices = 0;
	_uLength = 0;
	for (float u = uMin; u < uMax; u += uStep)
	{
		_vLength = 0;
		for (float v = vMin; v < vMax; v += vStep)
		{
			_vLength++;
			numberOfVertices++;
		}

		_uLength++;
	}

	return numberOfVertices;
}

void ParametricSurface::renderVertexPositionNormalTexture(float u, float v, int i, int j) const
{
	// edge cases for looping surfaces
	if (i >= _uLength)
	{
		i = 0;
	}

	if (j >= _vLength)
	{
		j = 0;
	}

	int index = j + _vLength * i;
	Vector* normal = _normals[index];
	Vector* vertex = _vertices[index];

	glTexCoord2f(u, v);
	glNormal3f(normal->x, normal->y, normal->z);
	glVertex3f(vertex->x, vertex->y, vertex->z);
}

ParametricSurface::~ParametricSurface()
{
	if (_normals != nullptr) {
		delete[] _normals;
		_normals = nullptr;
		_normalsLength = 0;
	}
}