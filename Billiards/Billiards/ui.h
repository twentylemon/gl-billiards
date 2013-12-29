/**
 * Defines behaviour for the glui user interface. Callback
 * methods for control functionality are defined here.
 *
 * @author Dan Lapp
 * @since 2013-12-27
**/
#include <string.h>
#include "main.h"
#include "glui.h"

#define ZOOM_STEP 0.15

#define CENTER_TYPE_CUE 0
#define CENTER_TYPE_ORIGIN 1

//glui callbacks
void initializeGlui();
void zoomIn();
void zoomOut();
void resetZoom();
void resetCamera();

//glui control methods
void updatePlayerTextField();
