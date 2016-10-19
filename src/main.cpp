// See LICENSE for details.

#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif // to make it work on Microsoft Windows, too


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
#include <iostream>
#include "Primitives/Circle.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

float g_Time = 0.0f;
float g_TimeElapsed = 0.0f;
float g_DeltaT = 0.1f;

class LegacyPrimitive
{
protected:
	bool isTextured;
	Material _material;
public:
	virtual void TesselateAndRender_gl() = 0;
};

class LegacyParametricSurface : LegacyPrimitive
{
protected:
	float _uMinValue, _uMaxValue, _uStep;
	float _vMinValue, _vMaxValue, _vStep;
	bool _hasShadow;
public:
	float lightX, lightY;
	LegacyParametricSurface() {}
	LegacyParametricSurface(float uMin_in, float uMax_in, float uStep_in, float vMin_in, float vMax_in, float vStep_in, bool hasShadow_in) : _uMinValue(uMin_in), _uMaxValue(uMax_in), _uStep(uStep_in), _vMinValue(vMin_in), _vMaxValue(vMax_in), _vStep(vStep_in), _hasShadow(hasShadow_in) {	}

	virtual Vector r(float u, float v) = 0;
	virtual Vector n(float u, float v) = 0;

	virtual void TesselateAndRender_gl()
	{
		Vector rVec, nVec, rVecShadow;

		glEnable(GL_NORMALIZE);
		glBegin(GL_QUADS);
		for (float u = _uMinValue; u < _uMaxValue; u += _uStep)
		{
			for (float v = _vMinValue; v < _vMaxValue; v += _vStep)
			{
				rVec = r(u, v);
				nVec = n(u, v);
				glTexCoord2f(u, v);
				glNormal3f(nVec.x, nVec.y, nVec.z);
				glVertex3f(rVec.x, rVec.y, rVec.z);

				rVec = r(u + _uStep, v);
				nVec = n(u + _uStep, v);
				glTexCoord2f(u + _uStep, v);
				glNormal3f(nVec.x, nVec.y, nVec.z);
				glVertex3f(rVec.x, rVec.y, rVec.z);

				rVec = r(u + _uStep, v + _vStep);
				nVec = n(u + _uStep, v + _vStep);
				glTexCoord2f(u + _uStep, v + _vStep);
				glNormal3f(nVec.x, nVec.y, nVec.z);
				glVertex3f(rVec.x, rVec.y, rVec.z);

				rVec = r(u, v + _vStep);
				nVec = n(u, v + _vStep);
				glTexCoord2f(u, v + _vStep);
				glNormal3f(nVec.x, nVec.y, nVec.z);
				glVertex3f(rVec.x, rVec.y, rVec.z);
			}
		}
		glEnd();
	}
};

class Ellipsoid : public LegacyParametricSurface
{
private:
	float _paramA, _paramB, _paramC;
public:
	Ellipsoid() {}
	Ellipsoid(float paramA_in, float paramB_in, float paramC_in) : LegacyParametricSurface(-1.57079632f, 1.57079632f, 0.19634954f, -3.1415926535f, 3.1415926535f, 0.39269908f, true), _paramA(paramA_in), _paramB(paramB_in), _paramC(paramC_in) {}

	Vector r(float u, float v)
	{
		Vector result;
		result.x = _paramA * cosf(u) * cosf(v);
		result.y = _paramB * cosf(u) * sinf(v);
		result.z = _paramC * sinf(u);
		return result;
	}

	Vector n(float u, float v)
	{
		Vector result;
		Vector rDerivedU(_paramA * -sinf(u) * cosf(v), _paramB * -sinf(u) * sinf(v), _paramC * cosf(u));
		Vector rDerivedV(_paramA * cosf(u) * -sinf(v), _paramB * cosf(u) * cosf(v), 0.0f);
		result = rDerivedU % rDerivedV;
		return result;
	}
};

class Cylinder : public LegacyParametricSurface
{
private:
	float _paramA, _paramB, _radius, _height, _resolution;
public:
	Cylinder() {}
	Cylinder(float paramA_in, float paramB_in, float radius_in, float height_in, float resolution_in) : LegacyParametricSurface(-3.1415926535f, 3.1415926535f, 0.39269908f, 0, height_in, height_in / resolution_in, true), _paramA(paramA_in), _paramB(paramB_in), _radius(radius_in), _height(height_in), _resolution(resolution_in) {}

	Vector r(float u, float v)
	{
		Vector result;
		result.x = _paramA + _radius * cosf(u);
		result.y = _paramB + _radius * sinf(u);
		result.z = _resolution * v;
		return result;
	}

	Vector n(float u, float v)
	{
		Vector rDerivedU(_radius * -(sinf(u)), _radius * cosf(u), 0.0f);
		Vector rDerivedV(0.0f, 0.0f, _resolution);
		return rDerivedU % rDerivedV;
	}
};

