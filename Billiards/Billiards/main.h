/**
 * Header for the main program.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-10
**/
#pragma once
//hides console window
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
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

#define CUE_BALL_XMIN (-physics::tablePlayWidth / 2.0 + physics::ballRadius)
#define CUE_BALL_XMAX global.balls[0]->getStartPosition().getX()
#define CUE_BALL_YMIN (-physics::tablePlayHeight / 2.0 + physics::ballRadius)
#define CUE_BALL_YMAX (physics::tablePlayHeight / 2.0 - physics::ballRadius)
#define CUE_BALL_STEP (physics::ballRadius / 3.0)

//gluPerspective constants
#define MAX_CLIPPING 10000.0
#define MIN_CLIPPING 0.001
#define PERSPECTIVE_FIELD_OF_VIEW_ANGLE 45.0

typedef struct {
	//glui objects
	int objectType;
	GLUI* glui;
	GLUI_Translation* cueTranslate;
	GLUI_StaticText* playerTextField;
	GLUI_StaticText* shotInfoTextField;
	GLUI_Spinner* shotPowerSpinner;
	GLUI_Translation* cameraTranslate;
    GLUI_RadioGroup* cameraCenterType;
	GLUI_Button* shootButton;

    int follow;
    GLUI_Listbox* cameraFollowList;

	int glutWindow;
	int windowHeight;
	int windowWidth;

    std::vector<Ball*> balls;
    std::vector<Ball> prev;
    std::vector<std::string> msg;

    Table table;
	Vector cameraCenter;

	Player players[2];
    int numPlayers;
    int turn, other;
    int firstBallHit, ballHit;
    bool ballsMoving;
    bool shooting;
    bool scratch;
    bool typeSetThisTurn;
    int shots;
	bool gameOver;

    std::clock_t clock;
} Global;

extern Global global;

void takeShot();
void updateCue();
void updateCamera();

//init.cpp
void init();
void restartGame();

//callback functions for glut/glui
void resizeWindow(int width, int height);
void keyboardFunc(unsigned char key, int x, int y);
void idleFunc();
