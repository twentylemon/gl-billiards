/**
 * Event.cpp
 * Implementation of event handlers.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-20
**/
#include "Event.h"

/**
 * Event constructor. Just stores the original dt for the frame time span.
**/
Event::Event(double dt){
    time = dt;
}


/**
 * Getters/Setters.
**/
double Event::getTime(){ return time; }


/**
 * CollisionEvent constructor.
 *
 * @param time the time at which this event occurs
 * @param ball1 the first ball in the collision
 * @param ball2 the second ball in the collision
**/
CollisionEvent::CollisionEvent(double time, Ball* ball1, Ball* ball2) : Event(time){
    this->ball1 = ball1;
    this->ball2 = ball2;
}


/**
 * Handles speed updates of the collision event.
**/
void CollisionEvent::handle(){
    // TODO
    double ballRadius = ball1->getRadius();
    double impulseTime = IMPULSE_TIME;

    //got the normal to the collision plane
    Vector normal = Vector::subtract(ball1->getPosition(), ball2->getPosition());
    normal.normalize();
    Vector negNormal = Vector::scale(normal, -1.0);

    //find the normal/tangential components for each of the balls velocities
    Vector norm1 = Vector::scale(negNormal, Vector::dotProduct(ball1->getVelocity(), negNormal));
}


/**
 * BankEvent constructor.
 *
 * @param time the time at which this event occurs
 * @param ball the ball involved in the bank
 * @param axis the bank axis against which the ball hits
**/
BankEvent::BankEvent(double time, Ball* ball, BankAxis axis) : Event(time){
    this->ball = ball;
    this->axis = axis;
}


/**
 * Handles the velocity update after a bank event.
**/
void BankEvent::handle(){
    // TODO
}
