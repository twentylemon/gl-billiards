/**
 * Implementation of Vector class.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-10
**/
#include "Vector.h"

/**
 * Default constructor. Sets everything to 0.
**/
Vector::Vector(void){
    set(0, 0, 0);
}


/**
 * Initializing constructor.
**/
Vector::Vector(double* data){
    set(data);
}


/**
 * Another initializing constructor.
**/
Vector::Vector(double x, double y, double z){
    set(x, y, z);
}


/**
 * Yet another initializing constructor. Copies the other Vector.
**/
Vector::Vector(Vector* other){
    set(other->data());
}


/**
 * Adds the other Vector to this one. This Vector becomes the
 * result of this + other.
 *
 * @param other the Vector to add to this one
**/
void Vector::add(Vector other){
    set(vec[X] + other.getX(), vec[Y] + other.getY(), vec[Z] + other.getZ());
}


/**
 * Adds a value to one of the fields of this Vector.
 *
 * @param idx the field to add a value to
 * @param value how much to add to the field
**/
void Vector::add(int idx, double value){
    set(idx, vec[X] + value);
}


/**
 * Adds values to this Vector.
 *
 * @param x the value to add to the X field
 * @param y the value to add to the Y field
 * @param z the value to add to the Z field
**/
void Vector::add(double x, double y, double z){
    set(vec[X] + x, vec[Y] + y, vec[Z] + z);
}


/**
 * Subtracts the other Vector from this one. This Vector becomes the
 * result of this - other.
 *
 * @param other the Vector to subtract this one
**/
void Vector::subtract(Vector other){
    set(vec[X] - other.getX(), vec[Y] - other.getY(), vec[Z] - other.getZ());
}


/**
 * Multiplies each element of this Vector by the value given.
 *
 * @param value the value to multiply each element of this Vector by
**/
void Vector::scale(double value){
    set(vec[X] * value, vec[Y] * value, vec[Z] * value);
}


/**
 * Compares this Vector to another. If they are sufficiently close to each other,
 * then they are considered equal and this will return true.
 *
 * @param other the other Vector to compare against
 * @return true if this and other are very close to each other
**/
bool Vector::equals(Vector other){
    return distance(other) < VECTOR_DISTANCE_EQUALS;
}


/**
 * Returns the length of this Vector.
 *
 * @return the length of the Vector
**/
double Vector::length(){
    return sqrt(lengthSq());
}


/**
 * Returns the squared length of this Vector.
 *
 * @return the squared length of this Vector
**/
double Vector::lengthSq(){
    return vec[X]*vec[X] + vec[Y]*vec[Y] + vec[Z]+vec[Z];
}


/**
 * Normalizes this Vector to a length of 1.
**/
void Vector::normalize(){
    normalize(1.0);
}


/**
 * Normalizes this Vector to the length specified.
 *
 * @param length the length to make this Vector
**/
void Vector::normalize(double length){
    double l = this->length();
    if (l > 0){
        scale(pow(length, 1.0/2.0) / l);
    }
}


/**
 * Returns the distance squared between this and another Vector.
 *
 * @param other the other Vector to get the distance from
 * @return the squared euclidean distance
**/
double Vector::distance(Vector other){
    double x = vec[X] - other.getX();
    double y = vec[Y] - other.getY();
    double z = vec[Z] - other.getZ();
    return x*x + y*y + z*z;
}


/**
 * Returns the distance squared between this and another Vector.
 *
 * @param (x,y,z) the point to get the distance to
 * @return the squared euclidean distance
**/
double Vector::distance(double x, double y, double z){
    return distance(Vector(x, y, z));
}


/**
 * Calculates the dot product between this Vector and another.
 *
 * @param other the other Vector
 * @return the dot product between the two Vector's
**/
double Vector::dotProduct(Vector other){
    return vec[X] * other.getX() + vec[Y] * other.getY() + vec[Z] * other.getZ();
}


