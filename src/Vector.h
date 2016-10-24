#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

struct Vector
{
	float x, y, z;

	Vector() : x(0.0f), y(0.0f), z(0.0f)
	{
	}

	Vector(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in)
	{
	}

	Vector& operator=(const Vector &rightHandSide)
	{
		if (this == &rightHandSide)
		{
			return *this;
		}

		this->x = rightHandSide.x;
		this->y = rightHandSide.y;
		this->z = rightHandSide.z;
		return *this;
	}

	Vector& operator+=(const Vector &rightHandSide)
	{
		this->x += rightHandSide.x;
		this->y += rightHandSide.y;
		this->z += rightHandSide.z;
		return *this;
	}

	Vector& operator-=(const Vector &righthandside)
	{
		this->x -= righthandside.x;
		this->y -= righthandside.y;
		this->z -= righthandside.z;
		return *this;
	}

	Vector operator+(const Vector &rightHandSide) const
	{
		Vector result = *this;
		result.x += rightHandSide.x;
		result.y += rightHandSide.y;
		result.z += rightHandSide.z;
		return result;
	}

	Vector operator-(const Vector &rightHandSide) const
	{
		Vector result = *this;
		result.x -= rightHandSide.x;
		result.y -= rightHandSide.y;
		result.z -= rightHandSide.z;
		return result;
	}

	Vector& operator-()
	{
		this->x = -(this->x);
		this->y = -(this->y);
		this->z = -(this->z);
		return *this;
	}

	Vector operator*(const float rightHandSide) const
	{
		Vector result = *this;
		result.x *= rightHandSide;
		result.y *= rightHandSide;
		result.z *= rightHandSide;
		return result;
	}

	float operator*(const Vector &rightHandSide) const
	{
		return (this->x * rightHandSide.x
			+ this->y * rightHandSide.y
			+ this->z * rightHandSide.z);
	}

	Vector operator%(const Vector &rightHandSide) const
	{
		Vector result = *this;
		result.x = this->y * rightHandSide.z - this->z * rightHandSide.y;
		result.y = this->z * rightHandSide.x - this->x * rightHandSide.z;
		result.z = this->x * rightHandSide.y - this->y * rightHandSide.x;
		return result;
	}

	Vector operator/(const float rightHandSide) const
	{
		Vector result = *this;
		result.x = result.x / rightHandSide;
		result.y = result.y / rightHandSide;
		result.z = result.z / rightHandSide;
		return result;
	}

	float length() const
	{
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}
};

#endif