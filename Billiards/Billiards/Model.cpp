/**
 * 3D imported model, loaded from disk
 *
 * @author Dan Lapp
 * @version 1.0
 * @since 2013-12-10
**/


#include "ModelLoader.h"
#include "Model.h"

obj_type model;

void Model::loadObject(char* modelPath, char* texture)
{
	Load3DS (&model, modelPath);
	model.id_texture = LoadTextureBitmap(texture); 
    
}

obj_type* Model::getModel()
{
	return &model;
}