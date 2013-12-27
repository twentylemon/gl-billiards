


#include "GL\glui.h"

#define ESC 27

class UserInterface{

public:
	int mainWindowHandle;
	float cueRotationMatrix[16];

	UserInterface(int glutMainWindow);
	void startWindow();

protected:
	GLUI* glui;
	GLUI_Panel* uiPanel;

	GLUI_Rotation* cueRotation;

};


