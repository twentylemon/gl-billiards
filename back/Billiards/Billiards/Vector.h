/**
 * Defines a point or vector in 3D space.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-10
**/
#pragma once
#include <new>
#include <array>
#include <string>
#define VECTOR_DISTANCE_EQUALS 0.1

class Vector {
public:
    Vector(void);
    Vector(double, double, double);
    Vector(double*);
    Vector(Vector*);
    ~Vector(void);

    static const int X = 0;
    static const int Y = 1;
    static const int Z = 2;

    //operations
    void add(Vector);
    void add(int, double);
    void add(double, double, double);
    void subtract(Vector);
    void scale(double);
    double distance(Vector);
    double distance(double, double, double);
    bool equals(Vector);
    double dotProduct(Vector);
    Vector crossProduct(Vector);

    static Vector add(Vector, Vector);
    static Vector add(Vector, double, double, double);
    static Vector subtract(Vector, Vector);
    static Vector scale(Vector, double);
    static double distance(Vector, Vector);
    static double dotProduct(Vector, Vector);
    static Vector crossProduct(Vector, Vector);
    static Vector normalize(Vector);
    static Vector project(Vector, Vector);

    double length();
    double lengthSq();
    void normalize();
    void normalize(double);

    //getters/setters
    double get(int);         //get single element
    double getX();
    double getY();
    double getZ();
    void set(int, double);   //set single element
    void set(double*);       //set all data
    void set(double, double, double);
    void setX(double);
    void setY(double);
    void setZ(double);
    double* data();

    std::string toString();

protected:
    std::array<double, 3> vec;
};
