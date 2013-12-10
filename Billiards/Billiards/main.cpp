/**
 * Entry point. Yay.
 *
 * @author Taras Mychaskiw
 * @version 1.0
 * @since 2013-12-10
**/
#include "main.h"
Global global;

/**
 * Main glut redraw function.
**/
void displayFunc(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glPopMatrix();
}


/**
 * glut keyboard function.
 *
 * @param key the character struck
 * @param x the x coord of where the mouse was when key was struck
 * @param y the y coord of where the mouse was when key was struck
**/
void keyboardFunc(unsigned char key, int x, int y){
    switch (key){
    case ESC: case 'q': case 'Q':
        return glutDestroyWindow(global.glutWindow);
    }
}


/**
 * glut mouse move function.
 *
 * @param x the x coord of where the mouse event occurred
 * @param y the y coord of where the mouse event occurred
**/
void motionFunc(int x, int y){
}


/**
 * glut mouse click function.
 *
 * @param button the mouse button clicked
 * @param state the state the button is in (up,down)
 * @param x the x coord of where the mouse event occurred
 * @param y the y coord of where the mouse event occurred
**/
void mouseFunc(int button, int state, int x, int y){
}


/**
 * Entry point to the application. Defines the main window etc.
**/
int main(int argc, char** argv){
    srand((unsigned)time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    global.glutWindow = glutCreateWindow("gl-billiards");
    //glutFullScreen();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0, 0, 0, 1);
    glOrtho(-ORTHO_WIDTH, ORTHO_WIDTH, -ORTHO_HEIGHT, ORTHO_HEIGHT, -ORTHO_DEPTH, ORTHO_DEPTH);

    glutDisplayFunc(displayFunc);
    //glutIdleFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);

    glutMainLoop();
    return 0;
}
