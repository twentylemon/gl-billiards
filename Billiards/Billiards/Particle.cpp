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
    rotation = Vector();
}


/**
 * Getters/Setters.
**/
void Particle::setPosition(double x, double y, double z){ position.set(x, y, z); }
void Particle::setPosition(int idx, double val){ position.set(idx, val); }
void Particle::setPosition(Vector val){ position.set(val.data()); }
double Particle::getPosition(int idx){ return position.get(idx); }
Vector Particle::getPosition(){ return position; }

void Particle::setVelocity(double x, double y, double z){ velocity.set(x, y, z); }
void Particle::setVelocity(int idx, double val){ velocity.set(idx, val); }
void Particle::setVelocity(Vector val){ velocity.set(val.data()); }
double Particle::getVelocity(int idx){ return velocity.get(idx); }
Vector Particle::getVelocity(){ return velocity; }

void Particle::setRotation(double x, double y, double z){ rotation.set(x, y, z); }
void Particle::setRotation(int idx, double val){ rotation.set(idx, val); }
void Particle::setRotation(Vector val){ rotation.set(val.data()); }
double Particle::getRotation(int idx){ return rotation.get(idx); }
Vector Particle::getRotation(){ return rotation; }

bool Particle::isMoving(){ return velocity.lengthSq() > 0; }

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
