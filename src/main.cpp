// See LICENSE for details.

#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN 1
#  endif
#include <windows.h>
#endif // to make it work on Microsoft Windows, too

#include <iostream>
#include "Color.h"
#include "Vector.h"
#include "Camera.h"
#include "LightSource.h"
#include "Material.h"
#include "Texture.h"
#include "Textures/GrassTexture.h"
#include "Textures/RoadTexture.h"
#include "Textures/WheelTexture.h"
#include "Primitive.h"
#include "Primitives/Cube.h"
#include "Primitives/Circle.h"
#include "Primitives/Ellipsoid.h"
#include "Primitives/Cylinder.h"
#include "Primitives/Cone.h"
#include "Primitives/Plane.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

float g_Time = 0.0f;
float g_TimeElapsed = 0.0f;
float g_DeltaT = 0.1f;

class ObjectBase
{
protected:
	bool _isShadowMode;
	float _boundingRadius;
	Vector _acceleration;
	Vector _velocity;
	Vector _position;
	Material _material;

public:
	ObjectBase() {}
	virtual void Build() = 0;
	virtual Vector GetPosition() { return _position; }
	virtual float GetBoundingRadius() { return _boundingRadius; }
	virtual void SetShadowMode(bool isShadowMode) { _isShadowMode = isShadowMode; }
	virtual void SetAcceleration(Vector acceleration) { _acceleration = acceleration; }
	virtual void SetVelocity(Vector velocity) { _velocity = velocity; }
	virtual void SetPosition(Vector position) { _position = position; }
	virtual void Update(float deltaT) = 0;
	virtual void SetTransformations_gl() = 0;
	virtual void TesselateAndRender_gl() = 0;

};

class RoadRoller : public ObjectBase
{
private:
	float _rotateVelocity;
	float _rotateFi;
	Circle* _wheelSide;
	Cylinder *_wheel, *_exhaust;
	Cube* _chassis[4];
	WheelTexture _texture;
	Material _chassisMaterial, _wheelMaterial;

public:
	RoadRoller()
	{
	}

	~RoadRoller()
	{
		if (_wheelSide != nullptr)
		{
			delete _wheelSide;
		}

		if (_wheel != nullptr)
		{
			delete _wheel;
		}
	}

	void build()
	{
		Vector nullVec = Vector(0.0f, 0.0f, 0.0f);

		Circle* wheelSide = new Circle(0.0f, 0.0f, 0.3f, 1.0f);
		Cylinder* wheel = new Cylinder(0.0f, 0.0f, 1.0f, 2.0f, 1.0f);
		Cylinder* exhaust = new Cylinder(0.0f, 0.0f, 0.16f, 2.0f, 1.0f);

		_acceleration = _velocity = _position = nullVec;
		_rotateVelocity = 0.0f;
		_rotateFi = 0.0f;
		_boundingRadius = 1.5f;

		Cube* chassisBottom = new Cube(1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f);
		Cube* chassisMiddle = new Cube(3.0f, 1.5f, 1.0f, 6.0f, 0.5f, 2.0f);
		Cube* chassisCockpit = new Cube(1.0f, 1.5f, 0.7f, 2.0f, -1.5f, 1.4f);
		Cube* chassisTop = new Cube(1.13f, 3.0f, 1.13f, 2.26f, -0.13f, 2.26f);

		chassisBottom->tesselate();
		chassisMiddle->tesselate();
		chassisCockpit->tesselate();
		chassisTop->tesselate();

		wheelSide->tesselate();
		wheel->tesselate();
		exhaust->tesselate();

		_wheelSide = wheelSide;
		_wheel = wheel;
		_exhaust = exhaust;

		_chassis[0] = chassisBottom;
		_chassis[1] = chassisMiddle;
		_chassis[2] = chassisCockpit;
		_chassis[3] = chassisTop;

		_chassisMaterial.kAmbient = Color(1.0f, 0.843f, 0.0f);
		_chassisMaterial.kDiffuse = Color(1.0f, 0.843f, 0.0f);
		_chassisMaterial.isSpecular = true;
		_chassisMaterial.kSpecular = Color(1.0f, 1.0f, 1.0f);
		_chassisMaterial.shininess = 40.0f;

		_wheelMaterial.kAmbient = Color(0.412f, 0.412f, 0.412f);
		_wheelMaterial.kDiffuse = Color(0.412f, 0.412f, 0.412f);
		_wheelMaterial.isSpecular = false;
		_wheelMaterial.kSpecular = Color(0.0f, 0.0f, 0.0f);
		_wheelMaterial.shininess = 0.0f;

		_texture.generate();
	}

