#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/freeglut.h>
#include "Color.h"

struct Material
{
	bool isSpecular;
	float shininess;
	Color kAmbient, kDiffuse, kSpecular;

	Material() {}

	void setup_gl() const
	{
		float ambient[] = { kAmbient.r, kAmbient.g, kAmbient.b, 1.0f };
		float diffuse[] = { kDiffuse.r, kDiffuse.g, kDiffuse.b, 1.0f };
		float specular[] = { kSpecular.r, kSpecular.g, kSpecular.b, 1.0f };

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		if (isSpecular)
		{
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		}

		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}
};

#endif
