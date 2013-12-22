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

    yaw = Vector();
    pitch = Vector();
    roll = Vector();
    for (int i = 0; i < 15; i++){
        rotationMatrix[i] = 0;
    }
    rotationMatrix[15] = 1.0;
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

void Particle::setAngular(double x, double y, double z){ angular.set(x, y, z); }
void Particle::setAngular(int idx, double val){ angular.set(idx, val); }
void Particle::setAngular(Vector val){ angular.set(val.data()); }
double Particle::getAngular(int idx){ return angular.get(idx); }
Vector Particle::getAngular(){ return angular; }

void Particle::setRotation(double x, double y, double z){ rotation.set(x, y, z); }
void Particle::setRotation(int idx, double val){ rotation.set(idx, val); }
void Particle::setRotation(Vector val){ rotation.set(val.data()); }
double Particle::getRotation(int idx){ return rotation.get(idx); }
Vector Particle::getRotation(){ return rotation; }

void Particle::setYaw(double x, double y, double z){ yaw.set(x, y, z); }
void Particle::setYaw(int idx, double val){ yaw.set(idx, val); }
void Particle::setYaw(Vector val){ yaw.set(val.data()); }
double Particle::getYaw(int idx){ return yaw.get(idx); }
Vector Particle::getYaw(){ return yaw; }

void Particle::setPitch(double x, double y, double z){ pitch.set(x, y, z); }
void Particle::setPitch(int idx, double val){ pitch.set(idx, val); }
void Particle::setPitch(Vector val){ pitch.set(val.data()); }
double Particle::getPitch(int idx){ return pitch.get(idx); }
Vector Particle::getPitch(){ return pitch; }

void Particle::setRoll(double x, double y, double z){ roll.set(x, y, z); }
void Particle::setRoll(int idx, double val){ roll.set(idx, val); }
void Particle::setRoll(Vector val){ roll.set(val.data()); }
double Particle::getRoll(int idx){ return roll.get(idx); }
Vector Particle::getRoll(){ return roll; }

void Particle::updateRotationMatrix(){
    yaw.normalize();
    rotationMatrix[0] = yaw.getX();
    rotationMatrix[1] = yaw.getY();
    rotationMatrix[2] = yaw.getZ();
    pitch.normalize();
    rotationMatrix[3] = pitch.getX();
    rotationMatrix[4] = pitch.getY();
    rotationMatrix[5] = pitch.getZ();
    roll.normalize();
    rotationMatrix[6] = roll.getX();
    rotationMatrix[7] = roll.getY();
    rotationMatrix[8] = roll.getZ();
}
double* Particle::getRotationMatrix(){ return rotationMatrix; }

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
            "yaw     : " + yaw.toString() + "\n" +
            "pitch   : " + pitch.toString() + "\n" +
            "roll    : " + roll.toString() + "\n";
}


/**
 * Destructor. Nothing to destroy.
**/
Particle::~Particle(void){
}
