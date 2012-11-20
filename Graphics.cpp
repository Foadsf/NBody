#include "Graphics.h"
#include "Body.h"


float degToRad(double degrees) {
	return degrees*PI/180.0f;
}

void init() {
	for (int i = 0; i < NUMBODIES; i++) 
		bodyList[i].setRandom(i);
	//  Timesteps
}

void drawBodies() {

}

void updateBodyPositions() {
	//  Reset forces at each time step
	for (int currentBody = 0; currentBody < NUMBODIES; currentBody++) {
		bodyList[currentBody].setForce(0, 0, 0);
	}
	//  N^2 Naive approach
	for (int currentBody = 0; currentBody < NUMBODIES; currentBody++) {  
		for (int otherBody = 0; otherBody < NUMBODIES; otherBody++) {
			if (currentBody != otherBody) {
				updateBody(bodyList[currentBody], bodyList[otherBody]);
			}
		}
	}
}

void display (void) {
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glClearColor (0.0,0.0,0.0,1.0); //clear the screen to   black
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glLoadIdentity();  
	glutSwapBuffers(); //swap the buffers
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode (GL_PROJECTION); //set the matrix to projection

	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, , epth)
	glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

void graphicsMain() {
	int argc = 1;
	char* argv[] = {"NBody", NULL};
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); //set  the display to Double buffer, with depth
	glutInitWindowSize (500, 500); //set the window size
	glutInitWindowPosition (100, 100); //set the position of  the window
	glutCreateWindow ("3D Scene"); //the caption of the window
	init (); //call the Init function
	glutDisplayFunc (display); //use the display function to  draw everything
	glutIdleFunc (display); //update any variables in display
	glutReshapeFunc (reshape); //reshape the window accordingly
	glutMainLoop (); //call the main loop
}