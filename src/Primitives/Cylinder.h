#ifndef CYLINDER_H
#define CYLINDER_H

#include "ParametricSurface.h"

/**
* Class for parametric cylinder.
*/
class Cylinder : public ParametricSurface
{
private:
	/* The radius of the cylinder. */
	float _radius;

	/* The height of the cylinder. */
	float _height;

	/* The tesselation fineness of the cylinder. */
	float _resolution;

public:
	/**
	* Initializes a new instance of the Cylinder class.
	*/
	Cylinder();

	/**
	* Initializes a new instance of the Cylinder class.
	*
	* @param radius The radius of the cylinder.
	* @param height The height of the cylinder.
	* @param fineness The tesselation fineness of the cylinder.
	*/
	Cylinder(float radius, float height, float fineness);

	/**
	* Gets the position vector of the parametric cylinder at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Position vector of the surface at the given coordinates.
	*/
	Vector* position(float u, float v) override;

	/**
	* Gets the normal vector (perpendicular to the surface) of the parametric cylinder at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Normal vector of the surface at the given coordinates.
	*/
	Vector* normal(float u, float v) override;
};

#endif