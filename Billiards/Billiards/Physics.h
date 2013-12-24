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

    Vector cueShot(Cue, Ball*);

    bool update(std::vector<Ball*>);
    bool update(std::vector<Ball*>, double);
    
private:
    Physics(void);
    
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
    double tableRailSize;
    double tablePlayWidth;  //size of where the balls lay
    double tablePlayHeight;

    int numPockets;
    double pocketSize;
    Vector pockets[6];  //positions of the pockets

    double feltFriction;
    double velocityStop;
    double angularStop;
    double gravity;

    double timeStep;
};
