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
    model = new Model("Objects/ball.3DS", "Objects/textures/ball" + std::to_string(number) + ".bmp");
    double offset = 2.0/9.0 * TABLE_WIDTH;
    switch (number){
    case 0: setPosition(0, -offset, 0); break;
    case 1: setPosition(0, offset, 0); break;
    case 2: setPosition(2.0 * RADIUS, offset + 4.0 * DIAMETER, 0); break;
    case 3: setPosition(-RADIUS, offset + DIAMETER, 0); break;
    case 4: setPosition(-RADIUS, offset + 3.0 * DIAMETER, 0); break;
    case 5: setPosition(-2.0 * RADIUS, offset + 4.0 * DIAMETER, 0); break;
    case 6: setPosition(2.0 * RADIUS, offset + 2.0 * DIAMETER, 0); break;
    case 7: setPosition(4.0 * RADIUS, offset + 4.0 * DIAMETER, 0); break;
    case 8: setPosition(0, offset + 2.0 * DIAMETER, 0); break;
    case 9: setPosition(-3.0 * RADIUS, offset + 3.0 * DIAMETER, 0); break;
    case 10: setPosition(0, offset + 4.0 * DIAMETER, 0); break;
    case 11: setPosition(RADIUS, offset + DIAMETER, 0); break;
    case 12: setPosition(-4.0 * RADIUS, offset + 4.0 * DIAMETER, 0); break;
    case 13: setPosition(3.0 * RADIUS, offset + 3.0 * DIAMETER, 0); break;
    case 14: setPosition(-2.0 * RADIUS, offset + 2.0 * DIAMETER, 0); break;
    case 15: setPosition(RADIUS, offset + 3.0 * DIAMETER, 0); break;
    }
}


/**
 * Draws this ball. The ball is translated and rotated before drawing.
**/
void Ball::draw(){
    glPushMatrix();
    glTranslated(position->getX(), position->getY(), position->getZ());
    glRotated(rotation->getX(), 1, 0, 0);
    glRotated(rotation->getY(), 0, 1, 0);
    glRotated(rotation->getZ(), 0, 0, 1);
    model->draw();
    glPopMatrix();
}


/**
 * Getters/Setters.
**/
double Ball::getRadius(){ return RADIUS; }
double Ball::getDiameter(){ return DIAMETER; }
double Ball::getMass(){ return MASS; }


/**
 * Destructor.
**/
Ball::~Ball(void){
    delete model;
}
