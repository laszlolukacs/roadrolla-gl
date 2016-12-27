// See LICENSE for details.

#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif // to make it work on Windows, too

#include <iostream>

#include "Camera.h"
#include "RoadRollerGame.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

float g_Time = 0.0f;
float g_TimeElapsed = 0.0f;
float g_DeltaT = 0.1f;

RoadRollerGame game;

void onInitialization()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	game.build();

	glutPostRedisplay();
}

void onDisplay()
{
	glClearColor(0.0f, 0.604f, 0.804f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game._cam.setupProjection_gl();
	game._cam.setupModelView_gl();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	game.render();
	glPopMatrix();

	game._inCar.setupProjection_gl();
	game._inCar.setupModelView_gl();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	game.render();
	glPopMatrix();

	game._chickenView.setupProjection_gl();
	game._chickenView.setupModelView_gl();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	game.render();
	glPopMatrix();

	glutSwapBuffers();
}

void onKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		game.startNextChicken();
		break;
	case 'f':
		game.accelerateRoller();
		break;
	case 'n':
		game.setStillRoller();
		break;
	case 'b':
		game.deccelerateRoller();
		break;
	case '\x1b': // that's the 'Esc' key
		glutLeaveMainLoop();
		break;
	default: break;
	}
}

void onMouse(int button, int state, int x, int y)
{
}

void g_SimulateWorld(float timeStart, float timeEnd)
{
	if (timeStart - g_TimeElapsed >= 10000.0f)
	{
		g_TimeElapsed = timeStart;
	}

	for (float tCurrent = timeStart; tCurrent < timeEnd; tCurrent += g_DeltaT)
	{
		float deltaT = ((g_DeltaT < (timeEnd - tCurrent)) ? (g_DeltaT) : (timeEnd - tCurrent));
		game.update(deltaT, tCurrent - g_TimeElapsed);
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
#if defined(_DEBUG) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
	_CrtDumpMemoryLeaks();
#endif

	std::cout << "Bye.";
}

/**
 * The entry point for the application.
 * @param argc the number of arguments passed to the application
 * @param argv array of strings containing the arguments that was passed to the application
 * @return 0 after normal exectuion.
 */
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