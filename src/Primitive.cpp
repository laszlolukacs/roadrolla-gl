#include "Primitive.h"

Primitive::Primitive()
{
	this->_vertices = nullptr;
	this->_verticesLength = 0;
}

Primitive::~Primitive()
{
	if (_vertices != nullptr) {
		delete[] this->_vertices;
		this->_vertices = nullptr;
		this->_verticesLength = 0;
	}
}
