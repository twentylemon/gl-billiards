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
    model = Model("Objects/cue.3DS", "Objects/textures/cue" + std::to_string(playerNumber) + ".bmp");
    rotation.setZ(180);
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


/**
 * Destructor. Nothing to detroy.
**/
Cue::~Cue(){
}
