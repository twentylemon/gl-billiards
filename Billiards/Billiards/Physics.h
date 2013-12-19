/**
 * Game master and physics handler.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-18
**/
#pragma once
#include <vector>
#include <algorithm>
#include "Array3.h"
#include "Cue.h"
#include "Ball.h"
#include "Table.h"
#undef min  //from Model.h -> stdio.h

class Physics
{
public:
    ~Physics(void);

    static Physics* getInstance();

    enum Event { None, Collision, Bank };
    enum BankAxis { Neither, X, Y };

    Array3* getHitSpot(Cue*, Ball*, double, double);
    Array3* cueShot(Cue*, Ball*);
    Array3* cueShot(Cue*, Ball*, Array3*);
    Array3* cueShot(Cue*, Ball*, double, double);

    bool update(std::vector<Ball*>);
    bool update(std::vector<Ball*>, double);
    
private:
    Physics(void);
    
    void rollBalls(std::vector<Ball*>, double);
    double calcCollisionTime(Ball*, Ball*);
    double calcBankTime(Ball*, BankAxis);
    void collide(Ball*, Ball*);
    void bank(Ball*, BankAxis);
    void moveBalls(std::vector<Ball*>, double);

    double cueBallContactTime;
    double cueSpringConstant;

    double ballMass;
    double ballRadius;
    double ballRadiusSq;

    double tableWidth;
    double tableHeight;
    double tableRailSize;

    double timeStep;
};

