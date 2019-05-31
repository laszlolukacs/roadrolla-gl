#ifndef CIRCLE_H
#define CIRCLE_H

#include "ParametricSurface.h"

/**
* Class for parametric circle.
*/
class Circle : public ParametricSurface
{
private:
	float _paramA, _paramB, _radius, _resolution;

public:
	/**
	* Initializes a new instance of the Circle class.
	*/
	Circle();

	/**
	* Initializes a new instance of the Cylinder class.
	*
	* @param radius The radius of the circle.
	* @param fineness The tesselation fineness of the circle.
	*/
	Circle(float paramA, float paramB, float radius, float fineness);

	/**
	* Gets the position vector of the parametric circle at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Position vector of the surface at the given coordinates.
	*/
	Vector* position(float u, float v) override;

	/**
	* Gets the normal vector (perpendicular to the surface) of the parametric circle at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Normal vector of the surface at the given coordinates.
	*/
	Vector* normal(float u, float v) override;
};

#endif