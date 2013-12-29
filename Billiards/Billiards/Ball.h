/**
 * Ball.h
 * Represents a pool ball. Fun fun.
 *
 * @author Taras Myckaskiw
 * @version 1.0
 * @since 2013-12-16
**/
#pragma once
#include <new>
#include <string>
#include <deque>
#include <utility>
#include "Particle.h"
#include "Model.h"
#include "glut.h"

#define BALL_RADIUS 1.125 * 0.0254
#define TABLE_WIDTH 9.0 * 12.0 * 0.0254
#define TABLE_HEIGHT 4.5 * 12.0 * 0.0254
#define BALL_MASS 0.170079

#define BALL_TYPE_NONE 0
#define BALL_TYPE_SOLID 1
#define BALL_TYPE_STRIPE 2

class Ball : public Particle
{
public:
    Ball(int);
    ~Ball(void);

    void draw();
    void pushRotation(Vector, double);
    void consolidateRotation();
    void sink();

    double getRadius();
    double getDiameter();
    double getMass();

    bool isSunk();
    void setSunk(bool);

private:
    const double RADIUS;
    const double DIAMETER;
    const double MASS;

    double rotMatrix[16];
    std::deque<std::pair<Vector, double>> rotList;
    void doRotate();

    bool sunk;
};

