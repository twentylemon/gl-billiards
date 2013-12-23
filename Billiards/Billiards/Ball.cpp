/**
 * Ball.cpp
 * Implementation for a pool ball.
 *
 * @author Taras Myckaskiw
 * @version 1.0
 * @since 2013-12-16
**/
#include "Ball.h"

/**
 * Default constructor.
 *
 * @param number the number on the ball, 0 if the cue ball
**/
Ball::Ball(int number) : RADIUS(BALL_RADIUS), DIAMETER(2.0 * BALL_RADIUS), MASS(BALL_MASS), Particle(){
    model = Model("Objects/ball.3DS", "Objects/textures/ball" + std::to_string(number) + ".bmp");
    sunk = false;
    double offset = 1.0/4.0 * TABLE_WIDTH;
    switch (number){
    case 0: setPosition(-1.5/5.0 * TABLE_WIDTH, 0, 0); break;
    case 1: setPosition(offset, 0, 0); break;
    case 2: setPosition(offset + 4.0 * DIAMETER, 2.0 * RADIUS, 0); break;
    case 3: setPosition(offset + DIAMETER, -RADIUS, 0); break;
    case 4: setPosition(offset + 3.0 * DIAMETER, -RADIUS, 0); break;
    case 5: setPosition(offset + 4.0 * DIAMETER, -2.0 * RADIUS, 0); break;
    case 6: setPosition(offset + 2.0 * DIAMETER, 2.0 * RADIUS, 0); break;
    case 7: setPosition(offset + 4.0 * DIAMETER, 4.0 * RADIUS, 0); break;
    case 8: setPosition(offset + 2.0 * DIAMETER, 0, 0); break;
    case 9: setPosition(offset + 3.0 * DIAMETER, -3.0 * RADIUS, 0); break;
    case 10: setPosition(offset + 4.0 * DIAMETER, 0, 0); break;
    case 11: setPosition(offset + DIAMETER, RADIUS, 0); break;
    case 12: setPosition(offset + 4.0 * DIAMETER, -4.0 * RADIUS, 0); break;
    case 13: setPosition(offset + 3.0 * DIAMETER, 3.0 * RADIUS, 0); break;
    case 14: setPosition(offset + 2.0 * DIAMETER, -2.0 * RADIUS, 0); break;
    case 15: setPosition(offset + 3.0 * DIAMETER, RADIUS, 0); break;
    }
    yaw = Vector(rand(), rand(), rand());
    yaw.normalize();

    Vector random = Vector(rand(), rand(), rand());
    pitch = Vector::subtract(random, Vector::project(random, yaw));
    pitch.normalize();

    roll = yaw.crossProduct(pitch);
    roll.normalize();
}


/**
 * Draws this ball. The ball is translated and rotated before drawing.
**/
void Ball::draw(){
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glTranslated(position.getX(), position.getY(), position.getZ());
    //glRotated(90, 1, 0, 0);
    //glRotated(0, 0, 1, 0);
    model.draw();
    glPopMatrix();
    rotation.setX(rotation.getX() + 1);
}


/**
 * Sinks this ball into a pocket.
**/
void Ball::sink(){
    setPosition(Vector::add(position, Vector(0, 0, -8.0 * 0.0254)));
    setVelocity(0, 0, 0);
    setAngular(0, 0, 0);
    setSunk(true);
}


/**
 * Getters/Setters.
**/
void Ball::setSunk(bool s){ sunk = s; }
double Ball::getRadius(){ return RADIUS; }
double Ball::getDiameter(){ return DIAMETER; }
double Ball::getMass(){ return MASS; }
bool Ball::isSunk(){ return sunk; }


/**
 * Destructor.
**/
Ball::~Ball(void){
}
