#include "Primitive.h"

Primitive::Primitive()
{
	this->_vertexBuffer = nullptr;
	this->_vertexBufferLength = 0;
}

Primitive::~Primitive()
{
	if (_vertexBuffer != nullptr) {
		delete[] this->_vertexBuffer;
		this->_vertexBuffer = nullptr;
		this->_vertexBufferLength = 0;
	}
}
