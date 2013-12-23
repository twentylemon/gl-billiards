

#include "UserInterface.h"

float cueRotationMatrix[16] =  {1, 0, 0, 0,
								0, 1, 0, 0, 
								0, 0, 1, 0,
								0, 0, 0, 1};

UserInterface::UserInterface(int mainWindowHandle){

	this->mainWindowHandle = mainWindowHandle;


};

void UserInterface::startWindow(){

	glui->set_main_gfx_window(mainWindowHandle);
}