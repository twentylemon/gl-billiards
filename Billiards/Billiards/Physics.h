/**
 * physics.h
 * Game master and physics handler.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-18
**/
#pragma once
#include <vector>
#include <algorithm>
#include "Table.h"
#include "Vector.h"
#include "Cue.h"
#include "Ball.h"
#define PI 3.14159
#undef min  //from Model.h -> stdio.h

namespace physics
{
    class Cushion
    {
    public:
        Cushion(void){}
        Cushion(Vector, Vector, double);

        void setRadius(double);
        Vector getStart();
        Vector getFinish();
        Vector getLine();
        Vector getNormal();
        Vector getNegRadius();
        double getLength();
        double getLengthSq();

    private:
        Vector start;
        Vector finish;
        Vector line;
        Vector normal;
        Vector negRadius;
        double length, lengthSq;
    };


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


    /**
     * A ball-ball collision.
    **/
    class CollisionEvent : public Event
    {
    public:
        CollisionEvent(double, Ball*, Ball*);
        virtual void handle();

    private:
        Ball* ball1;
        Ball* ball2;
    };


    /**
     * A ball-wall collision.
    **/
    class BankEvent : public Event
    {
    public:
        BankEvent(double, Ball*, Cushion);
        virtual void handle();

    private:
        Ball* ball;
        Cushion cushion;
    };

    Vector cueShot(Cue, Ball*);

    bool update(std::vector<Ball*>);
    bool update(std::vector<Ball*>, double);

    int detectPocket(Vector);
    void rollBalls(std::vector<Ball*>, double);
    double calcCollisionTime(Ball*, Ball*);
    double distance(Ball*, Cushion);
    double calcBankTime(Ball*, Cushion, double);
    void moveBalls(std::vector<Ball*>, double);

    /** cue to ball collision **/
    const double cueBallContactTime = 0.01;  //10ms
    const double cueSpringConstant = 200;    //10 kg m/s^2

    /** ball properties **/
    const double ballMass = 0.170079;        //6 oz (in kg)
    const double ballRadius = 0.028575;      //1.125in (in m)
    const double ballRadiusSq = ballRadius * ballRadius;
    const double ballCircumference = 2.0 * PI * ballRadius;

    /*     width                 ^
     4--------5--------0 h     y |
     |                 | e
     |                 | i     x
     |                 | g     ->
     3--------2--------1 h
   pocket nums labelled  t
    */
    /** table properties **/
    const double tableWidth = 9.0 * 0.0254;          //9 ft (in m), along the x axis
    const double tableHeight = 4.5 * 0.0254;         //4.5 ft (in m), along the y axis
    const double tableRailSize = 4 * 0.0254 / 2.0;   //4in (in m), divided by 2
    const double tablePlayWidth = 100.0 * 0.0254;    //100in (in m)
    const double tablePlayHeight = 50.0 * 0.0254;    //50in (in m)

    /** pockets **/
    const int numPockets = 6;
    const double pocketSize = 4.8 * 0.0254 / 2.0;    //actually corner = 4.5, side = 5 in, close enough
    static const Vector pockets[] = {
        Vector(tablePlayWidth / 2.0 + tableRailSize, tablePlayHeight / 2.0 + tableRailSize, 0),
        Vector(tablePlayWidth / 2.0 + tableRailSize, -tablePlayHeight / 2.0 - tableRailSize, 0),
        Vector(0, -tablePlayHeight / 2.0 - tableRailSize, 0),
        Vector(-tablePlayWidth / 2.0 - tableRailSize, -tablePlayHeight / 2.0 - tableRailSize, 0),
        Vector(-tablePlayWidth / 2.0 - tableRailSize, tablePlayHeight / 2.0 + tableRailSize, 0),
        Vector(0, tablePlayHeight / 2.0 + tableRailSize, 0)
    };

    /** cushions **/
    const double railSize = 2.0 * 0.0254;
    const int numCushions = 26;
    const double cushionFrictionLoss = 0.2;

    const double scale = 0.0254;
    //push cushions further into pockets so there's something to bounce off of
    //const double ctcx[] = { (52 + 17.0/32.0) * scale, (51 + 15.0/32.0) * scale, (50) * scale };
    //const double ctcy[] = { (24 + 3.0/32.0) * scale, (23) * scale, (20 + 16.0/32.0) * scale };
    //const double ctsx[] = { (48 + 30.0/32.0) * scale, (47 + 31.0/32.0) * scale, (45 + 19.0/32.0) * scale, (3 + 3.0/32.0) * scale, (2 + 12.0/32.0) * scale };
    //const double ctsy[] = { (27 + 16.0/32.0) * scale, (26 + 16.0/32.0) * scale, (24 + 31.0/32.0) * scale, (25) * scale, (27 + 16.0/32.0) * scale };
    const double ctcx[] = { (53 + 19.0/32.0) * scale, (51 + 15.0/32.0) * scale, (50) * scale };
    const double ctcy[] = { (25 + 6.0/32.0) * scale, (23) * scale, (20 + 16.0/32.0) * scale };
    const double ctsx[] = { (49 + 29.0/32.0) * scale, (47 + 31.0/32.0) * scale, (45 + 19.0/32.0) * scale, (3 + 3.0/32.0) * scale, (2 + 12.0/32.0) * scale };
    const double ctsy[] = { (28 + 16.0/32.0) * scale, (26 + 16.0/32.0) * scale, (24 + 31.0/32.0) * scale, (25) * scale, (27 + 16.0/32.0) * scale };


