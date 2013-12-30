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
#define ZOOM_MIN 1.0

class Table
{
public:
    Table(void);

    void draw(Vector, Vector);

    double getZoom();
    void setZoom(double);
    void addZoom(double);

private:
    Model bed;
    Model edges;
	Model rails;
    double zoom;
};
