#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Vector.h"
#include "Material.h"

class Primitive
{
protected:
	int _vertexBufferLength;
	Vector** _vertexBuffer;
	Material _material;

public:
	Primitive();
	virtual void tesselate() = 0;
	virtual void render() = 0;
	virtual ~Primitive();
};

#endif