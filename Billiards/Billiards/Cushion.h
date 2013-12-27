/**
 * Cushion.h
 * Represents a surface to bank off of.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-27
**/
#pragma once
#include "Vector.h"

class Cushion
{
public:
    Cushion(void){}
    Cushion(Vector, Vector);
    ~Cushion(void);

    void setRadius(double);
    Vector getStart();
    Vector getFinish();
    Vector getLine();
    Vector getNormal();
    Vector getNegRadius();
    double getLength();
    double getLengthSq();

private:
    Vector start;
    Vector finish;
    Vector line;
    Vector normal;
    Vector negRadius;
    double length, lengthSq;
};
