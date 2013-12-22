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
    double getPosition(int);
    Vector getPosition();

    void setVelocity(double, double, double);
    void setVelocity(int, double);
    void setVelocity(Vector);
    double getVelocity(int);
    Vector getVelocity();

    void setAngular(double, double, double);
    void setAngular(int, double);
    void setAngular(Vector);
    double getAngular(int);
    Vector getAngular();

    void setRotation(double, double, double);
    void setRotation(int, double);
    void setRotation(Vector);
    double getRotation(int);
    Vector getRotation();

    void setYaw(double, double, double);
    void setYaw(int, double);
    void setYaw(Vector);
    double getYaw(int);
    Vector getYaw();

    void setPitch(double, double, double);
    void setPitch(int, double);
    void setPitch(Vector);
    double getPitch(int);
    Vector getPitch();

    void setRoll(double, double, double);
    void setRoll(int, double);
    void setRoll(Vector);
    double getRoll(int);
    Vector getRoll();

    void updateRotationMatrix();
    double* getRotationMatrix();

    bool isMoving();
    void stopMoving();

    std::string toString();
    
protected:
    Vector position;    //position in (x,y,z)
    Vector velocity;    //speed in (x,y,z)
    Vector angular;     //angular velocity
    Vector rotation;
    Vector yaw, pitch, roll;
    double rotationMatrix[16];
    Model model;
};
