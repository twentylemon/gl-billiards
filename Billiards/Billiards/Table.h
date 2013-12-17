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

class Table
{
public:
    Table(void);
    ~Table(void);

    void draw();

private:
    Model* bed;
    Model* edges;
};