	void update(float deltaT)
	{
		_velocity += _acceleration * deltaT;
		_position += _velocity * deltaT;

		_rotateVelocity += 0.3f * _acceleration.x * deltaT;
		_rotateFi -= _rotateVelocity * deltaT * 0.3183f * 180.0f;
	}

	void setTransformations()
	{
		glTranslatef(_position.x, 1.0f + _position.y, _position.z);
	}

	void render()
	{
		if (!_isShadowMode)
			_wheelMaterial.setup_gl();
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(2.0f, 0.0f, 1.0f);
		glRotatef(_rotateFi, 0.0f, 0.0f, 1.0f);
		_wheelSide->render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2.0f, 0.0f, -1.0f);
		glRotatef(_rotateFi, 0.0f, 0.0f, 1.0f);
		_wheelSide->render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2.0f, 0.0f, 1.0f);
		glRotatef(_rotateFi, 0.0f, 0.0f, 1.0f);
		_wheelSide->render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2.0f, 0.0f, -1.0f);
		glRotatef(_rotateFi, 0.0f, 0.0f, 1.0f);
		_wheelSide->render();
		glPopMatrix();

		if (!_isShadowMode)
			_texture.setup_gl();
		glPushMatrix();
		glTranslatef(2.0f, 0.0f, -1.0f);
		glRotatef(_rotateFi, 0.0f, 0.0f, 1.0f);
		_wheel->render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2.0f, 0.0f, -1.0f);
		glRotatef(_rotateFi, 0.0f, 0.0f, 1.0f);
		_wheel->render();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		if (!_isShadowMode)
			_chassisMaterial.setup_gl();
		_chassis[0]->render();
		_chassis[1]->render();

		_chassisMaterial.kAmbient = Color(0.138f, 0.42f, 0.557f);
		_chassisMaterial.kDiffuse = Color(0.138f, 0.42f, 0.557f);
		_chassisMaterial.shininess = 200.0f;
		if (!_isShadowMode)
			_chassisMaterial.setup_gl();
		_chassis[2]->render();

		_chassisMaterial.kAmbient = Color(1.0f, 0.843f, 0.0f);
		_chassisMaterial.kDiffuse = Color(1.0f, 0.843f, 0.0f);
		_chassisMaterial.shininess = 40.0f;
		if (!_isShadowMode)
			_chassisMaterial.setup_gl();
		_chassis[3]->render();

		if (!_isShadowMode)
			_wheelMaterial.setup_gl();
		glPushMatrix();
		glTranslatef(1.8f, 3.0f, -0.7f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		_exhaust->render();
		glPopMatrix();
	}
};

class Chicken : public ObjectBase
{
private:
	bool _isAlive;
	bool _isMoving;

	Ellipsoid *_body, *_head, *_eye, *_knee;
	Cylinder *_neck, *_upperLeg;
	Cone *_beak, *_mohawk;

	Material _eyeMaterial;
	Material _bodyMaterial;
	Material _limbMaterial;

public:
	Chicken() {}

	void build()
	{
		Vector nullVec = Vector();

		Ellipsoid* body = new Ellipsoid(0.5f, 0.3f, 0.2f);
		Ellipsoid* head = new Ellipsoid(0.2f, 0.1f, 0.1f);
		Ellipsoid* eye = new Ellipsoid(0.02f, 0.02f, 0.02f);
		Ellipsoid* knee = new Ellipsoid(0.04f, 0.04f, 0.04f);
		Cylinder* neck = new Cylinder(0.0f, 0.0f, 0.08f, 0.6f, 1.0f);
		Cylinder* upperLeg = new Cylinder(0.0f, 0.0f, 0.03f, 0.5f, 1.0f);
		Cone* beak = new Cone(0.0f, 0.0f, 0.04f, 0.2f, 1.0f);
		Cone* mohawk = new Cone(0.0f, 0.0f, 0.03f, 0.23f, 1.0f);

		_isAlive = true;
		_acceleration = _velocity = _position = nullVec;
		_boundingRadius = 0.4f;

		body->tesselate();
		head->tesselate();
		eye->tesselate();
		knee->tesselate();

		neck->tesselate();
		upperLeg->tesselate();

		beak->tesselate();
		mohawk->tesselate();

		_body = body;
		_head = head;
		_eye = eye;
		_knee = knee;
		_neck = neck;
		_upperLeg = upperLeg;
		_beak = beak;
		_mohawk = mohawk;

		_eyeMaterial.kAmbient = Color(1.0f, 0.925f, 0.545f);
		_eyeMaterial.kDiffuse = Color(1.0f, 0.925f, 0.545f);
		_eyeMaterial.isSpecular = true;
		_eyeMaterial.kSpecular = Color(1.0f, 1.0f, 1.0f);
		_eyeMaterial.shininess = 20.0f;

		_bodyMaterial.kAmbient = Color(0.637f, 0.32f, 0.176f);
		_bodyMaterial.kDiffuse = Color(0.637f, 0.32f, 0.176f);
		_bodyMaterial.isSpecular = false;
		_bodyMaterial.kSpecular = Color(0.0f, 0.0f, 0.0f);
		_bodyMaterial.shininess = 0.0f;

		_limbMaterial.kAmbient = Color(1.0f, 0.612f, 0.0f);
		_limbMaterial.kDiffuse = Color(1.0f, 0.612f, 0.0f);
		_limbMaterial.isSpecular = false;
		_limbMaterial.kSpecular = Color(0.0f, 0.0f, 0.0f);
		_limbMaterial.shininess = 0.0f;
	}

