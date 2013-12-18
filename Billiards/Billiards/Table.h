/**
 * Table.h
 * Represents the billiards table.
 *
 * @author Taras Myckaskiw
 * @version 1.0
 * @since 2013-12-17
**/
#pragma once
#include <new>
#include "Model.h"
#define TABLE_FRICTION 0.95

class Table
{
public:
    Table(void);
    ~Table(void);

    void draw();

    const double FRICTION;

private:
    Model* bed;
    Model* edges;
	Model* rails;
};

