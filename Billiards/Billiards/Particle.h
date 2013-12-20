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
#include "Vector.h"
#include "Model.h"

class Particle {
public:
    Particle(void);
    ~Particle(void);

    void setPosition(double, double, double);
    void setPosition(int, double);
    void setPosition(Vector*);
    double getPosition(int);
    Vector* getPosition();

    void setSpeed(double, double, double);
    void setSpeed(int, double);
    void setSpeed(Vector*);
    double getSpeed(int);
    Vector* getSpeed();

    void setRotation(double, double, double);
    void setRotation(int, double);
    void setRotation(Vector*);
    double getRotation(int);
    Vector* getRotation();

    bool isMoving();

    std::string toString();

protected:
    Vector* position;
    Vector* speed;
    Vector* rotation;
    Model* model;
};
