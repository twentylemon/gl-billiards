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
    std::cerr << "handling collision event" << std::endl;
    //got the normal to the collision plane
    Vector normal = Vector::subtract(ball1->getPosition(), ball2->getPosition());
    normal.normalize();
    Vector negNormal = Vector::scale(normal, -1.0);

    //find the normal/tangential components for each of the balls velocities
    Vector norm1 = Vector::scale(negNormal, Vector::dotProduct(ball1->getVelocity(), negNormal));
    Vector tan1 = Vector::subtract(ball1->getVelocity(), norm1);
    Vector norm2 = Vector::scale(normal, Vector::dotProduct(ball2->getVelocity(), normal));
    Vector tan2 = Vector::subtract(ball2->getVelocity(), norm2);
    
    //constants
    double ballMass = ball1->getMass();
    double ballRadius = ball1->getRadius();
    double inertia = 2.0/5.0 * ballMass * ballRadius * ballRadius;

    //conservation of linear momentum, assume the collision is 100% elastic
    Vector dv1 = ball1->getVelocity();  //needed for angular below, difference in ball1 velocity
    ball1->setVelocity(Vector::add(tan1, norm2));
    ball2->setVelocity(Vector::add(tan2, norm1));
    dv1.subtract(ball1->getVelocity());
    dv1.scale(ballMass);

    //update angular velocity
    Vector perimeterSpeed1 = Vector::crossProduct(ball1->getAngular(), Vector::scale(normal, -ballRadius));
    Vector perimeterSpeed2 = Vector::crossProduct(ball2->getAngular(), Vector::scale(normal, ballRadius));
    Vector friction = Vector::add(Vector::subtract(perimeterSpeed1, perimeterSpeed2), tan2);
    friction.normalize();
    friction.scale(-dv1.length() * BALL_FRICTION_LOSS);
    Vector dw = Vector::scale(Vector::crossProduct(friction, normal), 2.0 * ballRadius / inertia);
    ball1->setAngular(Vector::add(ball1->getAngular(), dw));
    ball2->setAngular(Vector::add(ball2->getAngular(), dw));
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
    std::cerr << "handling bank event" << std::endl;
    Vector velocity = ball->getVelocity();

    //get the normal and tangential components of the velocity
    Vector norm = Vector();
    if (axis == BankAxis::X){
        velocity.setX(-velocity.getX());
    }
    else if (axis == BankAxis::Y){
        velocity.setY(-velocity.getY());
    }
    velocity.scale(1.0 - CUSHION_FRICTION_LOSS);
    ball->setVelocity(velocity);

    // TODO angular velocity loss, it doesn't change
    Vector angular = ball->getAngular();
    angular.scale(1.0 - CUSHION_FRICTION_LOSS);
    ball->setAngular(angular);
}
