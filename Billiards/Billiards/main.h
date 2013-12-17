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

#define ORTHO_WIDTH 100
#define ORTHO_HEIGHT 100
#define ORTHO_DEPTH 100

#define ESC 27

typedef struct {
    int glutWindow;
	int windowHeight;
	int windowWidth;

    std::vector<Ball*> balls;
    Table* table;
} Global;

extern Global global;

//init.cpp
void init();
