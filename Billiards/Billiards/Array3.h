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
#define ARRAY3_DISTANCE_EQUALS 0.1

class Array3 {
public:
    Array3(void);
    Array3(double, double, double);
    Array3(double*);
    ~Array3(void);

    static const int X = 0;
    static const int Y = 1;
    static const int Z = 2;

    //operations
    void add(Array3*);
    void add(int, double);
    void add(double, double, double);
    void subtract(Array3*);
    void multiply(double);
    void divide(double);
    double distance(Array3*);
    bool equals(Array3*);
    double dotProduct(Array3*);
    Array3* crossProduct(Array3*);

    static Array3* add(Array3*, Array3*);
    static Array3* subtract(Array3*, Array3*);
    static double distance(Array3*, Array3*);
    static double dotProduct(Array3*, Array3*);
    static Array3* crossProduct(Array3*, Array3*);

    double length();
    double lengthSq();
    void normalize();
    void normalize(double);

    //getters/setters
    double* get();           //pointer to data
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
