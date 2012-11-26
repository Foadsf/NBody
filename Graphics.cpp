#include "Graphics.h"
#include "Body.h"

int cTheta = 0, cPhi = 90;
float cx, cy, cz;
float aspectRatio = 1.0;
float AR = 1.0;
bool reset = false;
#define UNUSED(x) ((void)(x))

struct cam {
	float x;
	float y;
	float z;
}c;

float degToRad(double degrees) {
	return degrees*PI/180.0f;
}

void resetBodies() {
	for (int i = 0; i < NUMBODIES; i++) 
		bodyList[i].setRandom(i);
}

void init() {
	cx = 20.0; //camera location
	cy = 15.0;
	cz = 20.0;

	c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
  c.y = cy * cos(degToRad(cPhi));
	c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST); 		       // Enable depth buffering
	resetBodies();
}

void drawBodies() {
	glColor3f(1.0, 1.0, 0.0);
	for (int currentBody = 0; currentBody < NUMBODIES; currentBody++) {
		glPushMatrix();
		glTranslatef(5, 5, 5);
		glTranslated(bodyList[currentBody].getPosX(), bodyList[currentBody].getPosY(), bodyList[currentBody].getPosZ());
		glutSolidSphere(0.05, 10, 10);
		glPopMatrix();
	}
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

void drawAxes() {
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(10, 10, 10);
	glutWireCube(10);
	glPopMatrix();
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(50, AR, 1, 60);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0+c.x,10.0+c.y, 10.0+c.z, 10.0, 10.0, 10.0, 0.0, 1.0, 0.0);
	drawAxes();
	drawBodies();
	updateBodyPositions();
	glLoadIdentity();
	glFlush();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, float(w)/float(h), 0.001, 1000);
	glMatrixMode(GL_MODELVIEW);
	AR = float(w)/float(h);
}

float angle = 0.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
int yOrigin = -1;
float lx=0.0f,lz=-1.0f;

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
	display();
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0 || yOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 2.0f;
		cTheta+=deltaAngle;
	}
	display();
}

void keyboard (unsigned char key, int x, int y) {
	UNUSED(x);
	UNUSED(y);
	if (key=='a') {
		cTheta = (cTheta - 3) % 360;
		c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
		c.y = cy * cos(degToRad(cPhi));
		c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));
	} else  if (key=='d') {
		cTheta = (cTheta + 3) % 360;
		c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
		c.y = cy * cos(degToRad(cPhi));
		c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));
	} else  if (key=='q') {
		cPhi = (cPhi + 3);
		if (cPhi >= 177)
			cPhi = 177;
		c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
		c.y = cy * cos(degToRad(cPhi));
		c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));
	} else  if (key=='e') {
		cPhi = (cPhi - 3);
		if (cPhi <= 3)
			cPhi = 3;
		c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
		c.y = cy * cos(degToRad(cPhi));
		c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));
	} else  if (key=='w') {
		cx -= 0.25;
		cy -= 0.25;
		cz -= 0.25;
		c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
		c.y = cy * cos(degToRad(cPhi));
		c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));
	} else  if (key=='s') {
		cx += 0.25;
		cy += 0.25;
		cz += 0.25;
		c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
		c.y = cy * cos(degToRad(cPhi));
		c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));
	} else  if (key==27) {
		exit(0);
	} else if (key == 'r') {
		resetBodies();
	}
	display();
}

void graphicsMain() {
	int argc = 1;
	char* argv[] = {"NBody", NULL};
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutIdleFunc(display);
	glutMainLoop();
}