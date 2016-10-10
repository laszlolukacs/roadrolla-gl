#ifndef CAMERA_H
#define CAMERA_H

#include <GL/freeglut.h>
#include "Vector.h"

struct Camera
{
	Vector eyePos;
	Vector lookAt;
	Vector upDir;

	float fov;
	float nearClippingPane;
	float rearClippingPane;
	int viewportLeft, viewportBottom, viewportWidth, viewportHeight;

	Camera() {}

	void setupProjection_gl() const
	{
		glViewport(viewportLeft, viewportBottom, viewportWidth, viewportHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov, float(viewportWidth) / float(viewportHeight), nearClippingPane, rearClippingPane);
	}

	void setupModelView_gl() const
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eyePos.x, eyePos.y, eyePos.z, lookAt.x, lookAt.y, lookAt.z, upDir.x, upDir.y, upDir.z);
	}
};

#endif