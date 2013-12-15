/**
 * Definition of a basic Particle. An abstract base class for any thing in the world.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-10
**/
#pragma once
#include <string>
#include <new>
#include "Array3.h"
#include "Model.h"

class Particle {
public:
    Particle(void);
    ~Particle(void);

    void setPosition(double, double, double);
    void setPosition(int, double);
    void setPosition(Array3*);
    double getPosition(int);
    Array3* getPosition();

    void setSpeed(double, double, double);
    void setSpeed(int, double);
    void setSpeed(Array3*);
    double getSpeed(int);
    Array3* getSpeed();

    void setRotation(double, double, double);
    void setRotation(int, double);
    void setRotation(Array3*);
    double getRotation(int);
    Array3* getRotation();

    std::string toString();

protected:
    Array3* position;
    Array3* speed;
    Array3* rotation;
    Model* model;
};
