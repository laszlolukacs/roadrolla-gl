#include "RoadRoller.h"

RoadRoller::RoadRoller()
{
}

void RoadRoller::build()
{
	Vector nullVec = Vector(0.0f, 0.0f, 0.0f);

	Circle* wheelSide = new Circle(0.0f, 0.0f, 0.3f, 1.0f);
	Cylinder* wheel = new Cylinder(1.0f, 2.0f, 1.0f);
	Cylinder* exhaust = new Cylinder(0.16f, 2.0f, 1.0f);

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

void RoadRoller::render()
{
	if (!_isShadowMode)
		_wheelMaterial.setup_gl();
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(_rotateFi, 0.0f, 1.0f, 0.0f);
	_wheelSide->render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0f, 0.0f, -1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(_rotateFi, 0.0f, 1.0f, 0.0f);
	_wheelSide->render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(_rotateFi, 0.0f, 1.0f, 0.0f);
	_wheelSide->render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.0f, 0.0f, -1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(_rotateFi, 0.0f, 1.0f, 0.0f);
	_wheelSide->render();
	glPopMatrix();

	if (!_isShadowMode)
		_texture.setup_gl();
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, -1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(_rotateFi, 0.0f, 1.0f, 0.0f);
	_wheel->render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.0f, 0.0f, -1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(_rotateFi, 0.0f, 1.0f, 0.0f);
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
	glTranslatef(1.8f, 1.0f, -0.7f);
	_exhaust->render();
	glPopMatrix();
}

void RoadRoller::setTransformations()
{
	glTranslatef(_position.x, 1.0f + _position.y, _position.z);
}

void RoadRoller::update(float deltaT)
{
	_velocity += _acceleration * deltaT;
	_position += _velocity * deltaT;

	_rotateVelocity += 0.3f * _acceleration.x * deltaT;
	_rotateFi -= _rotateVelocity * deltaT * 0.3183f * 180.0f;
}

RoadRoller::~RoadRoller()
{
	if (_wheelSide != nullptr)
	{
		delete _wheelSide;
	}

	if (_wheel != nullptr)
	{
		delete _wheel;
	}

	if (_exhaust != nullptr)
	{
		delete _exhaust;
	}

	//if (_chassis != nullptr)
	//{
	//	delete _chassis;
	//}
}