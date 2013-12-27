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
    //got the normal to the collision plane
    Vector normal = Vector::subtract(ball1->getPosition(), ball2->getPosition());
    normal.normalize();
    Vector negNormal = Vector::scale(normal, -1.0);

    //find the normal/tangential components for each of the balls velocities
    Vector norm1 = Vector::scale(negNormal, Vector::dotProduct(ball1->getVelocity(), negNormal));
    Vector tan1 = Vector::subtract(ball1->getVelocity(), norm1);
    Vector norm2 = Vector::scale(normal, Vector::dotProduct(ball2->getVelocity(), normal));
    Vector tan2 = Vector::subtract(ball2->getVelocity(), norm2);

    //conservation of linear momentum, assume the collision is 100% elastic
    ball1->setVelocity(Vector::add(tan1, norm2));
    ball2->setVelocity(Vector::add(tan2, norm1));
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
    Vector velocity = ball->getVelocity();

    // TODO part of angular momentum is converted to linear momentum

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


/**
 * BankEvent constructor.
 *
 * @param time the time at which this event occurs
 * @param ball the ball involved in the bank
 * @param axis the bank axis against which the ball hits
**/
BankEvent2::BankEvent2(double time, Ball* ball, Cushion cushion) : Event(time){
    this->ball = ball;
    this->cushion = cushion;
}


/**
 * Handles the velocity update after a bank event.
**/
void BankEvent2::handle(){

    std::cerr << "handling bank event" << std::endl;

    Vector velocity = ball->getVelocity();
    Vector normal = cushion.getNormal();

    //std::cerr << "old: " << velocity.toString() << std::endl;
    //reflect the velocity through the cushion normal
    normal.scale(2.0 * velocity.dotProduct(normal));
    velocity.subtract(normal);

    //loss some speed due to friction
    velocity.scale(1.0 - CUSHION_FRICTION_LOSS);
    ball->setVelocity(velocity);
    ball->addPosition(Vector::scale(cushion.getNormal(), 0.001));   //add a little bounce
    //std::cerr << "new: " << velocity.toString() << std::endl << std::endl;
}