	bool IsAlive()
	{
		return _isAlive;
	}

	bool IsMoving()
	{
		return _isMoving;
	}

	void setPosition(Vector position)
	{
		_position = position;
	}

	void setTransformations()
	{
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	}

	void SetIsMoving(bool isMoving) { _isMoving = isMoving; }

	void SetStillAlive(bool isStillAlive) { _isAlive = isStillAlive; }

	void update(float deltaT)
	{
		if (_isAlive)
			_position += _velocity * deltaT;
		if (_position.z < -6.0f)
			_velocity.z = 0.0f;
	}

	void render()
	{
		if (!_isShadowMode)
			_bodyMaterial.setup_gl();
		glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
		glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
		_body->render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.3f, 1.6f, 0.0f);
		glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		_neck->render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.4f, 1.6f, 0.0f);
		_head->render();
		glPushMatrix();
		if (!_isShadowMode)
			_eyeMaterial.setup_gl();
		glTranslatef(0.1f, 0.0f, 0.1f);
		_eye->render();
		glTranslatef(0.0f, 0.0f, -0.2f);
		_eye->render();
		glPopMatrix();
		glPushMatrix();
		if (!_isShadowMode)
			_limbMaterial.setup_gl();
		glTranslatef(0.25f, -0.028f, 0.0f);
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		_beak->render();
		glPopMatrix();
		glPushMatrix();
		if (!_isShadowMode)
			_limbMaterial.setup_gl();
		glTranslatef(0.12f, 0.185f, 0.0f);
		glPushMatrix();
		glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
		_mohawk->render();
		glPopMatrix();
		glTranslatef(-0.06f, 0.0, 0.0f);
		_mohawk->render();
		glTranslatef(-0.06f, 0.0, 0.0f);
		_mohawk->render();
		glTranslatef(-0.06f, 0.0, 0.0f);
		_mohawk->render();
		glTranslatef(-0.06f, 0.0, 0.0f);
		glPushMatrix();
		glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
		_mohawk->render();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		if (!_isShadowMode)
			_limbMaterial.setup_gl();
		glPushMatrix();
		glTranslatef(-0.08f, 0.4f, -0.2f);
		glRotatef(-80.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
		_upperLeg->render();
		glPushMatrix();
		_knee->render();
		glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
		_upperLeg->render();
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.5f);
		glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
		_knee->render();
		_upperLeg->render();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.08f, 0.4f, 0.2f);
		glRotatef(-110.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
		_upperLeg->render();
		glPushMatrix();
		_knee->render();
		glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
		_upperLeg->render();
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.5f);
		glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
		_knee->render();
		_upperLeg->render();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	}
};

class Scene
{
private:
	float _shadowMatrix[4][4];
	float _carcassMatrix[4][4];
	float _shadowMatrixVariableMember_1;
	float _shadowMatrixVariableMember_2;

	Vector _lightDir;
	LightSource _sun;
	LightSource _carcass;

	GrassTexture _grassyTexture;
	RoadTexture _roadTexture;
	Material _grassMaterial;
	Material _roadMaterial;

	Plane* _grassy;
	Plane* _road;

public:
	Camera _cam;
	Camera _inCar;
	Camera _chickenView;

	Chicken _chicken[3];
	RoadRoller _roadRoller;

