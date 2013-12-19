/**
 * Implementation of Player
 *
 * @author Dan Lapp
 * @since 12-19-2013
 */

#include "Player.h"

/**
 * Default constructor
 *
 * @param player the player number
 */
Player::Player(int player){

	playerNumber = player;
	cue = new Cue(playerNumber);
	ballType = 0;
}


/**
 * Destructor
 */
Player::~Player(){
	delete cue;
}

/**
 * Returns the player number
 */
int Player::getPlayerNumber(){
	return playerNumber;
}


/**
 * Returns the type of ball this player has to sink.
 * @see Ball.h for ball type constants
 */
int Player::getBallType(){
	return ballType;
}


/**
 * Returns the Cue object for this player
 */
Cue* Player::getCue(){
	return cue;
}

