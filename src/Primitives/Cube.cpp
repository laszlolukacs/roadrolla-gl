#include "Cube.h"

Cube::Cube() : _width(1.0f), _height(1.0f), depth_(1.0f)
{
	pVertexBuffer_ = nullptr;
	vertexBufferLength_ = 0;
}

Cube::Cube(float startX, float startY, float startZ, float width, float height, float depth) : _width(width), _height(height), depth_(depth), _start(startX, startY, startZ)
{
	pVertexBuffer_ = nullptr;
	vertexBufferLength_ = 0;
}

void Cube::tesselate()
{
	if (pVertexBuffer_ != nullptr) {
		delete[] pVertexBuffer_;
	}

	vertexBufferLength_ = 0;
	pVertexBuffer_ = new Vector*[8];

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

				pVertexBuffer_[4 * i + 2 * j + k] = new Vector(x, y, z);
				vertexBufferLength_++;
			}
		}
	}
}

void Cube::render()
{
	if (pVertexBuffer_ != nullptr) {
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(pVertexBuffer_[0]->x, pVertexBuffer_[0]->y, pVertexBuffer_[0]->z);
		glVertex3f(pVertexBuffer_[1]->x, pVertexBuffer_[1]->y, pVertexBuffer_[1]->z);
		glVertex3f(pVertexBuffer_[2]->x, pVertexBuffer_[2]->y, pVertexBuffer_[2]->z);
		glVertex3f(pVertexBuffer_[3]->x, pVertexBuffer_[3]->y, pVertexBuffer_[3]->z);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(pVertexBuffer_[6]->x, pVertexBuffer_[6]->y, pVertexBuffer_[6]->z);
		glVertex3f(pVertexBuffer_[5]->x, pVertexBuffer_[5]->y, pVertexBuffer_[5]->z);
		glVertex3f(pVertexBuffer_[4]->x, pVertexBuffer_[4]->y, pVertexBuffer_[4]->z);
		glVertex3f(pVertexBuffer_[7]->x, pVertexBuffer_[7]->y, pVertexBuffer_[7]->z);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(pVertexBuffer_[0]->x, pVertexBuffer_[0]->y, pVertexBuffer_[0]->z);
		glVertex3f(pVertexBuffer_[4]->x, pVertexBuffer_[4]->y, pVertexBuffer_[4]->z);
		glVertex3f(pVertexBuffer_[5]->x, pVertexBuffer_[5]->y, pVertexBuffer_[5]->z);
		glVertex3f(pVertexBuffer_[1]->x, pVertexBuffer_[1]->y, pVertexBuffer_[1]->z);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(pVertexBuffer_[6]->x, pVertexBuffer_[6]->y, pVertexBuffer_[6]->z);
		glVertex3f(pVertexBuffer_[7]->x, pVertexBuffer_[7]->y, pVertexBuffer_[7]->z);
		glVertex3f(pVertexBuffer_[3]->x, pVertexBuffer_[3]->y, pVertexBuffer_[3]->z);
		glVertex3f(pVertexBuffer_[2]->x, pVertexBuffer_[2]->y, pVertexBuffer_[2]->z);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(pVertexBuffer_[0]->x, pVertexBuffer_[0]->y, pVertexBuffer_[0]->z);
		glVertex3f(pVertexBuffer_[3]->x, pVertexBuffer_[3]->y, pVertexBuffer_[3]->z);
		glVertex3f(pVertexBuffer_[7]->x, pVertexBuffer_[7]->y, pVertexBuffer_[7]->z);
		glVertex3f(pVertexBuffer_[4]->x, pVertexBuffer_[4]->y, pVertexBuffer_[4]->z);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(pVertexBuffer_[6]->x, pVertexBuffer_[6]->y, pVertexBuffer_[6]->z);
		glVertex3f(pVertexBuffer_[2]->x, pVertexBuffer_[2]->y, pVertexBuffer_[2]->z);
		glVertex3f(pVertexBuffer_[1]->x, pVertexBuffer_[1]->y, pVertexBuffer_[1]->z);
		glVertex3f(pVertexBuffer_[5]->x, pVertexBuffer_[5]->y, pVertexBuffer_[5]->z);
		glEnd();
	}
}