	Scene() {	}

	void Build()
	{
		Vector tempPosition(0.0f, 0.0f, 0.0f);

		_lightDir = Vector(0.0f, 20.0f, 0.0f);
		_shadowMatrixVariableMember_1 = -(_lightDir.x / _lightDir.y);
		_shadowMatrixVariableMember_2 = -(_lightDir.z / _lightDir.y);

		float carcassMatrixTemp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ _shadowMatrixVariableMember_1,  0.0f, _shadowMatrixVariableMember_2,  0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.001f, 0.0f, 1.0f }
		};

		_carcass.ambientIntensity = Color(0.0f, 0.0f, 0.0f);
		_carcass.diffuseIntensity = Color(0.0f, 0.0f, 0.0f);
		_carcass.specularIntensity = Color(0.0f, 0.0f, 0.0f);
		_carcass.position = _lightDir;

		_lightDir = Vector(0.0f, 0.0f, 0.0f);
		_shadowMatrixVariableMember_1 = -(_lightDir.x / _lightDir.y);
		_shadowMatrixVariableMember_2 = -(_lightDir.z / _lightDir.y);

		float shadowMatrixTemp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ _shadowMatrixVariableMember_1,  0.0f, _shadowMatrixVariableMember_2,  0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.001f, 0.0f, 1.0f }
		};

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				_shadowMatrix[i][j] = shadowMatrixTemp[i][j];
				_carcassMatrix[i][j] = carcassMatrixTemp[i][j];
			}

		_sun.ambientIntensity = Color(0.1f, 0.1f, 0.1f);
		_sun.diffuseIntensity = Color(1.0f, 0.51f, 0.278f);
		_sun.specularIntensity = Color(0.8f, 0.8f, 0.8f);
		_sun.position = _lightDir;

		_cam.eyePos = Vector(0.0f, 2.0f, -2.0f);
		_cam.lookAt = Vector(0.0f, 0.0f, 0.0f);
		_cam.upDir = Vector(0.0f, 1.0f, 0.0f);
		_cam.fov = 60.0f;
		_cam.viewportBottom = 0;
		_cam.viewportLeft = 0;
		_cam.viewportWidth = _cam.viewportHeight = 300;
		_cam.nearClippingPane = 1.0f;
		_cam.rearClippingPane = 56.0f;

		_cam.setupProjection_gl();
		_cam.setupModelView_gl();
		_sun.setup_gl();

		Plane* grass = new Plane(100.0f, 100.0f, -0.002f, 1.0f);
		Plane* road = new Plane(100.0f, 2.0f, -0.001f, 4.0f);
		grass->tesselate();
		road->tesselate();
		_grassy = grass;
		_road = road;

		_grassMaterial.kAmbient = Color(1.0f, 1.0f, 1.0f);
		_grassMaterial.kDiffuse = Color(2.0f, 2.0f, 2.0f);
		_grassMaterial.isSpecular = false;
		_grassMaterial.kSpecular = Color(0.0f, 0.0f, 0.0f);
		_grassMaterial.shininess = 0.0f;

		_roadMaterial.kAmbient = Color(1.0f, 1.0f, 1.0f);
		_roadMaterial.kDiffuse = Color(2.0f, 2.0f, 2.0f);
		_roadMaterial.isSpecular = false;
		_roadMaterial.kSpecular = Color(0.0f, 0.0f, 0.0f);
		_roadMaterial.shininess = 0.0f;

		_grassyTexture.generate();
		_roadTexture.generate();

		for (int i = 0; i < 3; i++)
		{
			_chicken[i].build();
			tempPosition.x = 2.0f + 2.0f * (float)i;
			tempPosition.z = 3.0f;
			_chicken[i].setPosition(tempPosition);
		}
		_chickenView.eyePos = tempPosition;
		_chickenView.eyePos.y = tempPosition.y + 0.8f;
		_chickenView.lookAt = tempPosition;
		_chickenView.lookAt.x = tempPosition.x + 4.0f;
		_chickenView.upDir = Vector(0.0f, 1.0f, 0.0f);
		_chickenView.fov = 100.0f;
		_chickenView.viewportBottom = 0;
		_chickenView.viewportLeft = 300;
		_chickenView.viewportWidth = 300;
		_chickenView.viewportHeight = 300;
		_chickenView.nearClippingPane = 0.3f;
		_chickenView.rearClippingPane = 20.0f;

		_roadRoller.build();
		tempPosition.x = -4.0f;
		tempPosition.z = 0.0f;
		_roadRoller.SetPosition(tempPosition);

		_inCar.eyePos = tempPosition;
		_inCar.eyePos.x = tempPosition.x + 1.0f;
		_inCar.eyePos.y = tempPosition.y + 4.0f;
		_inCar.lookAt = tempPosition;
		_inCar.lookAt.x = tempPosition.x + 6.0f;
		_inCar.upDir = Vector(0.0f, 1.0f, 0.0f);
		_inCar.fov = 80.0f;
		_inCar.viewportBottom = 300;
		_inCar.viewportLeft = 0;
		_inCar.viewportWidth = 600;
		_inCar.viewportHeight = 300;
		_inCar.nearClippingPane = 2.0f;
		_inCar.rearClippingPane = 40.0f;
	}

	void AccelerateRoller()
	{
		_roadRoller.SetAcceleration(Vector(0.000001f, 0.0f, 0.0f));
	}

	void StillRoller()
	{
		_roadRoller.SetAcceleration(Vector(0.0f, 0.0f, 0.0f));
	}

	void DeccelerateRoller()
	{
		_roadRoller.SetAcceleration(Vector(-0.000001f, 0.0f, 0.0f));
	}

	void StartChicken()
	{
		for (int i = 0; i < 3; i++)
		{
			if (_chicken[i].IsAlive() && !_chicken[i].IsMoving())
			{
				_chicken[i].SetIsMoving(true);
				_chicken[i].SetVelocity(Vector(0.0f, 0.0f, -0.001f));
				return;
			}
		}
	}

	void Update(float deltaT, float periodTime)
	{
		Vector distance(0.0f, 0.0f, 0.0f);
		float minimumDistance = 0.0f;
		float time = periodTime / 3183.09886184f;
		float timeCircle = periodTime / 1591.54943092f;

		if (periodTime < 5000.0f)
		{
			_sun.diffuseIntensity.g += 0.00008167f;
			_sun.diffuseIntensity.b += 0.0001203f;
		}
		else
		{
			_sun.diffuseIntensity.g -= 0.00008167f;
			_sun.diffuseIntensity.b -= 0.0001203f;
		}
		_lightDir.z = 20.0f * cosf(time);
		_lightDir.y = 20.0f * sinf(time);
		_shadowMatrixVariableMember_1 = -(_lightDir.x / _lightDir.y);
		_shadowMatrixVariableMember_2 = -(_lightDir.z / _lightDir.y);
		_sun.position = _lightDir;
		_sun.setup_gl();
		_shadowMatrix[1][0] = _shadowMatrixVariableMember_1;
		_shadowMatrix[1][2] = _shadowMatrixVariableMember_2;

		_cam.eyePos.x = 5.0f * cosf(time * 0.5f);
		_cam.eyePos.z = 5.0f * sinf(time * 0.5f);

		_roadRoller.update(deltaT);
		_inCar.eyePos.x = _roadRoller.GetPosition().x;
		_inCar.lookAt.x = 6.0f + _roadRoller.GetPosition().x;
		for (int i = 0; i < 3; i++)
		{
			_chicken[i].update(deltaT);
			if (_chicken[i].IsAlive())
			{
				_chickenView.eyePos = _chicken[i].GetPosition();
				_chickenView.eyePos.y = _chicken[i].GetPosition().y + 0.8f;
				_chickenView.eyePos.z = _chicken[i].GetPosition().z;
				_chickenView.lookAt = _chicken[i].GetPosition();
				_chickenView.lookAt.z = -4.0f + _chicken[i].GetPosition().z;
				distance = _chicken[i].GetPosition() - _roadRoller.GetPosition();
				minimumDistance = _chicken[i].GetBoundingRadius() + _roadRoller.GetBoundingRadius();
				if (distance.length() < minimumDistance)
				{
					_chicken[i].SetStillAlive(false);
				}
			}
		}
	}

	void Render()
	{
		_sun.setup_gl();

		glColor3f(1.0f, 1.0f, 1.0f);

		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		_grassMaterial.setup_gl();
		_grassyTexture.setup_gl();

		glPushMatrix();
		glTranslatef(0.0f, -0.002f, 0.0f);
		_grassy->render();
		glPopMatrix();

		_roadMaterial.setup_gl();
		_roadTexture.setup_gl();
		glPushMatrix();
		glTranslatef(0.0f, -0.001f, 0.00f);
		_road->render();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glColor3f(0.0f, 0.0f, 0.0f);
		if (_chicken[0].IsAlive() || _chicken[1].IsAlive() || _chicken[2].IsAlive())
		{
			for (int i = 0; i < 3; i++)
			{
				if (_chicken[i].IsAlive())
				{
					glPushMatrix();
					_chicken[i].SetShadowMode(false);
					_chicken[i].setTransformations();
					_chicken[i].render();
					glPopMatrix();
				}
			}
		}

		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		_roadRoller.SetShadowMode(false);
		_roadRoller.setTransformations();
		_roadRoller.render();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPopMatrix();

		if (!_chicken[0].IsAlive() || !_chicken[1].IsAlive() || !_chicken[2].IsAlive())
		{
			glPushMatrix();
			glMatrixMode(GL_MODELVIEW);
			glMultMatrixf(&_carcassMatrix[0][0]);
			glColor3f(1.0f, 0.0f, 0.0f);
			glDisable(GL_LIGHTING);

			for (int j = 0; j < 3; j++)
			{
				if (!_chicken[j].IsAlive())
				{
					glPushMatrix();
					_chicken[j].SetShadowMode(true);
					_chicken[j].setTransformations();
					_chicken[j].render();
					_chicken[j].SetShadowMode(false);
					glPopMatrix();
				}
			}
			glEnable(GL_LIGHTING);
			glShadeModel(GL_SMOOTH);
			glPopMatrix();
		}

		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixf(&_shadowMatrix[0][0]);
		glColor3f(0.0f, 0.0f, 0.0f);
		glDisable(GL_LIGHTING);

		if (_chicken[0].IsAlive() || _chicken[1].IsAlive() || _chicken[2].IsAlive())
		{
			for (int k = 0; k < 3; k++)
			{
				if (_chicken[k].IsAlive())
				{
					glPushMatrix();
					_chicken[k].SetShadowMode(true);
					_chicken[k].setTransformations();
					_chicken[k].render();
					_chicken[k].SetShadowMode(false);
					glPopMatrix();
				}
			}
		}

		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		_roadRoller.SetShadowMode(true);
		_roadRoller.setTransformations();
		_roadRoller.render();
		_roadRoller.SetShadowMode(false);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		glPopMatrix();
	}
};

