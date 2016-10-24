#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <GL/freeglut.h>
#include "Vector.h"

class Primitive
{
protected:
	int _vertexBufferLength;
	Vector** _vertexBuffer;

public:
	Primitive();
	virtual void tesselate() = 0;
	virtual void render() = 0;
	virtual ~Primitive();
};

#endif