class Cone : public LegacyParametricSurface
{
private:
	float _paramA, _paramB, _radius, _height, _resolution;
public:
	Cone() {}
	Cone(float paramA_in, float paramB_in, float radius_in, float height_in, float resolution_in) : LegacyParametricSurface(-3.1415926535f, 3.1415926535f, 0.39269908f, -(height_in / 2.0f), (height_in / 2.0f), height_in / resolution_in, true), _paramA(paramA_in), _paramB(paramB_in), _radius(radius_in), _height(height_in), _resolution(resolution_in) {}

	Vector r(float u, float v)
	{
		Vector result;
		float coneDivider = 1.0f - ((v + (_height / 2.0f)) / _height);

		if (coneDivider > 0.0f)
		{
			result.x = _paramA + _radius * coneDivider * cosf(u);
			result.y = _resolution * v;
			result.z = _paramB + _radius * coneDivider * sinf(u);
		}

		return result;
	}

	Vector n(float u, float v)
	{
		float coneDivider = 1.0f - ((v + (_height / 2.0f)) / _height);

		if (coneDivider != 0.0f)
		{
			Vector rDerivedU(_radius * coneDivider * -(sinf(u)), 0.0f, _radius * coneDivider * cosf(u));
			Vector rDerivedV(0.0f, _resolution, 0.0f);
			return rDerivedU % rDerivedV;
		}
		else
			return Vector(0.0f, 0.0f, 0.0f);
	}
};

class Plane : public LegacyParametricSurface
{
private:
	float _height, _resolution;
public:
	Plane() {}
	Plane(float width_in, float depth_in, float height_in, float resolution_in) : LegacyParametricSurface(-(width_in / 2.0f), width_in / 2.0f, width_in / resolution_in, -(depth_in / 2.0f), depth_in / 2.0f, depth_in / resolution_in, false), _height(height_in), _resolution(resolution_in) {}

	Vector r(float u, float v)
	{
		Vector result;
		result.x = _resolution * u;
		result.y = _height;
		result.z = _resolution * v;
		return result;
	}

	Vector n(float u, float v)
	{
		Vector rDerivedU(_resolution, 0.0f, 0.0f);
		Vector rDerivedV(0.0f, 0.0f, _resolution);
		return rDerivedU % rDerivedV;
	}
};

class ObjectBase : public LegacyPrimitive
{
protected:
	bool _isShadowMode;
	float _boundingRadius;
	Vector _acceleration;
	Vector _velocity;
	Vector _position;

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
	Cylinder _wheel, _exhaust;
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
	}

	void Build()
	{
		Vector nullVec = Vector(0.0f, 0.0f, 0.0f);

		Circle* wheelSide = new Circle(0.0f, 0.0f, 0.3f, 1.0f);
		Cylinder wheel(0.0f, 0.0f, 1.0f, 2.0f, 1.0f);
		Cylinder exhaust(0.0f, 0.0f, 0.16f, 2.0f, 1.0f);

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

		wheelSide->lightX = _wheel.lightX = _exhaust.lightX = -4.0f;
		wheelSide->lightY = _wheel.lightY = _exhaust.lightY = 8.0f;

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

	void Update(float deltaT)
	{
		_velocity += _acceleration * deltaT;
		_position += _velocity * deltaT;

		_rotateVelocity += 0.3f * _acceleration.x * deltaT;
		_rotateFi -= _rotateVelocity * deltaT * 0.3183f * 180.0f;
	}

	void SetTransformations_gl()
	{
		glTranslatef(_position.x, 1.0f + _position.y, _position.z);
	}

	void TesselateAndRender_gl()
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
		_wheelSide->TesselateAndRender_gl();
		glPopMatrix();

		if (!_isShadowMode)
			_texture.setup_gl();
		glPushMatrix();
		glTranslatef(2.0f, 0.0f, -1.0f);
		glRotatef(_rotateFi, 0.0f, 0.0f, 1.0f);
		_wheel.TesselateAndRender_gl();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2.0f, 0.0f, -1.0f);
		glRotatef(_rotateFi, 0.0f, 0.0f, 1.0f);
		_wheel.TesselateAndRender_gl();
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
		_exhaust.TesselateAndRender_gl();
		glPopMatrix();
	}
};

class Chicken : public ObjectBase
{
private:
	bool _isAlive;
	bool _isMoving;

	Ellipsoid _body, _head, _eye, _knee;
	Cylinder _neck, _upperLeg;
	Cone _beak, _mohawk;

	Material _eyeMaterial;
	Material _bodyMaterial;
	Material _limbMaterial;

public:
	Chicken() {}

