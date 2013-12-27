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
#include "Cushion.h"
#define BALL_FRICTION_LOSS 0.1  //only applies to angular
#define CUSHION_FRICTION_LOSS 0.2

/**
 * Event superclass. Provides general behaviour.
**/
class Event
{
public:
    Event(double);

    virtual void handle(){}

    double getTime();

protected:
    double time;
};


class CollisionEvent : public Event
{
public:
    CollisionEvent(double, Ball*, Ball*);
    virtual void handle();

private:
    Ball* ball1;
    Ball* ball2;
};


class BankEvent : public Event
{
public:
    BankEvent(double, Ball*, Cushion);
    virtual void handle();

private:
    Ball* ball;
    Cushion cushion;
};
