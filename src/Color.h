#ifndef COLOR_H
#define COLOR_H

struct Color
{
	float r, g, b, a;

	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

	Color(float r_in, float g_in, float b_in) : r(r_in), g(g_in), b(b_in), a(1.0f) {}

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

#endif