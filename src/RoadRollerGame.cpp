#include "RoadRollerGame.h"

RoadRollerGame::RoadRollerGame()
{
}

void RoadRollerGame::build()
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
		tempPosition.x = 2.0f + 2.0f * float(i);
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
	_roadRoller.setPosition(tempPosition);

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

void RoadRollerGame::accelerateRoller()
{
	_roadRoller.setAcceleration(Vector(0.000001f, 0.0f, 0.0f));
}

void RoadRollerGame::setStillRoller()
{
	_roadRoller.setAcceleration(Vector(0.0f, 0.0f, 0.0f));
}

void RoadRollerGame::deccelerateRoller()
{
	_roadRoller.setAcceleration(Vector(-0.000001f, 0.0f, 0.0f));
}

void RoadRollerGame::startNextChicken()
{
	for (int i = 0; i < 3; i++)
	{
		if (_chicken[i].isAlive() && !_chicken[i].isMoving())
		{
			_chicken[i].setIsMoving(true);
			_chicken[i].setVelocity(Vector(0.0f, 0.0f, -0.001f));
			return;
		}
	}
}

void RoadRollerGame::update(float deltaT, float periodTime)
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
	_inCar.eyePos.x = _roadRoller.getPosition().x;
	_inCar.lookAt.x = 6.0f + _roadRoller.getPosition().x;
	for (int i = 0; i < 3; i++)
	{
		_chicken[i].update(deltaT);
		if (_chicken[i].isAlive())
		{
			_chickenView.eyePos = _chicken[i].getPosition();
			_chickenView.eyePos.y = _chicken[i].getPosition().y + 0.8f;
			_chickenView.eyePos.z = _chicken[i].getPosition().z;
			_chickenView.lookAt = _chicken[i].getPosition();
			_chickenView.lookAt.z = -4.0f + _chicken[i].getPosition().z;
			distance = _chicken[i].getPosition() - _roadRoller.getPosition();
			minimumDistance = _chicken[i].getBoundingRadius() + _roadRoller.getBoundingRadius();
			if (distance.length() < minimumDistance)
			{
				_chicken[i].setStillAlive(false);
			}
		}
	}
}

void RoadRollerGame::render()
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
	if (_chicken[0].isAlive() || _chicken[1].isAlive() || _chicken[2].isAlive())
	{
		for (int i = 0; i < 3; i++)
		{
			if (_chicken[i].isAlive())
			{
				glPushMatrix();
				_chicken[i].setShadowMode(false);
				_chicken[i].setTransformations();
				_chicken[i].render();
				glPopMatrix();
			}
		}
	}

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	_roadRoller.setShadowMode(false);
	_roadRoller.setTransformations();
	_roadRoller.render();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	if (!_chicken[0].isAlive() || !_chicken[1].isAlive() || !_chicken[2].isAlive())
	{
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixf(&_carcassMatrix[0][0]);
		glColor3f(1.0f, 0.0f, 0.0f);
		glDisable(GL_LIGHTING);

		for (int j = 0; j < 3; j++)
		{
			if (!_chicken[j].isAlive())
			{
				glPushMatrix();
				_chicken[j].setShadowMode(true);
				_chicken[j].setTransformations();
				_chicken[j].render();
				_chicken[j].setShadowMode(false);
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

	if (_chicken[0].isAlive() || _chicken[1].isAlive() || _chicken[2].isAlive())
	{
		for (int k = 0; k < 3; k++)
		{
			if (_chicken[k].isAlive())
			{
				glPushMatrix();
				_chicken[k].setShadowMode(true);
				_chicken[k].setTransformations();
				_chicken[k].render();
				_chicken[k].setShadowMode(false);
				glPopMatrix();
			}
		}
	}

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	_roadRoller.setShadowMode(true);
	_roadRoller.setTransformations();
	_roadRoller.render();
	_roadRoller.setShadowMode(false);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glPopMatrix();
}

RoadRollerGame::~RoadRollerGame()
{
}
