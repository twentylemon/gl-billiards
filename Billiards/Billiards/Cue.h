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
#include "GL/glut.h"

class Cue : public Particle{
	public:
    Cue();
    ~Cue(void);

    void draw();

};