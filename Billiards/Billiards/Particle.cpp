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
    position = new Array3();
    speed = new Array3();
    rotation = new Array3();
}


/**
 * Getters/Setters.
**/
void Particle::setPosition(double x, double y, double z){ position->set(x, y, z); }
void Particle::setPosition(int idx, double val){ position->set(idx, val); }
void Particle::setPosition(Array3* val){ delete position; position = val; }
double Particle::getPosition(int idx){ return position->get(idx); }
Array3* Particle::getPosition(){ return position; }

void Particle::setSpeed(double x, double y, double z){ speed->set(x, y, z); }
void Particle::setSpeed(int idx, double val){ speed->set(idx, val); }
void Particle::setSpeed(Array3* val){ delete speed; speed = val; }
double Particle::getSpeed(int idx){ return speed->get(idx); }
Array3* Particle::getSpeed(){ return speed; }

void Particle::setRotation(double x, double y, double z){ rotation->set(x, y, z); }
void Particle::setRotation(int idx, double val){ rotation->set(idx, val); }
void Particle::setRotation(Array3* val){ delete rotation; position = val; }
double Particle::getRotation(int idx){ return rotation->get(idx); }
Array3* Particle::getRotation(){ return rotation; }


/**
 * Returns a string representation of this particle.
 *
 * @return string of the values in this particle
**/
std::string Particle::toString(){
    return  "position: " + position->toString() + "\n" +
            "speed:    " + speed->toString() + "\n" +
            "rotation: " + rotation->toString() + "\n";
}

/**
 * Destructor. Nothing to destroy.
**/
Particle::~Particle(void){
}
