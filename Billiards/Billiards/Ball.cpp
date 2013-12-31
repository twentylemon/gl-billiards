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
    this->number = number;
    setPosition(getStartPosition());

    //initialize a random rotation
    for (int i = 0; i < 16; i++){
        rotMatrix[i] = (i % 5 == 0) ? 1 : 0;    //makes 4x4 identity matrix
    }
    pushRotation(Vector(rand(), rand(), rand()), rand() % 360);
    consolidateRotation();
}


/**
 * Draws this ball. The ball is translated and rotated before drawing.
**/
void Ball::draw(){
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glTranslated(position.getX(), position.getY(), position.getZ());
    doRotate();
    model.draw();
    glPopMatrix();
}


/**
 * Pushes a new rotation into the list of rotations.
 *
 * @param axis the axis through which the rotation occurs
 * @param angle how much to rotate
**/
void Ball::pushRotation(Vector axis, double angle){
    if (rotList.size() > 0 && rotList.front().first.equals(axis)){
        rotList.front().second += angle;
    }
    else {
        rotList.push_front(std::make_pair(axis, angle));
    }
}


/**
 * Clears the rotation list and updates the rotation matrix.
 * We have a list of all the rotations this ball underwent this frame, and we
 * also have the rotation history from { @code rotMatrix }. What this does
 * is combine the list of new rotations with the rotation history.
**/
void Ball::consolidateRotation(){
    if (rotList.size() > 0){
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        doRotate();
        //copy the rotation matrix into our system
        glGetDoublev(GL_MODELVIEW_MATRIX, rotMatrix);
        rotList.clear();    //and finally, clear the list
        glPopMatrix();
    }
}


/**
 * Rotates the ball. Uses the list of all rotations to perform, then
 * adds on all the previous rotations the ball underwent. Context-sensitivity, ho!
**/
void Ball::doRotate(){
    //starting from the most recent rotation, rotate the ball
    for (unsigned int i = 0; i < rotList.size(); i++){
        glRotated(rotList[i].second, rotList[i].first.getX(), rotList[i].first.getY(), rotList[i].first.getY());
    }
    glMultMatrixd(rotMatrix);   //add in the previous rotations
}


/**
 * Sinks this ball into a pocket.
**/
void Ball::sink(){
    addPosition(Vector(0, 0, -8.0 * 0.0254));
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
int Ball::getNumber(){ return number; }
int Ball::getType(){
    switch (number){
    case 0: return BALL_TYPE_CUE;
    case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        return BALL_TYPE_SOLID;
    case 8: return BALL_TYPE_BLACK;
    case 9: case 10: case 11: case 12: case 13: case 14: case 15:
        return BALL_TYPE_STRIPE;
    }
    return BALL_TYPE_NONE;
}


/**
 * @return the starting position of this ball
**/
Vector Ball::getStartPosition(){
    double offset = 1.0/4.0 * TABLE_WIDTH;
    double o = 0.01 * RADIUS;   //leave tiny bit of extra space
    double radius = RADIUS + o;
    double diameter = DIAMETER + 2.0*o;
    switch (number){
    case 0: return Vector(-1.4/5.0 * TABLE_WIDTH, 0, 0);
    case 1: return Vector(offset, 0, 0);
    case 2: return Vector(offset + 4.0 * diameter, 2.0 * radius, 0);
    case 3: return Vector(offset + diameter, -radius, 0);
    case 4: return Vector(offset + 3.0 * diameter, -radius, 0);
    case 5: return Vector(offset + 4.0 * diameter, -2.0 * radius, 0);
    case 6: return Vector(offset + 2.0 * diameter, 2.0 * radius, 0);
    case 7: return Vector(offset + 4.0 * diameter, 4.0 * radius, 0);
    case 8: return Vector(offset + 2.0 * diameter, 0, 0);
    case 9: return Vector(offset + 3.0 * diameter, -3.0 * radius, 0);
    case 10: return Vector(offset + 4.0 * diameter, 0, 0);
    case 11: return Vector(offset + diameter, radius, 0);
    case 12: return Vector(offset + 4.0 * diameter, -4.0 * radius, 0);
    case 13: return Vector(offset + 3.0 * diameter, 3.0 * radius, 0);
    case 14: return Vector(offset + 2.0 * diameter, -2.0 * radius, 0);
    case 15: return Vector(offset + 3.0 * diameter, radius, 0);
    }
    return Vector();
}


/**
 * Bookkeeping copy. Used for keeping the previous state of a ball, so only the key
 * attributes are copied, like number, position and pocketed state.
 *
 * @param other the ball to deep copy
**/
void Ball::copy(Ball* ball){
    number = ball->getNumber();
    position = ball->getPosition();
    sunk = ball->isSunk();
}


/**
 * Destructor.
**/
Ball::~Ball(void){
}