    static const Cushion cushions[] = {
        /** from pocket 0 to pocket 1 **/
        Cushion(Vector(ctcx[0], ctcy[0], 0), Vector(ctcx[1], ctcy[1], 0), ballRadius),
        Cushion(Vector(ctcx[1], ctcy[1], 0), Vector(ctcx[2], ctcy[2], 0), ballRadius),
        Cushion(Vector(ctcx[2], ctcy[2], 0), Vector(ctcx[2], -ctcy[2], 0), ballRadius),
        Cushion(Vector(ctcx[2], -ctcy[2], 0), Vector(ctcx[1], -ctcy[1], 0), ballRadius),
        Cushion(Vector(ctcx[1], -ctcy[1], 0), Vector(ctcx[0], -ctcy[0], 0), ballRadius),

        /** from pocket 1 to pocket 2 **/
        Cushion(Vector(ctsx[0], -ctsy[0], 0), Vector(ctsx[1], -ctsy[1], 0), ballRadius),
        Cushion(Vector(ctsx[1], -ctsy[1], 0), Vector(ctsx[2], -ctsy[2], 0), ballRadius),
        Cushion(Vector(ctsx[2], -ctsy[2], 0), Vector(ctsx[3], -ctsy[3], 0), ballRadius),
        Cushion(Vector(ctsx[3], -ctsy[3], 0), Vector(ctsx[4], -ctsy[4], 0), ballRadius),

        /** pocket 2 to pocket 3 **/
        Cushion(Vector(-ctsx[4], -ctsy[4], 0), Vector(-ctsx[3], -ctsy[3], 0), ballRadius),
        Cushion(Vector(-ctsx[3], -ctsy[3], 0), Vector(-ctsx[2], -ctsy[2], 0), ballRadius),
        Cushion(Vector(-ctsx[2], -ctsy[2], 0), Vector(-ctsx[1], -ctsy[1], 0), ballRadius),
        Cushion(Vector(-ctsx[1], -ctsy[1], 0), Vector(-ctsx[0], -ctsy[0], 0), ballRadius),

        /** pocket 3 to pocket 4 **/
        Cushion(Vector(-ctcx[0], -ctcy[0], 0), Vector(-ctcx[1], -ctcy[1], 0), ballRadius),
        Cushion(Vector(-ctcx[1], -ctcy[1], 0), Vector(-ctcx[2], -ctcy[2], 0), ballRadius),
        Cushion(Vector(-ctcx[2], -ctcy[2], 0), Vector(-ctcx[2], ctcy[2], 0), ballRadius),
        Cushion(Vector(-ctcx[2], ctcy[2], 0), Vector(-ctcx[1], ctcy[1], 0), ballRadius),
        Cushion(Vector(-ctcx[1], ctcy[1], 0), Vector(-ctcx[0], ctcy[0], 0), ballRadius),
    
        /** pocket 4 to pocket 5 **/
        Cushion(Vector(-ctsx[0], ctsy[0], 0), Vector(-ctsx[1], ctsy[1], 0), ballRadius),
        Cushion(Vector(-ctsx[1], ctsy[1], 0), Vector(-ctsx[2], ctsy[2], 0), ballRadius),
        Cushion(Vector(-ctsx[2], ctsy[2], 0), Vector(-ctsx[3], ctsy[3], 0), ballRadius),
        Cushion(Vector(-ctsx[3], ctsy[3], 0), Vector(-ctsx[4], ctsy[4], 0), ballRadius),

        /** pocket 5 to pocket 0 **/
        Cushion(Vector(ctsx[4], ctsy[4], 0), Vector(ctsx[3], ctsy[3], 0), ballRadius),
        Cushion(Vector(ctsx[3], ctsy[3], 0), Vector(ctsx[2], ctsy[2], 0), ballRadius),
        Cushion(Vector(ctsx[2], ctsy[2], 0), Vector(ctsx[1], ctsy[1], 0), ballRadius),
        Cushion(Vector(ctsx[1], ctsy[1], 0), Vector(ctsx[0], ctsy[0], 0), ballRadius)
    };

    /** friction **/
    const double feltFriction = 0.005;
    const double velocityStop = 0.01 * 0.01; //use squared value so we can use squared length
    const double angularStop = 0.05;
    const double gravity = 9.8;

    /** animation **/
    const double timeStep = 0.1;
};
