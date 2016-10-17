#ifndef CUBE_H
#define CUBE_H

#include "../Primitive.h"
#include "../Vector.h"

class Cube : public Primitive
{
private:
	float _width, _height, depth_;
	Vector _start;
public:
	Cube();
	Cube(float startX, float startY, float startZ, float width, float height, float depth);

	virtual void tesselate() override;
	virtual void render() override;
};

#endif