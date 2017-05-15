#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "ParametricSurface.h"

/**
* Class for parametric ellipsoid.
*/
class Ellipsoid : public ParametricSurface
{
private:
	float _paramA, _paramB, _paramC;

public:
	/**
	* Initializes a new instance of the Ellipsoid class.
	*/
	Ellipsoid();

	/**
	* Initializes a new instance of the Ellipsoid class.
	*
	* @param paramA The modifier parameter for the width.
	* @param paramB The modifier parameter for the depth.
	* @param paramC The modifier parameter for the height.
	*/
	Ellipsoid(float paramA, float paramB, float paramC);

	/**
	* Initializes a new instance of the Ellipsoid class.
	*
	* @param paramA The modifier parameter for the width.
	* @param paramB The modifier parameter for the depth.
	* @param paramC The modifier parameter for the height.
	* @param uMin The lower value of the 'u'.
	* @param uMax The upper value of the 'u'.
	* @param uStep The incrementing value of 'u'.
	* @param vMin The lower value of the 'v'.
	* @param vMax The upper value of the 'v'.
	* @param vStep The incrementing value of 'v'.
	*/
	Ellipsoid(float paramA, float paramB, float paramC, float uMin, float uMax, float uStep, float vMin, float vMax, float vStep);

	/**
	* Gets the position vector of the parametric ellipsoid at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Position vector of the surface at the given coordinates.
	*/
	Vector* position(float u, float v) override;

	/**
	* Gets the normal vector (perpendicular to the surface) of the parametric ellipsoid at the given 'u' and 'v' coordinates.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Normal vector of the surface at the given coordinates.
	*/
	Vector* normal(float u, float v) override;
};

#endif
