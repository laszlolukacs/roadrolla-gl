#ifndef PLANE_H
#define PLANE_H

#include "ParametricSurface.h"

/**
* Class for parametric plane.
*/
class Plane : public ParametricSurface
{
private:
	float _height, _resolution;
public:
	/**
	* Initializes a new instance of the Plane class.
	*/
	Plane();

	/**
	* Initializes a new instance of the Plane class.
	*
	* @param width The width of the plane.
	* @param depth The depth of the plane.
	* @param height The elevation of the plane.
	* @param resolution The tesselation fineness of the plane.
	*/
	Plane(float width, float depth, float height, float resolution);

	/**
	* Gets the position vector of the parametric plane at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Position vector of the surface at the given coordinates.
	*/
	Vector* position(float u, float v) override;

	/**
	* Gets the normal vector (perpendicular to the surface) of the parametric plane at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Normal vector of the surface at the given coordinates.
	*/
	Vector* normal(float u, float v) override;
};

#endif