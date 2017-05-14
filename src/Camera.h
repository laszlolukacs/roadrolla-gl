#ifndef CAMERA_H
#define CAMERA_H

#include <GL/freeglut.h>
#include "Vector.h"

/* Structure for 3 dimensional OpenGL camera and its respective operations. */
struct Camera
{
	/* Specifies the position of the observer. */
	Vector eyePos;

	/* Specifies the `front` direction of the observer. */
	Vector frontDir;

	/* Specifies the `up` direction of the observer. */
	Vector upDir;

	/* The field of view, angle of view frustum, in degrees. */
	float fov;

	/* The distance of the frontal clipping pane from the observer, nearest view frustum plane. */
	float nearClippingPane;

	/* The distance of the rear clipping pane from the observer, farthest view frustum plane. */
	float rearClippingPane;

	/* The respective dimension of the viewport. */
	int viewportLeft, viewportBottom, viewportWidth, viewportHeight;

	/**
	 * Initializes a new instance of the Camera struct.
	 */
	Camera()
	{
		this->eyePos = Vector(0.0f, 0.0f, 3.0f);
		this->frontDir = Vector(0.0f, 0.0f, -1.0f);
		this->upDir = Vector(0.0f, 1.0f, 0.0f);
		this->fov = 90.0f;
		this->nearClippingPane = 1.0f;
		this->rearClippingPane = 45.0f;
		this->viewportLeft = this->viewportBottom = 0;
		this->viewportWidth = this->viewportHeight = 600;
	}

	/**
	* Sets the GL_PROJECTION matrix of a 3D camera with the stored parameters.
	*/
	void setProjectionMatrix() const
	{
		glViewport(this->viewportLeft, this->viewportBottom, this->viewportWidth, this->viewportHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(this->fov, float(this->viewportWidth) / float(this->viewportHeight), this->nearClippingPane, this->rearClippingPane);
	}

	/**
	 * Sets the GL_MODELVIEW matrix of a 3D camera with the specified positions.
	 */
	void setModelViewMatrix() const
	{
		Vector lookAt = this->eyePos + this->frontDir;

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			this->eyePos.x, this->eyePos.y, this->eyePos.z,
			lookAt.x, lookAt.y, lookAt.z,
			this->upDir.x, this->upDir.y, this->upDir.z);
	}

	/**
	 * Sets the viewport coordinates for the camera.
	 *
	 * @param viewportLeft The leftmost coordinate of the viewport.
	 * @param viewportBottom The bottommost coordinate of the viewport.
	 * @param viewportWidth The width of the viewport in pixels.
	 * @param viewportHeight The height of the viewport in pixels.
	 */
	void setViewport(int viewportLeft, int viewportBottom, int viewportWidth, int viewportHeight)
	{
		this->viewportLeft = viewportLeft;
		this->viewportBottom = viewportBottom;
		this->viewportWidth = viewportWidth;
		this->viewportHeight = viewportHeight;
		this->setProjectionMatrix();
	}

	/**
	 * Moves the camera to the specified direction.
	 *
	 * @param direction The direction to which the camera should be moved.
	 */
	void move(const Vector direction)
	{
		this->eyePos += direction;
		this->setProjectionMatrix();
	}

	/**
	 * Rotates the camera with the specified angles.
	 *
	 * @param yaw The yaw angle of the camera in degrees.
	 * @param pitch The pitch angle of the camera in degrees.
	 */
	void rotate(float yaw, float pitch)
	{
		// TODO: use/implement math.clamp instead of plain branching to clamp pitch values
		if (pitch > this->fov - 15.1f)
		{
			pitch = this->fov - 15.1f;
		}

		if (pitch < -1.0f * this->fov + 15.1f)
		{
			pitch = -1.0f * this->fov + 15.1f;
		}

		Vector frontDir;
		float yawRadians = yaw * 3.1415926535f / 180.0f;
		float pitchRadians = pitch * 3.1415926535f / 180.0f;

		frontDir.x = cosf(yawRadians) * cosf(pitchRadians);
		frontDir.y = sinf(pitchRadians);
		frontDir.z = sinf(yawRadians) * cosf(pitchRadians);

		this->frontDir = frontDir.normalize();
		this->setProjectionMatrix();
	}
};

#endif