	void Build()
	{
		Vector nullVec = Vector();

		Ellipsoid body(0.5f, 0.3f, 0.2f);
		Ellipsoid head(0.2f, 0.1f, 0.1f);
		Ellipsoid eye(0.02f, 0.02f, 0.02f);
		Ellipsoid knee(0.04f, 0.04f, 0.04f);
		Cylinder neck(0.0f, 0.0f, 0.08f, 0.6f, 1.0f);
		Cylinder upperLeg(0.0f, 0.0f, 0.03f, 0.5f, 1.0f);
		Cone beak(0.0f, 0.0f, 0.04f, 0.2f, 1.0f);
		Cone mohawk(0.0f, 0.0f, 0.03f, 0.23f, 1.0f);

		_isAlive = true;
		_acceleration = _velocity = _position = nullVec;
		_boundingRadius = 0.4f;

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

	void SetPosition(Vector position)
	{
		_position = position;
	}

	void SetTransformations_gl()
	{
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	}

	void SetIsMoving(bool isMoving) { _isMoving = isMoving; }

	void SetStillAlive(bool isStillAlive) { _isAlive = isStillAlive; }

	void Update(float deltaT)
	{
		if (_isAlive)
			_position += _velocity * deltaT;
		if (_position.z < -6.0f)
			_velocity.z = 0.0f;
	}

	void TesselateAndRender_gl()
	{
		if (!_isShadowMode)
			_bodyMaterial.setup_gl();
		glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
		glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
		_body.TesselateAndRender_gl();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.3f, 1.6f, 0.0f);
		glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		_neck.TesselateAndRender_gl();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.4f, 1.6f, 0.0f);
		_head.TesselateAndRender_gl();
		glPushMatrix();
		if (!_isShadowMode)
			_eyeMaterial.setup_gl();
		glTranslatef(0.1f, 0.0f, 0.1f);
		_eye.TesselateAndRender_gl();
		glTranslatef(0.0f, 0.0f, -0.2f);
		_eye.TesselateAndRender_gl();
		glPopMatrix();
		glPushMatrix();
		if (!_isShadowMode)
			_limbMaterial.setup_gl();
		glTranslatef(0.25f, -0.028f, 0.0f);
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		_beak.TesselateAndRender_gl();
		glPopMatrix();
		glPushMatrix();
		if (!_isShadowMode)
			_limbMaterial.setup_gl();
		glTranslatef(0.12f, 0.185f, 0.0f);
		glPushMatrix();
		glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
		_mohawk.TesselateAndRender_gl();
		glPopMatrix();
		glTranslatef(-0.06f, 0.0, 0.0f);
		_mohawk.TesselateAndRender_gl();
		glTranslatef(-0.06f, 0.0, 0.0f);
		_mohawk.TesselateAndRender_gl();
		glTranslatef(-0.06f, 0.0, 0.0f);
		_mohawk.TesselateAndRender_gl();
		glTranslatef(-0.06f, 0.0, 0.0f);
		glPushMatrix();
		glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
		_mohawk.TesselateAndRender_gl();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		if (!_isShadowMode)
			_limbMaterial.setup_gl();
		glPushMatrix();
		glTranslatef(-0.08f, 0.4f, -0.2f);
		glRotatef(-80.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
		_upperLeg.TesselateAndRender_gl();
		glPushMatrix();
		_knee.TesselateAndRender_gl();
		glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
		_upperLeg.TesselateAndRender_gl();
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.5f);
		glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
		_knee.TesselateAndRender_gl();
		_upperLeg.TesselateAndRender_gl();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.08f, 0.4f, 0.2f);
		glRotatef(-110.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
		_upperLeg.TesselateAndRender_gl();
		glPushMatrix();
		_knee.TesselateAndRender_gl();
		glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
		_upperLeg.TesselateAndRender_gl();
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.5f);
		glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
		_knee.TesselateAndRender_gl();
		_upperLeg.TesselateAndRender_gl();
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

	Plane _grassy;
	Plane _road;

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

		Plane grass(100.0f, 100.0f, -0.002f, 1.0f);
		Plane road(100.0f, 2.0f, -0.001f, 4.0f);
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
			_chicken[i].Build();
			tempPosition.x = 2.0f + 2.0f * (float)i;
			tempPosition.z = 3.0f;
			_chicken[i].SetPosition(tempPosition);
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

		_roadRoller.Build();
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

		_roadRoller.Update(deltaT);
		_inCar.eyePos.x = _roadRoller.GetPosition().x;
		_inCar.lookAt.x = 6.0f + _roadRoller.GetPosition().x;
		for (int i = 0; i < 3; i++)
		{
			_chicken[i].Update(deltaT);
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
		_grassy.TesselateAndRender_gl();
		glPopMatrix();

		_roadMaterial.setup_gl();
		_roadTexture.setup_gl();
		glPushMatrix();
		glTranslatef(0.0f, -0.001f, 0.00f);
		_road.TesselateAndRender_gl();
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
					_chicken[i].SetTransformations_gl();
					_chicken[i].TesselateAndRender_gl();
					glPopMatrix();
				}
			}
		}

		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		_roadRoller.SetShadowMode(false);
		_roadRoller.SetTransformations_gl();
		_roadRoller.TesselateAndRender_gl();
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
					_chicken[j].SetTransformations_gl();
					_chicken[j].TesselateAndRender_gl();
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
					_chicken[k].SetTransformations_gl();
					_chicken[k].TesselateAndRender_gl();
					_chicken[k].SetShadowMode(false);
					glPopMatrix();
				}
			}
		}

		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		_roadRoller.SetShadowMode(true);
		_roadRoller.SetTransformations_gl();
		_roadRoller.TesselateAndRender_gl();
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