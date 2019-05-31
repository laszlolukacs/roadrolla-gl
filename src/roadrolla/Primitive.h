#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <GL/freeglut.h>
#include "Vector.h"

/**
 * Base class for tesselating and rendering basic geometric shapes and forms.
 */
class Primitive
{
protected:
	/* Lenght of the vertex data collection. */
	int _verticesLength;

	/* The vertex data of the primitive, stored in the system memory. */
	Vector** _vertices;

public:

	/**
	 * Initializes a new instance of the Primitive class.
	 */
	Primitive();

	/**
	 * Performs the tesselation of the primitive.
	 * Tesselation calculates and stores the vertices of the primitive.
	 * The inheritor class *MUST* implement this method.
	 */
	virtual void tesselate() = 0;

	/**
	 * Performs the rendering of the primitive.
	 * This involves using the vertices to draw the primitive.
	 * The inheritor class *MUST* implement this method.
	 */
	virtual void render() = 0;

	/**
	 * Finalizes an instance of the Primitive class.
	 */
	virtual ~Primitive();
};

#endif