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
Table::Table(void){
    bed = Model("Objects/table_bed.3DS", "Objects/textures/tabletop.bmp");
    edges = Model("Objects/table_edges.3DS", "Objects/textures/tablesides.bmp");
	rails = Model("Objects/table_rails.3DS", "Objects/textures/felt.bmp");
    zoom = 0;
    rotation = Vector(0, 0, 180);
}


/**
 * Draws the table.
 *
 * @param cameraRotationMatrix specifies the position of the camera
 *		around the table
 * @param cameraCenter the camera rotates about this location in the
 *		world. Usually set to rotate about cueball
**/
void Table::draw(float rotationY, float rotationZ, Vector cameraCenter){
	if (zoom > ZOOM_MIN){
		glTranslatef(zoom, 0, ZOOM_MIN);
    }
	else {
		glTranslatef(zoom, 0, zoom);
    }
	
	glRotatef(180, 0, 0, 1);
	glRotatef(rotationY, 0, 1, 0);
	glRotatef(rotationZ, 0, 0, 1);

	//glMultMatrixf(cameraRotationMatrix);

	glTranslated(cameraCenter.getX(), cameraCenter.getY(), -0.45);
	
    bed.draw();
    edges.draw();
	rails.draw();
}


/**
 * Getters/Setters.
**/
double Table::getZoom(){ return zoom; }
double Table::getRotation(int idx){ return rotation.get(idx); }
Vector Table::getRotation(){ return rotation; }
void Table::setZoom(double zoom){ this->zoom = zoom; }
void Table::setRotation(int idx, double val){ rotation.set(idx, val); }
void Table::setRotation(Vector rot){ rotation = rot; }
void Table::addZoom(double diff){ zoom += diff; }
