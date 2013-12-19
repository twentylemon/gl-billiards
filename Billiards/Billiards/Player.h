/**
 * Datatype representing a player of the game.
 * Each player has their own cue and a ball type
 *
 * @author Dan Lapp
 * @since 12-19-2013
 */

#include "Cue.h"

class Player{

public:
	Player(int player);
	~Player();

	int getPlayerNumber();
	int getBallType();
	Cue* getCue();
	void drawCue();

protected:
	int playerNumber;
	int ballType;
	Cue* cue;

};