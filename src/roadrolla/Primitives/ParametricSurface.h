#ifndef PARAMETRIC_SURFACE_H
#define PARAMETRIC_SURFACE_H

#include "../Primitive.h"
#include "../Vector.h"

/**
* Base class for parametric surfaces.
* A parametric surface is a surface in the Euclidean (3D) space which is defined by a parametric equation.
* The parametric equation itself must be implemented by the inheritor classes.
*
* @see position(float u, float v)
*/
class ParametricSurface : Primitive
{
protected:
	/* Lenght of the normal vectors collection */
	int _normalsLength;

	/* The normal vectors of the parametric surface, stored in the system memory */
	Vector** _normals;

	/* The details of the 'u' axis of the parametric surface. */
	float _uMin, _uMax, _uStep;

	/* Indicates whether the parametric surface loops around the 'u' axis. */
	bool _uLoop = false;

	/* The details of the 'v' axis of the parametric surface. */
	float _vMin, _vMax, _vStep;

	/* Indicates whether the parametric surface loops around the 'v' axis. */
	bool _vLoop = false;

	/* The number of individual 'u' and 'v' values used by this instance of ParametricSurface */
	int _uLength, _vLength;

	/**
	* Gets the total amount of vertices needed by this instance of ParametricSurface, based on the boundaries of the 'u' and 'v' values.
	*
	* @param uMin The lower value of the 'u'
	* @param uMax The upper value of the 'u'
	* @param uStep The incrementing value of 'u'
	* @param vMin The lower value of the 'v'
	* @param vMax The upper value of the 'v'
	* @param vStep The incrementing value of 'v'
	*
	* @returns The total amount of vertices required by this instance of the ParametricSurface class.
	*/
	int getNumberOfVertices(float uMin, float uMax, float uStep, float vMin, float vMax, float vStep);

	/**
	 * Performs the specifying the textures, normals and vertices of the parametric surface within the gfxApiBeginDraw / gfxApiEndDraw function pairs.
	 *
	 * @param u The 'u' coordinate of the parametric surface, used for texturing.
	 * @param v The 'v' coordinate of the parametric surface, used for texturing.
	 * @param i The 'i' lookup index of the vertice and normals map to be used.
	 * @param j The 'j' lookup index of the vertice and normals map to be used.
	 */
	void renderVertexPositionNormalTexture(float u, float v, int i, int j) const;

public:
	/**
	* Initializes a new instance of the ParametricSurface class.
	*/
	ParametricSurface();

	/**
	* Initializes a new instance of the ParametricSurface class.
	*
	* @param uMin The lower value of the 'u'
	* @param uMax The upper value of the 'u'
	* @param uStep The incrementing value of 'u'
	* @param uLoop Indicates whether the surface loops around the 'u' axis
	* @param vMin The lower value of the 'v'
	* @param vMax The upper value of the 'v'
	* @param vStep The incrementing value of 'v'
	* @param vLoop Indicates whether the surface loops around the 'v' axis
	*/
	ParametricSurface(float uMin, float uMax, float uStep, bool uLoop, float vMin, float vMax, float vStep, bool vLoop);

	/**
	* Gets the position vector of the parametric surface at the given 'u' and 'v' coordinates.
	* The inheritor class *MUST* implement this method.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Position vector of the surface at the given coordinates.
	*/
	virtual Vector* position(float u, float v) = 0;

	/**
	* Gets the normal vector (perpendicular to the surface) of the parametric surface at the given 'u' and 'v' coordinates.
	* The inheritor class *MUST* implement this method.
	*
	* @param u The 'u' coordinate
	* @param v The 'v' coordinate
	*
	* @returns Normal vector of the surface at the given coordinates.
	*/
	virtual Vector* normal(float u, float v) = 0;

	/**
	* Performs the tesselation of the parametric surface.
	* Tesselation calculates and stores the vertices of the primitive using methods provided by the `position(u, v)` and `normal(u, v)` methods.
	*
	* @see position(float u, float v)
	* @see normal(float u, float v)
	*/
	virtual void tesselate() override;

	/**
	* Performs the rendering of the parametric surface.
	*/
	virtual void render() override;

	/**
	* Finalizes an instance of the ParametricSurface class.
	*/
	virtual ~ParametricSurface();
};

#endif