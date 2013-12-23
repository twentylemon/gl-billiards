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
#include "GL/glut.h"
#include "Model.h"
#include "Ball.h"
#include "Table.h"
#include "Player.h"
#include "Physics.h"

#define ORTHO_WIDTH 2
#define ORTHO_HEIGHT 2
#define ORTHO_DEPTH 2

//gluPerspective constants
#define MAX_CLIPPING 10000.0
#define MIN_CLIPPING 1.0
#define PERSPECTIVE_FIELD_OF_VIEW_ANGLE 45.0

#define ESC 27

typedef struct {
    int glutWindow;
	int windowHeight;
	int windowWidth;

    std::vector<Ball*> balls;
    Table* table;
	Player* player1;

    Physics* physics;
    std::clock_t clock;
} Global;

extern Global global;

//init.cpp
void init();
void resizeWindow(int width, int height);
