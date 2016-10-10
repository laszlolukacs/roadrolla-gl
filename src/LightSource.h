#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <GL/freeglut.h>
#include "Vector.h"
#include "Color.h"

struct LightSource
{
	int id;
	Color ambientIntensity, diffuseIntensity, specularIntensity;
	Vector position;

	void setup_gl() const
	{
		float ambient[] = { ambientIntensity.r, ambientIntensity.g, ambientIntensity.b, 1.0f };
		float diffuse[] = { diffuseIntensity.r, diffuseIntensity.g, diffuseIntensity.b, 1.0f };
		float specular[] = { specularIntensity.r, specularIntensity.g, specularIntensity.b, 1.0f };
		float direction[] = { position.x, position.y, position.z, 0.0f };

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_POSITION, direction);
		glEnable(GL_LIGHT0);
	}
};

#endif