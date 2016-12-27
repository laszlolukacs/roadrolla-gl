#ifndef ROADROLLER_GAME_H
#define ROADROLLER_GAME_H

#include <GL/freeglut.h>
#include "Vector.h"
#include "Camera.h"
#include "LightSource.h"
#include "Material.h"
#include "Textures/GrassTexture.h"
#include "Textures/RoadTexture.h"
#include "Actors/Chicken.h"
#include "Actors/RoadRoller.h"
#include "Primitives/Plane.h"

class RoadRollerGame
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

	Chicken _chicken[3];
	RoadRoller _roadRoller;

public:
	Camera _cam;
	Camera _inCar;
	Camera _chickenView;

	RoadRollerGame();
	void build();

	void accelerateRoller();
	void setStillRoller();
	void deccelerateRoller();
	void startNextChicken();

	void update(float deltaT, float periodTime);
	void render();

	~RoadRollerGame();
};

#endif // ROADROLLER_GAME_H
