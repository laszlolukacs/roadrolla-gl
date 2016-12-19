#include "ParametricSurface.h"

ParametricSurface::ParametricSurface() : Primitive()
{
	_normals = nullptr;
	_normalsLength = 0;

	_uMin = 0.0f;
	_uMax = 1.0f;
	_uStep = 0.5f;

	_vMin = 0.0f;
	_vMax = 1.0f;
	_vStep = 0.5f;
	_vLength = 0;

}

ParametricSurface::ParametricSurface(float uMin, float uMax, float uStep, float vMin, float vMax, float vStep)
	: Primitive(), _uMin(uMin), _uMax(uMax), _uStep(uStep), _vMin(vMin), _vMax(vMax), _vStep(vStep)
{
	_normals = nullptr;
	_normalsLength = 0;

	_vLength = 0;
}

void ParametricSurface::tesselate()
{
	int numberOfVertices = getNumberOfVertices(_uMin, _uMax, _uStep, _vMin, _vMax, _vStep);

	_verticesLength = 0;
	_vertices = new Vector*[numberOfVertices];

	_normalsLength = 0;
	_normals = new Vector*[numberOfVertices];

	int i = 0;
	for (float u = _uMin; u < _uMax + _uStep; u += _uStep)
	{
		int j = 0;
		for (float v = _vMin; v < _vMax + _vStep; v += _vStep)
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

int ParametricSurface::getNumberOfVertices(float uMin, float uMax, float uStep, float vMin, float vMax, float vStep)
{
	int numberOfVertices = 0;
	for (float u = uMin; u < uMax + uStep; u += uStep)
	{
		_vLength = 0;
		for (float v = vMin; v < vMax + vStep; v += vStep)
		{
			_vLength++;
			numberOfVertices++;
		}
	}

	return numberOfVertices;
}

void ParametricSurface::renderVertexPositionNormalTexture(float u, float v, int i, int j) const
{
	Vector* vertex = _vertices[j + _vLength * i];
	Vector* normal = _normals[j + _vLength * i];

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