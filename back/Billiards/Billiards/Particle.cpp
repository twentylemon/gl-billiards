/**
 * Implementation of the abstract Particle class.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-10
**/
#include "Particle.h"

/**
 * Default constructor.
**/
Particle::Particle(void){
    position = Vector();
    velocity = Vector();
    angular = Vector();
    rotation = Vector();
}


/**
 * Getters/Setters.
**/
void Particle::setPosition(double x, double y, double z){ position.set(x, y, z); }
void Particle::setPosition(int idx, double val){ position.set(idx, val); }
void Particle::setPosition(Vector val){ position.set(val.data()); }
void Particle::addPosition(Vector val){ position.add(val); }
double Particle::getPosition(int idx){ return position.get(idx); }
Vector Particle::getPosition(){ return position; }

void Particle::setVelocity(double x, double y, double z){ velocity.set(x, y, z); }
void Particle::setVelocity(int idx, double val){ velocity.set(idx, val); }
void Particle::setVelocity(Vector val){ velocity.set(val.data()); }
void Particle::addVelocity(Vector val){ velocity.add(val); }
double Particle::getVelocity(int idx){ return velocity.get(idx); }
Vector Particle::getVelocity(){ return velocity; }

void Particle::setAngular(double x, double y, double z){ angular.set(x, y, z); }
void Particle::setAngular(int idx, double val){ angular.set(idx, val); }
void Particle::setAngular(Vector val){ angular.set(val.data()); }
void Particle::addAngular(Vector val){ angular.add(val); }
double Particle::getAngular(int idx){ return angular.get(idx); }
Vector Particle::getAngular(){ return angular; }

void Particle::setRotation(double x, double y, double z){ rotation.set(x, y, z); }
void Particle::setRotation(int idx, double val){ rotation.set(idx, val); }
void Particle::setRotation(Vector val){ rotation.set(val.data()); }
void Particle::addRotation(Vector val){ rotation.add(val); }
double Particle::getRotation(int idx){ return rotation.get(idx); }
Vector Particle::getRotation(){ return rotation; }

bool Particle::isMoving(){ return velocity.lengthSq() > 0 || angular.lengthSq() > 0; }
void Particle::stopMoving(){
    velocity.set(0, 0, 0);
    angular.set(0, 0, 0);
}


/**
 * Returns a string representation of this particle.
 *
 * @return string of the values in this particle
**/
std::string Particle::toString(){
    return  "position: " + position.toString() + "\n" +
            "velocity: " + velocity.toString() + "\n" +
            "rotation: " + rotation.toString() + "\n";
}


/**
 * Destructor. Nothing to destroy.
**/
Particle::~Particle(void){
}
