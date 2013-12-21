/**
 * Event.h
 * Represents a collision or a bank event in the game.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-20
**/
#pragma once
#include "Vector.h"
#include "Ball.h"
#define IMPULSE_TIME 0.05
#define CUSHION_FRICTION_LOSS 0.2

/**
 * Event superclass. Provides general behaviour.
**/
class Event
{
public:
    Event(double);
    enum BankAxis { Neither, X, Y };

    virtual void handle(){}

    double getTime();

protected:
    double time;
};


class CollisionEvent : public Event
{
public:
    CollisionEvent(double, Ball*, Ball*);
    void handle();

private:
    Ball* ball1;
    Ball* ball2;
};


class BankEvent : public Event
{
public:
    BankEvent(double, Ball*, BankAxis);
    void handle();

private:
    Ball* ball;
    BankAxis axis;
};
