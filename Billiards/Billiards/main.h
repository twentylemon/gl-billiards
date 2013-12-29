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
#include "ui.h"

#include "Ball.h"
#include "Table.h"
#include "Player.h"
#include "physics.h"

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
	GLUI_StaticText* playerTextField;
	GLUI_StaticText* shotInfoTextField;
	GLUI_Spinner* shotPowerSpinner;
	GLUI_Translation* cueTranslate;

	int glutWindow;
	int windowHeight;
	int windowWidth;

	int mousePositionX;
	int mousePositionY;

    std::vector<Ball*> balls;
    std::vector<bool> sinkState;

    Table table;

	Player players[2];
    int numPlayers;
    int turn, other;
    bool ballsMoving;
    bool shooting;
    bool scratch;

    std::clock_t clock;
} Global;

extern Global global;

void glTranslatefv(Vector translate);
void takeShot();
void updateCue();

//init.cpp
void init();

//callback functions for glut/glui
void resizeWindow(int width, int height);
void keyboardFunc(unsigned char key, int x, int y);
void idleFunc();
