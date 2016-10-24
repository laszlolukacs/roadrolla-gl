#include "Cube.h"

Cube::Cube() : Primitive(), _width(1.0f), _height(1.0f), depth_(1.0f)
{
}

Cube::Cube(float startX, float startY, float startZ, float width, float height, float depth) : Primitive(), _width(width), _height(height), depth_(depth), _start(startX, startY, startZ)
{
}

void Cube::tesselate()
{
	if (_vertexBuffer != nullptr) {
		delete[] _vertexBuffer;
	}

	_vertexBufferLength = 0;
	_vertexBuffer = new Vector*[8];

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

				_vertexBuffer[4 * i + 2 * j + k] = new Vector(x, y, z);
				_vertexBufferLength++;
			}
		}
	}
}

void Cube::render()
{
	if (_vertexBuffer != nullptr) {
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(_vertexBuffer[0]->x, _vertexBuffer[0]->y, _vertexBuffer[0]->z);
		glVertex3f(_vertexBuffer[1]->x, _vertexBuffer[1]->y, _vertexBuffer[1]->z);
		glVertex3f(_vertexBuffer[2]->x, _vertexBuffer[2]->y, _vertexBuffer[2]->z);
		glVertex3f(_vertexBuffer[3]->x, _vertexBuffer[3]->y, _vertexBuffer[3]->z);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(_vertexBuffer[6]->x, _vertexBuffer[6]->y, _vertexBuffer[6]->z);
		glVertex3f(_vertexBuffer[5]->x, _vertexBuffer[5]->y, _vertexBuffer[5]->z);
		glVertex3f(_vertexBuffer[4]->x, _vertexBuffer[4]->y, _vertexBuffer[4]->z);
		glVertex3f(_vertexBuffer[7]->x, _vertexBuffer[7]->y, _vertexBuffer[7]->z);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(_vertexBuffer[0]->x, _vertexBuffer[0]->y, _vertexBuffer[0]->z);
		glVertex3f(_vertexBuffer[4]->x, _vertexBuffer[4]->y, _vertexBuffer[4]->z);
		glVertex3f(_vertexBuffer[5]->x, _vertexBuffer[5]->y, _vertexBuffer[5]->z);
		glVertex3f(_vertexBuffer[1]->x, _vertexBuffer[1]->y, _vertexBuffer[1]->z);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(_vertexBuffer[6]->x, _vertexBuffer[6]->y, _vertexBuffer[6]->z);
		glVertex3f(_vertexBuffer[7]->x, _vertexBuffer[7]->y, _vertexBuffer[7]->z);
		glVertex3f(_vertexBuffer[3]->x, _vertexBuffer[3]->y, _vertexBuffer[3]->z);
		glVertex3f(_vertexBuffer[2]->x, _vertexBuffer[2]->y, _vertexBuffer[2]->z);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(_vertexBuffer[0]->x, _vertexBuffer[0]->y, _vertexBuffer[0]->z);
		glVertex3f(_vertexBuffer[3]->x, _vertexBuffer[3]->y, _vertexBuffer[3]->z);
		glVertex3f(_vertexBuffer[7]->x, _vertexBuffer[7]->y, _vertexBuffer[7]->z);
		glVertex3f(_vertexBuffer[4]->x, _vertexBuffer[4]->y, _vertexBuffer[4]->z);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(_vertexBuffer[6]->x, _vertexBuffer[6]->y, _vertexBuffer[6]->z);
		glVertex3f(_vertexBuffer[2]->x, _vertexBuffer[2]->y, _vertexBuffer[2]->z);
		glVertex3f(_vertexBuffer[1]->x, _vertexBuffer[1]->y, _vertexBuffer[1]->z);
		glVertex3f(_vertexBuffer[5]->x, _vertexBuffer[5]->y, _vertexBuffer[5]->z);
		glEnd();
	}
}
