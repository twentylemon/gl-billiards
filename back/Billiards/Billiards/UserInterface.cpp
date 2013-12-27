

#include "UserInterface.h"

float cueRotationMatrix[16] =  {1, 0, 0, 0,
								0, 1, 0, 0, 
								0, 0, 1, 0,
								0, 0, 0, 1};

UserInterface::UserInterface(int mainWindowHandle){

	this->mainWindowHandle = mainWindowHandle;

	glui = GLUI_Master.create_glui_subwindow(mainWindowHandle, GLUI_SUBWINDOW_RIGHT);
	uiPanel = new GLUI_Rollout(glui, "Billiards");

	new GLUI_Rotation(glui, "Cue", cueRotationMatrix);

};

void UserInterface::startWindow(){

	glui->set_main_gfx_window(mainWindowHandle);
}