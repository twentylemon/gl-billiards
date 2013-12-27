/**
 * Cue.h
 * Represents a pool cue.
 *
 * @author Taras Myckaskiw
 * @version 1.0
 * @since 2013-12-16
**/
#pragma once
#include <new>
#include <string>
#include "Particle.h"
#include "Model.h"

class Cue : public Particle
{
public:
    Cue(void){}
    Cue(int playerNumber);
    ~Cue(void);

    void draw();
};
