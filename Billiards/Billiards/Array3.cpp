/**
 * Implementation of Array3 class.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-10
**/
#include "Array3.h"

/**
 * Default constructor. Sets everything to 0.
**/
Array3::Array3(void){
    set(0, 0, 0);
}


/**
 * Initializing constructor.
**/
Array3::Array3(double* data){
    set(data);
}


/**
 * Another initializing constructor.
**/
Array3::Array3(double x, double y, double z){
    set(x, y, z);
}


/**
 * Yet another initializing constructor. Copies the other Array3.
**/
Array3::Array3(Array3* other){
    set(other->data());
}


/**
 * Adds the other Array3 to this one. This Array3 becomes the
 * result of this + other.
 *
 * @param other the Array3 to add to this one
**/
void Array3::add(Array3* other){
    set(vec[X] + other->getX(), vec[Y] + other->getY(), vec[Z] + other->getZ());
}


/**
 * Adds a value to one of the fields of this Array3.
 *
 * @param idx the field to add a value to
 * @param value how much to add to the field
**/
void Array3::add(int idx, double value){
    set(idx, vec[X] + value);
}


/**
 * Adds values to this Array3.
 *
 * @param x the value to add to the X field
 * @param y the value to add to the Y field
 * @param z the value to add to the Z field
**/
void Array3::add(double x, double y, double z){
    set(vec[X] + x, vec[Y] + y, vec[Z] + z);
}


/**
 * Subtracts the other Array3 from this one. This Array3 becomes the
 * result of this - other.
 *
 * @param other the Array3 to subtract this one
**/
void Array3::subtract(Array3* other){
    set(vec[X] - other->getX(), vec[Y] - other->getY(), vec[Z] - other->getZ());
}


/**
 * Multiplies each element of this Array3 by the value given.
 *
 * @param scale the value to multiply each element of this Array3 by
**/
void Array3::multiply(double scale){
    set(vec[X] * scale, vec[Y] * scale, vec[Z] * scale);
}


/**
 * Divides each element of this Array3 by the value given.
 *
 * @param scale the value to divide each element of this Array3 by
**/
void Array3::divide(double scale){
    set(vec[X] / scale, vec[Y] / scale, vec[Z] / scale);
}


/**
 * Compares this Array3 to another. If they are sufficiently close to each other,
 * then they are considered equal and this will return true.
 *
 * @param other the other Array3 to compare against
 * @return true if this and other are very close to each other
**/
bool Array3::equals(Array3* other){
    return distance(other) < ARRAY3_DISTANCE_EQUALS;
}


/**
 * Returns the length of this Array3.
 *
 * @return the length of the Array3
**/
double Array3::length(){
    return sqrt(lengthSq());
}


/**
 * Returns the squared length of this Array3.
 *
 * @return the squared length of this Array3
**/
double Array3::lengthSq(){
    return vec[X]*vec[X] + vec[Y]*vec[Y] + vec[Z]+vec[Z];
}


/**
 * Normalizes this Array3 to a length of 1.
**/
void Array3::normalize(){
    normalize(1.0);
}


/**
 * Normalizes this Array3 to the length specified.
 *
 * @param length the length to make this Array3
**/
void Array3::normalize(double length){
    double l = this->length();
    if (l > 0){
        divide(sqrt(l));
        multiply(pow(length, 1.0/2.0));
    }
}


/**
 * Returns the distance squared between this and another Array3.
 *
 * @param other the other Array3 to get the distance from
 * @return the squared euclidean distance
**/
double Array3::distance(Array3* other){
    return distance(this, other);
}


/**
 * Calculates the dot product between this Array3 and another.
 *
 * @param other the other Array3
 * @return the dot product between the two Array3's
**/
double Array3::dotProduct(Array3* other){
    return vec[X] * other->getX() + vec[Y] * other->getY() + vec[Z] * other->getZ();
}


/**
 * Calculates the cross product between the two Array3's.
 *
 * @param other the other Array3
 * @return the cross product between the two Array3's
**/
Array3* Array3::crossProduct(Array3* other){
    double x = vec[Y] * other->getZ() - vec[Z] * other->getY();
    double y = vec[Z] * other->getX() - vec[X] * other->getZ();
    double z = vec[X] * other->getY() - vec[Y] * other->getX();
    return new Array3(x, y, z);
}


/**
 * Getters/Setters.
**/
double Array3::get(int idx){ return vec[idx]; }
double* Array3::get(){ return vec.data(); }
double Array3::getX(){ return vec[X]; }
double Array3::getY(){ return vec[Y]; }
double Array3::getZ(){ return vec[Z]; }
void Array3::set(int idx, double val){ vec[idx] = val; }
void Array3::set(double* data){ set(data[X], data[Y], data[Z]); }
void Array3::set(double x, double y, double z){ vec[X] = x; vec[Y] = y; vec[Z] = z; }
void Array3::setX(double x){ vec[X] = x; }
void Array3::setY(double y){ vec[Y] = y; }
void Array3::setZ(double z){ vec[Z] = z; }
double* Array3::data(){ return vec.data(); }


/**
 * Returns a string representation of this Array3.
 *
 * @return a string "(x, y, z)"
**/
std::string Array3::toString(){
    return "(" + std::to_string(vec[X]) + ", " + std::to_string(vec[Y]) + ", " + std::to_string(vec[Z]) + ")";
}


/**
 * Adds the two Array3's together.
 *
 * @param first one of the Array3's
 * @param second the other Array3
 * @return the result of first + second
**/
Array3* Array3::add(Array3* first, Array3* second){
    return new Array3(first->getX() + second->getX(), first->getY() + second->getY(), first->getZ() + second->getZ());
}


/**
 * Subtracts the two Array3's
 *
 * @param first one of the Array3's
 * @param second the other Array3
 * @return the result of first - second
**/
Array3* Array3::subtract(Array3* first, Array3* second){
    return new Array3(first->getX() - second->getX(), first->getY() - second->getY(), first->getZ() - second->getZ());
}


/**
 * Returns this squared distance between the two Array3's
 *
 * @param first one Array3
 * @param second the other Array3
 * @return the squared euclidean distance between first and second
**/
double Array3::distance(Array3* first, Array3* second){
    double x = first->getX() - second->getX();
    double y = first->getY() - second->getY();
    double z = first->getZ() - second->getZ();
    return x*x + y*y + z*z;
}


/**
 * Calculates the dot product between this Array3 and another.
 *
 * @param first one Array3
 * @param second the other Array3
 * @return the dot product between the two Array3's
**/
double Array3::dotProduct(Array3* first, Array3* second){
    return first->getX() * second->getX() + first->getY() * second->getY() + first->getZ() * second->getZ();
}


/**
 * Calculates the cross product between the two Array3's.
 *
 * @param first one Array3
 * @param second the other Array3
 * @return the cross product between the two Array3's
**/
Array3* Array3::crossProduct(Array3* first, Array3* second){
    double x = first->getY() * second->getZ() - first->getZ() * second->getY();
    double y = first->getZ() * second->getX() - first->getX() * second->getZ();
    double z = first->getX() * second->getY() - first->getY() * second->getX();
    return new Array3(x, y, z);
}


/**
 * Destructor. Nothing to destroy. std::array is destroyed automatically.
**/
Array3::~Array3(void){
}
