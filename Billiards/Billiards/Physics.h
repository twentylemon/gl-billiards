/**
 * Game master and physics handler.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-18
**/
#pragma once
#include "Array3.h"
#include "Cue.h"
#include "Ball.h"
#include "Table.h"

class Physics
{
public:
    ~Physics(void);

    static Physics* getInstance();

    Array3* getHitSpot(Ball*, double, double);
    Array3* cueShot(Cue*, Ball*);
    Array3* cueShot(Cue*, Ball*, Array3*);
    
private:
    Physics(void);

    double cueBallContactTime;
    double cueSpringConstant;

    double ballMass;
    double ballRadius;
};

