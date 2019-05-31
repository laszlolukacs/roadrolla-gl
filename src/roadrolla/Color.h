#ifndef COLOR_H
#define COLOR_H

/**
 * Structure for representing an RGBA color.
 */
struct Color
{
	float r, g, b, a;

	/**
	* Initializes a new instance of the Color struct.
	*/
	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

	/**
	* Initializes a new instance of the Color struct.
	*
	* @param r_in Red channel
	* @param g_in Green channel
	* @param b_in Blue channel
	* @param a_in Alpha (opacity) channel
	*/
	Color(float r_in, float g_in, float b_in, float a_in = 1.0f) : r(r_in), g(g_in), b(b_in), a(a_in) {}

	Color& operator=(const Color &rightHandSide)
	{
		if (this == &rightHandSide)
		{
			return *this;
		}

		this->r = rightHandSide.r;
		this->g = rightHandSide.g;
		this->b = rightHandSide.b;
		this->a = rightHandSide.a;
		return *this;
	}
};

#endif // COLOR_H