#include "Chicken.h"

Chicken::Chicken()
{
}

void Chicken::build()
{
	Vector nullVec = Vector();

	Ellipsoid* body = new Ellipsoid(0.5f, 0.3f, 0.2f);
	Ellipsoid* head = new Ellipsoid(0.2f, 0.1f, 0.1f);
	Ellipsoid* eye = new Ellipsoid(0.02f, 0.02f, 0.02f);
	Ellipsoid* knee = new Ellipsoid(0.04f, 0.04f, 0.04f);
	Cylinder* neck = new Cylinder(0.08f, 0.6f, 1.0f);
	Cylinder* upperLeg = new Cylinder(0.03f, 0.5f, 1.0f);
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

void Chicken::render()
{
	if (!_isShadowMode)
		_bodyMaterial.setup_gl();
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
	_body->render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2f, 1.0f, 0.0f);
	glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
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
	glTranslatef(0.168f, -0.028f, 0.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	_beak->render();
	glPopMatrix();
	glPushMatrix();
	if (!_isShadowMode)
		_limbMaterial.setup_gl();
	glTranslatef(0.12f, 0.08f, 0.0f);
	glPushMatrix();
	glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
	_mohawk->render();
	glPopMatrix();
	glTranslatef(-0.06f, 0.0f, 0.0f);
	_mohawk->render();
	glTranslatef(-0.06f, 0.0f, 0.0f);
	_mohawk->render();
	glTranslatef(-0.06f, 0.0f, 0.0f);
	_mohawk->render();
	glTranslatef(-0.06f, 0.0f, 0.0f);
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
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	_upperLeg->render();
	glPopMatrix();
	glPushMatrix();
	_knee->render();
	glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	_upperLeg->render();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	_knee->render();
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	_upperLeg->render();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.08f, 0.4f, 0.2f);
	glRotatef(-110.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	_upperLeg->render();
	glPopMatrix();
	glPushMatrix();
	_knee->render();
	glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	_upperLeg->render();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	_knee->render();
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	_upperLeg->render();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Chicken::setTransformations()
{
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
}

void Chicken::update(float deltaT)
{
	if (_isAlive)
	{
		_position += _velocity * deltaT;
	}

	if (_position.z < -6.0f)
	{
		_velocity.z = 0.0f;
	}
}

Chicken::~Chicken()
{
}
