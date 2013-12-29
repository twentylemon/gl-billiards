/**
 * Defines behaviour for the glui user interface. Inflates
 * the UI and sets/defines callbacks
 *
 * @author Dan Lapp
 * @since 2013-12-27
**/
#include "UserInterface.h"

/**
 * Callback method for Zoom In button.
**/
void zoomIn(){
	global.tableZoom += ZOOM_STEP;
}


/**
 * Callback method for Zoom Out button.
**/
void zoomOut(){
	global.tableZoom -= ZOOM_STEP;
}


/**
 * Callback method for Reset Zoom button.
**/
void resetZoom(){
	global.tableZoom = 0;
}


/**
 * Updates the text field to show info for whoever is shooting.
**/
void updatePlayerTextField(){
	std::string text = "Player ";
	
	if (global.turn == 0){
		text.append("1: ");
    }
	else {
		text.append("2: ");
    }

	switch (global.players[global.turn].getBallType()){
	case BALL_TYPE_NONE:
		text.append("Open");
		break;
	case BALL_TYPE_SOLID:
		text.append("Solid");
		break;
    case BALL_TYPE_STRIPE:
		text.append("Striped");
		break;
	}
	
	global.playerTextField->set_text(text.data());
}


/**
 * Initializes the GLUI subwindow and inflates it
 * with controls. Also sets callbacks.
**/
void initializeGlui(){
	global.objectType = 1;

	//create glui window and add a rollout panel for controls
	global.glui = GLUI_Master.create_glui_subwindow(global.glutWindow, GLUI_SUBWINDOW_RIGHT);

	global.playerTextField = new GLUI_StaticText(global.glui, "Player 1: Open");
	global.cuePanel = new GLUI_Rollout(global.glui, "Cue");
	global.cameraPanel = new GLUI_Rollout(global.glui, "Camera");

	//rotation control for cue
	GLUI_Panel* cueRotatePanel = global.glui->add_panel_to_panel(global.cuePanel, NULL);
	GLUI_Panel* cueShotPanel = global.glui->add_panel_to_panel(global.cuePanel, NULL);
	
    global.cueTranslate = new GLUI_Translation(cueRotatePanel, "Rotate Cue", GLUI_TRANSLATION_Z, (float*)0, -1, (GLUI_Update_CB)updateCue);
	global.cueTranslate->set_z(180);
	new GLUI_Button(cueShotPanel, "Shoot", 0, (GLUI_Update_CB)takeShot);

	global.shotPowerSpinner = new GLUI_Spinner(cueShotPanel, "Power", GLUI_SPINNER_FLOAT, -1, (GLUI_Update_CB)updateCue);
	global.shotPowerSpinner->set_float_limits(0.0, 1.0);

	//zoom buttons
	GLUI_Panel* zoomPanel = global.glui->add_panel_to_panel(global.cameraPanel, NULL);
	GLUI_Panel* resetZoomPanel = global.glui->add_panel_to_panel(global.cameraPanel, NULL);

	new GLUI_Button(zoomPanel, "Zoom In", 0, (GLUI_Update_CB) zoomIn);
	new GLUI_Button(zoomPanel, "Zoom Out", 0, (GLUI_Update_CB) zoomOut);
	new GLUI_Button(resetZoomPanel, "Reset Zoom", 0, (GLUI_Update_CB) resetZoom);

	//link main glut window with our control panel
	global.glui->set_main_gfx_window(global.glutWindow);
	
	//make sure GLUI knows about our idle function
	GLUI_Master.set_glutIdleFunc(idleFunc);
}
