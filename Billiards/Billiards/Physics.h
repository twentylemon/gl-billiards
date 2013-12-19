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
using std::auto_ptr;

class Physics
{
public:
    ~Physics(void);

    static Physics* getInstance();

    Array3* getHitSpot(Cue*, Ball*, double, double);
    Array3* cueShot(Cue*, Ball*);
    Array3* cueShot(Cue*, Ball*, Array3*);
    Array3* cueShot(Cue*, Ball*, double, double);
    
private:
    Physics(void);

    double cueBallContactTime;
    double cueSpringConstant;

    double ballMass;
    double ballRadius;

    double tableWidth;
    double tableHeight;
};

