/**
 * Ball.cpp
 * Implementation for a pool cue.
 *
 * @author Taras Myckaskiw
 * @version 1.0
 * @since 2013-12-16
**/
#include "Cue.h"

/**
 * Default constructor.
**/
Cue::Cue(int playerNumber) : Particle(){
	if (playerNumber == 1){
		model = Model("Objects/cue.3DS", "Objects/textures/cue1.bmp");
    }
	else {
		model = Model("Objects/cue.3DS", "Objects/textures/cue1.bmp");
    }
    rotation.setZ(180);
}


/**
 * Destructor. Nothing to detroy.
**/
Cue::~Cue(){
}


/**
 * Draws the cue on the screen.
**/
void Cue::draw(){
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
	glTranslated(position.getX(), position.getY(), position.getZ());
    glRotated(rotation.getZ(), 0, 0, 1);
	model.draw();
    glPopMatrix();
}
