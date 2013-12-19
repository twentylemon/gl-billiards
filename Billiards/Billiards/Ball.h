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
#include "Particle.h"
#include "Model.h"
#include "GL/glut.h"

#define BALL_RADIUS 1.125
#define BALL_MASS 6.0
#define TABLE_WIDTH 9.0 * 12.0
#define TABLE_HEIGHT 4.5 * 12.0

#define BALL_TYPE_SOLID 1
#define BALL_TYPE_STRIPE 2

class Ball : public Particle
{
public:
    Ball(int);
    ~Ball(void);

    void draw();

    double getRadius();
    double getDiameter();
    double getMass();

private:
    const double RADIUS;
    const double DIAMETER;
    const double MASS;

    Array3* rollStart;
};

