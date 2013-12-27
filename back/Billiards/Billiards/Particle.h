/**
 * Definition of a basic Particle. An abstract base class for any thing in the world.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-10
**/
#pragma once
#include <new>
#include <string>
#include <iostream>
#include "Vector.h"
#include "Model.h"

class Particle {
public:
    Particle(void);
    ~Particle(void);

    void setPosition(double, double, double);
    void setPosition(int, double);
    void setPosition(Vector);
    void addPosition(Vector);
    double getPosition(int);
    Vector getPosition();

    void setVelocity(double, double, double);
    void setVelocity(int, double);
    void setVelocity(Vector);
    void addVelocity(Vector);
    double getVelocity(int);
    Vector getVelocity();

    void setAngular(double, double, double);
    void setAngular(int, double);
    void setAngular(Vector);
    void addAngular(Vector);
    double getAngular(int);
    Vector getAngular();

    void setRotation(double, double, double);
    void setRotation(int, double);
    void setRotation(Vector);
    void addRotation(Vector);
    double getRotation(int);
    Vector getRotation();

    bool isMoving();
    void stopMoving();

    std::string toString();
    
protected:
    Vector position;    //position in (x,y,z)
    Vector velocity;    //speed in (x,y,z)
    Vector angular;     //angular velocity
    Vector rotation;
    Model model;
};
