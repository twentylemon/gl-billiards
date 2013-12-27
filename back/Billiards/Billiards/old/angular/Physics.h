/**
 * Physics.h
 * Game master and physics handler.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-18
**/
#pragma once
#include <vector>
#include <algorithm>
#include "Event.h"
#include "Vector.h"
#include "Cue.h"
#include "Ball.h"
#define PI 3.14159
#undef min  //from Model.h -> stdio.h

class Physics
{
public:
    ~Physics(void);

    static Physics* getInstance();

    Vector getHitSpot(Cue*, Ball*, double, double);
    Vector cueShot(Cue*, Ball*);
    Vector cueShot(Cue*, Ball*, Vector);
    Vector cueShot(Cue*, Ball*, double, double);

    bool update(std::vector<Ball*>);
    bool update(std::vector<Ball*>, double);
    
private:
    Physics(void);
    
    void rotate(Ball*, Vector, Vector);
    void rotate(Ball*, double);
    void rollBalls(std::vector<Ball*>, double);
    double calcCollisionTime(Ball*, Ball*);
    double calcBankTime(Ball*, Event::BankAxis);
    void moveBalls(std::vector<Ball*>, double);

    double cueBallContactTime;
    double cueSpringConstant;

    double ballMass;
    double ballRadius;
    double ballRadiusSq;
    double ballCircumference;

    double tableWidth;      //size of entire table
    double tableHeight;
    double tablePlayWidth;  //size of where the balls lay
    double tablePlayHeight;

    int numPockets;
    double pocketSize;
    Vector pockets[6];  //positions of the pockets

    double clothFriction;
    double velocityStop;
    double angularStop;
    double gravity;

    double timeStep;
};