/**
 * Calculates the cross product between the two Vector's.
 *
 * @param other the other Vector
 * @return the cross product between the two Vector's
**/
Vector Vector::crossProduct(Vector other){
    double x = vec[Y] * other.getZ() - vec[Z] * other.getY();
    double y = vec[Z] * other.getX() - vec[X] * other.getZ();
    double z = vec[X] * other.getY() - vec[Y] * other.getX();
    return Vector(x, y, z);
}


/**
 * Getters/Setters.
**/
double Vector::get(int idx){ return vec[idx]; }
double Vector::getX(){ return vec[X]; }
double Vector::getY(){ return vec[Y]; }
double Vector::getZ(){ return vec[Z]; }
void Vector::set(int idx, double val){ vec[idx] = val; }
void Vector::set(double* data){ set(data[X], data[Y], data[Z]); }
void Vector::set(double x, double y, double z){ vec[X] = x; vec[Y] = y; vec[Z] = z; }
void Vector::setX(double x){ vec[X] = x; }
void Vector::setY(double y){ vec[Y] = y; }
void Vector::setZ(double z){ vec[Z] = z; }
double* Vector::data(){ return vec.data(); }


/**
 * Returns a string representation of this Vector.
 *
 * @return a string "(x, y, z)"
**/
std::string Vector::toString(){
    return "(" + std::to_string(vec[X]) + ", " + std::to_string(vec[Y]) + ", " + std::to_string(vec[Z]) + ")";
}


/**
 * Adds the two Vector's together.
 *
 * @param first one of the Vector's
 * @param second the other Vector
 * @return the result of first + second
**/
Vector Vector::add(Vector first, Vector second){
    return Vector(first.getX() + second.getX(), first.getY() + second.getY(), first.getZ() + second.getZ());
}


/**
 * Adds the two Vector's together.
 *
 * @param first one of the Vector's
 * @param x the value to add to the X field
 * @param y the value to add to the Y field
 * @param z the value to add to the Z field
 * @return the result of first + (x,y,z)
**/
Vector Vector::add(Vector first, double x, double y, double z){
    return Vector(first.getX() + x, first.getY() + y, first.getZ() + z);
}


/**
 * Subtracts the two Vector's
 *
 * @param first one of the Vector's
 * @param second the other Vector
 * @return the result of first - second
**/
Vector Vector::subtract(Vector first, Vector second){
    return Vector(first.getX() - second.getX(), first.getY() - second.getY(), first.getZ() - second.getZ());
}


/**
 * Multiplies the Vector by the scale and returns the new result.
 *
 * @param first the Vector to scale
 * @param scale the value to multiply by
 * @return the result of value * first
**/
Vector Vector::scale(Vector first, double value){
    return new Vector(first.getX() * value, first.getY() * value, first.getZ() * value);
}


/**
 * Returns this squared distance between the two Vector's
 *
 * @param first one Vector
 * @param second the other Vector
 * @return the squared euclidean distance between first and second
**/
double Vector::distance(Vector first, Vector second){
    return first.distance(second);
}


/**
 * Calculates the dot product between this Vector and another.
 *
 * @param first one Vector
 * @param second the other Vector
 * @return the dot product between the two Vector's
**/
double Vector::dotProduct(Vector first, Vector second){
    return first.getX() * second.getX() + first.getY() * second.getY() + first.getZ() * second.getZ();
}


/**
 * Calculates the cross product between the two Vector's.
 *
 * @param first one Vector
 * @param second the other Vector
 * @return the cross product between the two Vector's
**/
Vector Vector::crossProduct(Vector first, Vector second){
    double x = first.getY() * second.getZ() - first.getZ() * second.getY();
    double y = first.getZ() * second.getX() - first.getX() * second.getZ();
    double z = first.getX() * second.getY() - first.getY() * second.getX();
    return Vector(x, y, z);
}


/**
 * Projects first onto second and returns the resultant Vector.
 *
 * @param first the Vector to project from
 * @param second the Vector to project onto
 * @return first projected onto second
**/
Vector Vector::project(Vector first, Vector second){
    double length = second.lengthSq();
    if (length > 0){
        return Vector::scale(second, dotProduct(first, second) / length);
    }
    return first;
}


/**
 * Destructor. Nothing to destroy. std::array is destroyed automatically.
**/
Vector::~Vector(void){
}