Scene g_Scene;

void onInitialization()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	g_Scene.Build();

	glutPostRedisplay();
}

void onDisplay()
{
	glClearColor(0.0f, 0.604f, 0.804f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_Scene._cam.setupProjection_gl();
	g_Scene._cam.setupModelView_gl();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	g_Scene.Render();
	glPopMatrix();

	g_Scene._inCar.setupProjection_gl();
	g_Scene._inCar.setupModelView_gl();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	g_Scene.Render();
	glPopMatrix();

	g_Scene._chickenView.setupProjection_gl();
	g_Scene._chickenView.setupModelView_gl();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	g_Scene.Render();
	glPopMatrix();

	glutSwapBuffers();
}

void onKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		g_Scene.StartChicken();
		break;
	case 'f':
		g_Scene.AccelerateRoller();
		break;
	case 'n':
		g_Scene.StillRoller();
		break;
	case 'b':
		g_Scene.DeccelerateRoller();
		break;
	case '\x1b': // that's the 'Esc' key
		glutLeaveMainLoop();
		break;
	}
}

void onMouse(int button, int state, int x, int y)
{
}

void g_SimulateWorld(float timeStart, float timeEnd)
{
	if (timeStart - g_TimeElapsed >= 10000.0f)
		g_TimeElapsed = timeStart;

	for (float tCurrent = timeStart; tCurrent < timeEnd; tCurrent += g_DeltaT)
	{
		float deltaT = ((g_DeltaT < (timeEnd - tCurrent)) ? (g_DeltaT) : (timeEnd - tCurrent));
		g_Scene.Update(deltaT, tCurrent - g_TimeElapsed);
	}
}

void onIdle()
{
	float oldTime = g_Time;
	g_Time = glutGet(GLUT_ELAPSED_TIME);
	g_SimulateWorld(oldTime, g_Time);
	glutPostRedisplay();
}

void onExit()
{
	std::cout << "Bye.";
}

// entry point
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Roadrolla'");
	atexit(onExit);

	// sets GL_MODELVIEW and GL_PROJECTION matrices to identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// performs initializing tasks
	onInitialization();

	// registers event handlers
	glutDisplayFunc(onDisplay);
	glutMouseFunc(onMouse);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);

	glutMainLoop();

#if defined(_DEBUG) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}