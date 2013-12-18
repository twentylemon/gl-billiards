/**
 * Table.cpp
 * Represents the billiards table.
 *
 * @author Taras Myckaskiw
 * @version 1.0
 * @since 2013-12-17
**/
#include "Table.h"

/**
 * Constructor. Loads the models for the pool table.
**/
Table::Table(void) : FRICTION(TABLE_FRICTION){
    bed = new Model("Objects/table_bed.3DS", "Objects/textures/felt.bmp");
    edges = new Model("Objects/table_edges.3DS", "Objects/textures/crate.bmp");
}


/**
 * Draws the table.
**/
void Table::draw(){
    bed->draw();
    edges->draw();
}


/**
 * Destructor.
**/
Table::~Table(void){
    delete bed;
    delete edges;
}
