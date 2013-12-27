/**
 * Cushion.h
 * Represents a surface to bank off of.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-27
**/
#include "Cushion.h"

/**
 * Constructor.
 *
 * @param start where this cushion starts
 * @param finish where this cushion ends
**/
Cushion::Cushion(Vector start, Vector finish){
    this->start = start;
    this->finish = finish;
    line = Vector::subtract(finish, start);
    normal = Vector::normalize(line.crossProduct(Vector(0, 0, 1)));
    negRadius = Vector::scale(normal, -1.0);
}


/**
 * Getters/Setters
**/
void Cushion::setRadius(double ballRadius){ negRadius.normalize(ballRadius); }
Vector Cushion::getStart(){ return start; }
Vector Cushion::getFinish(){ return finish; }
Vector Cushion::getLine(){ return line; }
Vector Cushion::getNormal(){ return normal; }
Vector Cushion::getNegRadius(){ return negRadius; }


/**
 * Destructor.
**/
Cushion::~Cushion(void){
}
