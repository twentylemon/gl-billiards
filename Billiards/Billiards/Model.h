/**
 * 3D imported model, loaded from disk
 *
 * @author Dan Lapp
 * @version 1.0
 * @since 2013-12-10
**/

#pragma once
#include "ModelLoader.h"

class Model{

	obj_type model;

public:
	void loadObject(char* model, char* texture);
	obj_type* getModel();

};