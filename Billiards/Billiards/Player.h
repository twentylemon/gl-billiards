/**
 * Datatype representing a player of the game.
 * Each player has their own cue and a ball type
 *
 * @author Dan Lapp
 * @since 12-19-2013
 */
#pragma once
#include "Cue.h"

class Player
{
public:
    Player(void){}
	Player(int player);
	~Player();

	int getPlayerNumber();
	int getBallType();
    Cue getCue();
    Vector getCuePosition();
    void setCuePosition(Vector);
    void addCuePosition(Vector);
    void setCueRotation(Vector);
    void addCueRotation(Vector);

	void drawCue();

protected:
	int playerNumber;
	int ballType;
	Cue cue;
};
