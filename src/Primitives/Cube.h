#ifndef CUBE_H
#define CUBE_H

#include "../Primitive.h"
#include "../Vector.h"

/**
* Class for cube.
*/
class Cube : public Primitive
{
private:
	float _width, _height, depth_;
	Vector _start;

public:
	/**
	* Initializes a new instance of the Cube class.
	*/
	Cube();

	/**
	* Initializes a new instance of the Cube class.
	*
	* @param startX The starting point of the cube.
	* @param startY The starting point of the cube.
	* @param startZ The starting point of the cube.
	* @param width The width of the cube.
	* @param height The height of the cube.
	* @param depth The depth of the cube.
	*/
	Cube(float startX, float startY, float startZ, float width, float height, float depth);

	/**
	* Performs the tesselation of the cube.
	*/
	virtual void tesselate() override;

	/**
	* Performs the rendering of the parametric surface.
	*/
	virtual void render() override;
};

#endif