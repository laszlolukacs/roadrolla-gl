#include "Cube.h"

Cube::Cube() : Primitive(), _width(1.0f), _height(1.0f), depth_(1.0f)
{
}

Cube::Cube(float startX, float startY, float startZ, float width, float height, float depth) : Primitive(), _width(width), _height(height), depth_(depth), _start(startX, startY, startZ)
{
}

void Cube::tesselate()
{
	if (_vertices != nullptr) {
		delete[] _vertices;
	}

	_verticesLength = 0;
	_vertices = new Vector*[8];

	float height = -_height;
	float width = -_width;
	float depth = -depth_;

	float x = 0.0f, y = 0.0f, z = 0.0f;
	for (int i = 0; i < 2; i++)
	{
		z = _start.z + i * depth;
		for (int j = 0; j < 2; j++)
		{
			y = _start.y + j * height;
			for (int k = 0; k < 2; k++)
			{
				if ((j == 1) ^ (k == 1))
				{
					x = _start.x + width;
				}
				else
				{
					x = _start.x;
				}

				_vertices[4 * i + 2 * j + k] = new Vector(x, y, z);
				_verticesLength++;
			}
		}
	}
}

void Cube::render()
{
	if (_vertices != nullptr) {
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(_vertices[0]->x, _vertices[0]->y, _vertices[0]->z);
		glVertex3f(_vertices[1]->x, _vertices[1]->y, _vertices[1]->z);
		glVertex3f(_vertices[2]->x, _vertices[2]->y, _vertices[2]->z);
		glVertex3f(_vertices[3]->x, _vertices[3]->y, _vertices[3]->z);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(_vertices[6]->x, _vertices[6]->y, _vertices[6]->z);
		glVertex3f(_vertices[5]->x, _vertices[5]->y, _vertices[5]->z);
		glVertex3f(_vertices[4]->x, _vertices[4]->y, _vertices[4]->z);
		glVertex3f(_vertices[7]->x, _vertices[7]->y, _vertices[7]->z);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(_vertices[0]->x, _vertices[0]->y, _vertices[0]->z);
		glVertex3f(_vertices[4]->x, _vertices[4]->y, _vertices[4]->z);
		glVertex3f(_vertices[5]->x, _vertices[5]->y, _vertices[5]->z);
		glVertex3f(_vertices[1]->x, _vertices[1]->y, _vertices[1]->z);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(_vertices[6]->x, _vertices[6]->y, _vertices[6]->z);
		glVertex3f(_vertices[7]->x, _vertices[7]->y, _vertices[7]->z);
		glVertex3f(_vertices[3]->x, _vertices[3]->y, _vertices[3]->z);
		glVertex3f(_vertices[2]->x, _vertices[2]->y, _vertices[2]->z);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(_vertices[0]->x, _vertices[0]->y, _vertices[0]->z);
		glVertex3f(_vertices[3]->x, _vertices[3]->y, _vertices[3]->z);
		glVertex3f(_vertices[7]->x, _vertices[7]->y, _vertices[7]->z);
		glVertex3f(_vertices[4]->x, _vertices[4]->y, _vertices[4]->z);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(_vertices[6]->x, _vertices[6]->y, _vertices[6]->z);
		glVertex3f(_vertices[2]->x, _vertices[2]->y, _vertices[2]->z);
		glVertex3f(_vertices[1]->x, _vertices[1]->y, _vertices[1]->z);
		glVertex3f(_vertices[5]->x, _vertices[5]->y, _vertices[5]->z);
		glEnd();
	}
}
