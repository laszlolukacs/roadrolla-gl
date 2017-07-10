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

int g_clientWidth, g_lastClientWidth = 800;
int g_clientHeight, g_lastClientHeight = 480;
int g_clientPositionX = 100;
int g_clientPositionY = 100;
bool g_windowed = true;

bool g_keystates[256];

int g_lastMouseX = 0;
int g_lastMouseY = 0;
float g_pitch = 0.0f;
float g_yaw = 0.0f;
bool g_pointerWarped = true;

float g_time = 0.0f;
float g_timeElapsed = 0.0f;
float g_deltaT = 0.1f;

Camera* currentCam = nullptr;
Camera roamingCam;
RoadRollerGame game;

void handleMouseInput(float deltaX, float deltaY)
{
	g_yaw += deltaX;
	g_pitch += deltaY;
	if (g_pitch > 74.9f) { g_pitch = 74.9f; }
	if (g_pitch < -74.9f) { g_pitch = -74.9f; }
	if (currentCam != nullptr) {
		currentCam->rotate(g_yaw, g_pitch);
	}
}

void handleKeyboardInput(bool keyStates[])
{
	float cameraSpeed = 0.0001f;
	unsigned char w = 'w';
	if (keyStates[w]) {
		roamingCam.move(roamingCam.frontDir * cameraSpeed);
	}

	unsigned char s = 's';
	if (keyStates[s])
	{
		roamingCam.move(roamingCam.frontDir * -1.0f * cameraSpeed);
	}

	unsigned char a = 'a';
	if (keyStates[a])
	{
		roamingCam.move((roamingCam.frontDir % roamingCam.upDir).normalize() * -1.0f * cameraSpeed);
	}

	unsigned char d = 'd';
	if (keyStates[d])
	{
		roamingCam.move((roamingCam.frontDir % roamingCam.upDir).normalize() * cameraSpeed);
	}
}

void simulateWorld(float timeStart, float timeEnd)
{
	if (timeStart - g_timeElapsed >= 10000.0f)
	{
		g_timeElapsed = timeStart;
	}

	for (float tCurrent = timeStart; tCurrent < timeEnd; tCurrent += g_deltaT)
	{
		handleKeyboardInput(g_keystates);
		float deltaT = ((g_deltaT < (timeEnd - tCurrent)) ? (g_deltaT) : (timeEnd - tCurrent));
		game.update(deltaT, tCurrent - g_timeElapsed);
	}
}

void onKeyboard(unsigned char key, int x, int y)
{
	// for repeated presses
	if (key == 'w' || key == 's' || key == 'a' || key == 'd')
	{
		g_keystates[key] = true;
	}

	// for one-time keypresses
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

void onKeyUp(unsigned char key, int x, int y) {
	if (key == 'w' || key == 's' || key == 'a' || key == 'd')
	{
		g_keystates[key] = false;
	}
}

void onKeyboardSpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		// switches to dashboard cam
		currentCam = &(game.inCam);
		break;
	case GLUT_KEY_F2:
		// switches to chase cam
		currentCam = &(game.chaseCam);
		break;
	case GLUT_KEY_F3:
		// switches to free cam
		roamingCam.eyePos = currentCam->eyePos;
		roamingCam.frontDir = currentCam->frontDir;
		currentCam = &roamingCam;
		break;
	case GLUT_KEY_F4:
		// toggles (the still windowed) fullscreen
		if (g_windowed) {
			g_clientPositionX = glutGet(GLUT_WINDOW_X);
			g_clientPositionY = glutGet(GLUT_WINDOW_Y);
			// hides the window's borders, puts it to (0,0), sets its size to match the current desktop resolution
			glutFullScreen();
			g_windowed = false;
		}
		else
		{
			glutPositionWindow(g_clientPositionX, g_clientPositionY);
			glutReshapeWindow(g_lastClientWidth, g_lastClientHeight);
			g_windowed = true;
		}

		break;
	default: break;
	}

	currentCam->viewportWidth = g_clientWidth;
	currentCam->viewportHeight = g_clientHeight;
	currentCam->setProjectionMatrix();
	glutPostRedisplay();
}

void onMouseMotion(int x, int y)
{
	if (!g_pointerWarped) {
		float mouseSensitivity = 0.233f;
		float deltaX = (x - g_lastMouseX) * mouseSensitivity;
		float deltaY = (g_lastMouseY - y) * mouseSensitivity;

		handleMouseInput(deltaX, deltaY);

		g_pointerWarped = true;
		glutWarpPointer(100, 100);
		g_lastMouseX = 100; // x;
		g_lastMouseY = 100; // y;
		glutPostRedisplay();
	}
	else
	{
		// to prevent infinite callbacks caused by previous glutWarpPointer(...) call
		g_pointerWarped = false;
	}
}

void onReshape(int newWidth, int newHeight)
{
	g_lastClientWidth = g_clientWidth;
	g_lastClientHeight = g_clientHeight;
	g_clientWidth = newWidth;
	g_clientHeight = newHeight;

	if (currentCam != nullptr) {
		currentCam->setViewport(0, 0, newWidth, newHeight);
	}
}

void onInitialization()
{
	glutWarpPointer(100, 100);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutIgnoreKeyRepeat(true);

	// sets GL_MODELVIEW and GL_PROJECTION matrices to identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	printf("Game initialization\n");
	roamingCam.viewportWidth = g_clientWidth;
	roamingCam.viewportHeight = g_clientHeight;
	roamingCam.setProjectionMatrix();
	roamingCam.setModelViewMatrix();

	currentCam = &roamingCam;

	game.build();
	currentCam = &game.chaseCam;

	printf("Roadroller game initialized\n");

	glutPostRedisplay();
}

void onIdle()
{
	float oldTime = g_time;
	g_time = glutGet(GLUT_ELAPSED_TIME);
	simulateWorld(oldTime, g_time);
	glutPostRedisplay();
}

void onDisplay()
{
	glClearColor(0.0f, 0.604f, 0.804f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (currentCam != nullptr) {
		currentCam->setProjectionMatrix();
		currentCam->setModelViewMatrix();
	}

	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	game.render();
	glPopMatrix();

	glutSwapBuffers();
}

void onExit()
{
	currentCam = nullptr;

#if defined(_DEBUG) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
	_CrtDumpMemoryLeaks();
#endif

	printf("Shutting down...");
}

/**
 * The entry point for the application.
 * @param argc the number of arguments passed to the application
 * @param argv array of strings containing the arguments that was passed to the application
 * @return 0 after normal execution.
 */
int main(int argc, char **argv) {
	printf("Roadrolla' application startup\n");
#if defined(_DEBUG) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
	SetConsoleTitle(TEXT("Roadrolla' console"));
#endif
	printf("Graphics initialization\n");

	glutInit(&argc, argv);
	glutInitWindowSize(g_clientWidth, g_clientHeight);
	glutInitWindowPosition(g_clientPositionX, g_clientPositionY);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Roadrolla'");
	atexit(onExit);
	printf("GL Vendor: %s\n", glGetString(GL_VENDOR));
	printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
	printf("GL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL initializated\n");

	// performs initializing tasks
	onInitialization();

	// registers event handlers
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);
	glutKeyboardUpFunc(onKeyUp);
	glutSpecialFunc(onKeyboardSpecial);
	glutPassiveMotionFunc(onMouseMotion);
	glutReshapeFunc(onReshape);

	printf("Roadrolla' application initializated, entering main loop ... \n");

	glutMainLoop();

	onExit();

#if defined(_DEBUG) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}