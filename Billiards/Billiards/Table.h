/**
 * Table.h
 * Represents the billiards table.
 *
 * @author Taras Myckaskiw
 * @version 1.0
 * @since 2013-12-17
**/
#pragma once
#include "Model.h"
#define ZOOM_MIN 0.7

class Table
{
public:
    Table(void);

    void draw();

    double getZoom();
    double getRotation(int);
    Vector getRotation();
    void setZoom(double);
    void setRotation(int, double);
    void setRotation(Vector);
    void addZoom(double);

private:
    Model bed;
    Model edges;
	Model rails;
    Vector rotation;
    double zoom;
};
