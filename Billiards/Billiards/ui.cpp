/**
 * Defines behaviour for the glui user interface. Inflates
 * the UI and sets/defines callbacks
 *
 * @author Dan Lapp
 * @since 2013-12-27
**/
#include "ui.h"

/**
 * Callback method for Zoom In button.
**/
void zoomIn(){
    global.table.addZoom(ZOOM_STEP);
}


/**
 * Callback method for Zoom Out button.
**/
void zoomOut(){
    global.table.addZoom(-ZOOM_STEP);
}


/**
 * Callback method for Reset Zoom button.
**/
void resetZoom(){
    global.table.setZoom(0);
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
		text.append("Solids");
		break;
    case BALL_TYPE_STRIPE:
		text.append("Stripes");
		break;
	}
	
	global.playerTextField->set_text(text.data());
	if (!global.gameOver){
		global.shotInfoTextField->set_text("");
    }
}


/**
 * Glut callback to reset the camera to it's original rotation
**/
void resetCamera(){
    global.cameraTranslate->set_x(0);
    global.cameraTranslate->set_y(0);
    global.cameraTranslate->set_z(0);
}


/**
 * Updates the ui when a player wins the game.
**/
void playerWins(int player){
    player++;
	std::string str = "Player " + std::to_string(player) + " Wins";
	global.playerTextField->set_text("8 Ball Pocketed");
	global.shotInfoTextField->set_text(str.data());
	global.shootButton->set_name("Restart Game");
}


/**
 * Initializes the GLUI subwindow and inflates it
 * with controls. Also sets callbacks.
**/
void initializeGlui(){
	global.objectType = 1;

	//create glui window and add a rollout panel for controls
	global.glui = GLUI_Master.create_glui_subwindow(global.glutWindow, GLUI_SUBWINDOW_RIGHT);

	//player and turn info
	GLUI_Panel* playerInfoPanel = global.glui->add_panel(NULL);
	global.playerTextField = new GLUI_StaticText(playerInfoPanel, "Player 1: Open");
	global.shotInfoTextField = new GLUI_StaticText(playerInfoPanel, "");

	GLUI_Panel* cuePanel = new GLUI_Rollout(global.glui, "Cue");
	GLUI_Panel* cameraPanel = new GLUI_Rollout(global.glui, "Camera");

	//rotation control for cue
	GLUI_Panel* cueRotatePanel = global.glui->add_panel_to_panel(cuePanel, NULL);
	GLUI_Panel* cueShotPanel = global.glui->add_panel_to_panel(cuePanel, NULL);
	
    global.cueTranslate = new GLUI_Translation(cueRotatePanel, "Rotate Cue", GLUI_TRANSLATION_X, (float*)0, -1, (GLUI_Update_CB)updateCue);
	global.cueTranslate->set_z(180);
	global.shootButton = new GLUI_Button(cueShotPanel, "Shoot", 0, (GLUI_Update_CB)takeShot);

	global.shotPowerSpinner = new GLUI_Spinner(cueShotPanel, "Power", GLUI_SPINNER_FLOAT, -1, (GLUI_Update_CB)updateCue);
	global.shotPowerSpinner->set_float_limits(0.0, 1.0);

	//camera panel
	GLUI_Panel* cameraRotatePanel = global.glui->add_panel_to_panel(cameraPanel, NULL);
    GLUI_Panel* followPanel = global.glui->add_panel_to_panel(cameraPanel, "Follow a Ball");
	GLUI_Panel* zoomPanel = global.glui->add_panel_to_panel(cameraPanel, NULL);
	//GLUI_Panel* resetZoomPanel = global.glui->add_panel_to_panel(cameraPanel, NULL);

	global.cameraTranslate = new GLUI_Translation(cameraRotatePanel, "Rotate", GLUI_TRANSLATION_XY);
    global.cameraCenterType = new GLUI_RadioGroup(cameraRotatePanel, (int*)0, -1, (GLUI_Update_CB)updateCamera);
    //order of radio buttons matters! follow = 0, origin = 1
    new GLUI_RadioButton(global.cameraCenterType, "Follow Ball");
    new GLUI_RadioButton(global.cameraCenterType, "Center of Table");

    global.cameraFollowList = new GLUI_Listbox(followPanel, "Follow", &global.follow, -1, (GLUI_Update_CB)updateCamera);
    global.cameraFollowList->add_item(0, "Cue Ball");
    for (int i = 1; i < 16; i++){
        global.cameraFollowList->add_item(i, std::to_string(i).append(" Ball").data());
    }

	new GLUI_Button(cameraRotatePanel, "Reset Camera", 0, (GLUI_Update_CB)resetCamera);
	new GLUI_Button(zoomPanel, "Zoom In", 0, (GLUI_Update_CB)zoomIn);
	new GLUI_Button(zoomPanel, "Zoom Out", 0, (GLUI_Update_CB)zoomOut);
	//new GLUI_Button(resetZoomPanel, "Reset Zoom", 0, (GLUI_Update_CB)resetZoom);
	new GLUI_Button(zoomPanel, "Reset Zoom", 0, (GLUI_Update_CB)resetZoom);

	//link main glut window with our control panel
	global.glui->set_main_gfx_window(global.glutWindow);
	
	//make sure GLUI knows about our idle function
	GLUI_Master.set_glutIdleFunc(idleFunc);
}
