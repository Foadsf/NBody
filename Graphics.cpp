#include "Graphics.h"
#include "Body.h"

int camRot = 0;
float cx, cy, cz;
float aspectRatio = 1.0;
static int spin = 45;
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
	cx = c.x = 6.0; //camera location
	cy = c.y = 0.5;
	cz = c.z = 6.0;
	c.z = 0.0;
	
	glClearColor (0.3, 0.3, 0.3, 0.0);
	glEnable(GL_DEPTH_TEST); 		       // Enable depth buffering
	resetBodies();
}

void drawBodies() {
	glColor3f(1.0, 1.0, 0.0);
	for (int currentBody = 0; currentBody < NUMBODIES; currentBody++) {
		glPushMatrix();
		glTranslated(bodyList[currentBody].getPosX(), bodyList[currentBody].getPosY(), bodyList[currentBody].getPosZ());
		glutSolidSphere(0.005, 10, 10);
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
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
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
		gluLookAt(c.x, c.y, c.z, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
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
	gluPerspective(60, float(w)/float(h), 0.001, 100);
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
		camRot+=deltaAngle;
	}
	display();
}

void keyboard (unsigned char key, int x, int y) {
	UNUSED(x);
	UNUSED(y);
	if (key=='a') {
    camRot = (camRot - 3) % 360;
		c.x = cx * cos(degToRad(camRot));
		c.z = cz* sin(degToRad(camRot));
  } else  if (key=='d') {
    camRot = (camRot + 3) % 360;
		c.x = cx * cos(degToRad(camRot));
		c.z = cz* sin(degToRad(camRot));
  } else  if (key=='q') {
    spin = (spin+5) % 360;
  } else  if (key=='e') {
    spin = (spin-5) % 360;
  } else  if (key=='w') {
    cx--;
		cz--;
		c.x = cx * cos(degToRad(camRot));
		c.z = cz* sin(degToRad(camRot));
  } else  if (key=='s') {
		cx++;
		cz++;
		c.x = cx * cos(degToRad(camRot));
		c.z = cz* sin(degToRad(camRot));
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