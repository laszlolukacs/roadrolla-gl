#ifndef CONE_H
#define CONE_H

#include "ParametricSurface.h"

/**
* Class for parametric cone.
*/
class Cone : public ParametricSurface
{
private:
	float _paramA, _paramB, _radius, _height, _resolution;

public:
	/**
	* Initializes a new instance of the Cone class.
	*/
	Cone();

	/**
	* Initializes a new instance of the Cone class.
	*
	* @param radius The radius of the cylinder.
	* @param height The height of the cylinder.
	* @param resolution The tesselation fineness of the cone.
	*/
	Cone(float paramA, float paramB, float radius, float height, float resolution);

	/**
	* Gets the position vector of the parametric cone at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Position vector of the surface at the given coordinates.
	*/
	Vector* position(float u, float v) override;

	/**
	* Gets the normal vector (perpendicular to the surface) of the parametric cone at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Normal vector of the surface at the given coordinates.
	*/
	Vector* normal(float u, float v) override;
};

#endif
