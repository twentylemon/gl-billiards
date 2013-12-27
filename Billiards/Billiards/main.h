/**
 * Header for the main program.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-10
**/
#pragma once
#include <iostream>
#include <vector>
#include <new>
#include <ctime>
#include "glut.h"
#include "glui.h"
#include "Model.h"
#include "Ball.h"
#include "Table.h"
#include "Player.h"
#include "Physics.h"
#include "UserInterface.h"

#define ORTHO_WIDTH 100
#define ORTHO_HEIGHT 100
#define ORTHO_DEPTH 100

//gluPerspective constants
#define MAX_CLIPPING 10000.0
#define MIN_CLIPPING 0.1
#define PERSPECTIVE_FIELD_OF_VIEW_ANGLE 45.0

#define ESC 27

typedef struct {

	//glui objects
	int objectType;
	GLUI* glui;
	GLUI_Panel* cuePanel;
	GLUI_Panel* cameraPanel;
	GLUI_Rotation* cueRotation;
	GLUI_StaticText* playerTextField;
	GLUI_Spinner* shotPowerSpinner;

	int glutWindow;
	int windowHeight;
	int windowWidth;

	int mousePositionX;
	int mousePositionY;

    std::vector<Ball*> balls;

    Table table;
	Vector tableRotation;
	float tableZoom;

	Player players[2];
    int numPlayers;
    int turn, other;
    bool ballsMoving;
    bool shooting;

    Physics* physics;
    std::clock_t clock;
} Global;

extern Global global;

//init.cpp
void init();

void resizeWindow(int width, int height);
void keyboardFunc(unsigned char key, int x, int y);
void idleFunc();
void glTranslatefv(Vector translate);
void takeShot();