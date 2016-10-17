#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Vector.h"
#include "Material.h"

class Primitive
{
protected:
	int _vertexBufferLength;
	Vector** _pVertexBuffer;
	Material _material;

public:
	virtual void tesselate() = 0;
	virtual void render() = 0;
	virtual ~Primitive();
};

#endif