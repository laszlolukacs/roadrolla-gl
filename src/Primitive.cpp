#include "Primitive.h"

Primitive::~Primitive()
{
	if (pVertexBuffer_ != nullptr) {
		delete[] pVertexBuffer_;
		pVertexBuffer_ = nullptr;
	}
}
