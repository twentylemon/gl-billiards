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
Cue::Cue(int playerNumber) : Particle() {

	/*
	Commented out until theres a model
	
	if(playerNumber == 1)
		model = new Model("Objects/cue.3DS", "Objects/textures/cuePlayer1.bmp");
	else
		model = new Model("Objects/cue.3DS", "Objects/textures/cuePlayer2.bmp");*/
}


/**
 * Destructor
 */
Cue::~Cue(){
	delete model;
}