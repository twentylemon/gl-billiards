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
**/
Player::Player(int player){
	playerNumber = player;
	cue = Cue(playerNumber);
	ballType = BALL_TYPE_NONE;
}


/**
 * Getters/Setters
**/
int Player::getPlayerNumber(){ return playerNumber; }
int Player::getBallType(){ return ballType; }
void Player::setBallType(int ballType) { this->ballType = ballType; }
Cue Player::getCue(){ return cue; }
Vector Player::getCuePosition(){ return cue.getPosition(); }
void Player::setCuePosition(Vector position){ cue.setPosition(position); }
void Player::addCuePosition(Vector position){ cue.addPosition(position); }
void Player::setCueRotation(Vector rotation){ cue.setRotation(rotation); }
void Player::addCueRotation(Vector rotation){ cue.addRotation(rotation); }


/**
 * @param ballType the type of ball
 * @return true if hitting ballType first would be a foul
**/
bool Player::isFoul(int ballType){
    if (this->ballType != BALL_TYPE_NONE && ballType != BALL_TYPE_BLACK){
        return this->ballType != ballType;
    }
    return ballType == BALL_TYPE_CUE;
}


/**
 * Draws this player's cue
**/
void Player::drawCue(){
	cue.draw();
}


/**
 * Destructor
**/
Player::~Player(){
}
