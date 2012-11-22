#include "Graphics.h"
#include "Body.h"

int camRot = 220;
float aspectRatio = 1.0;
static int spin = 45;
#define UNUSED(x) ((void)(x))

struct cam {
	float x;
	float y;
	float z;
};
cam c;

float degToRad(double degrees) {
	return degrees*PI/180.0f;
}

void init() {
	c.x = 3.0; //camera location
	c.y = 2.0;
	c.z = 2.0;
	glClearColor (0.3, 0.3, 0.3, 0.0);
	glEnable(GL_DEPTH_TEST); 		       // Enable depth buffering
	for (int i = 0; i < NUMBODIES; i++) 
		bodyList[i].setRandom(i);
}

void drawBodies() {
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
	glColor3f(1.0, 1.0, 1.0);
	drawAxes();
	drawBodies();
	updateBodyPositions();
	glFlush ();
	glutPostRedisplay();
	
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, 2, 0, 2);
	gluPerspective(60, float(w)/float(h), 0.001, 100);
	//gluLookAt(c.x, c.y, c.z, 0.5, 0.5, 0.5, 0.0, 1.0, 0.0);
	gluLookAt(c.x, 0.5, c.z, c.x+cos(degToRad(camRot)), 0.5, c.z+sin(degToRad(camRot)), 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y) {
	UNUSED(x);
	UNUSED(y);
	if (key=='a') {
    camRot = (camRot - 3) % 360;
  } else  if (key=='d') {
    camRot = (camRot + 3) % 360;
  } else  if (key=='q') {
    spin = (spin+5) % 360;
  } else  if (key=='e') {
    spin = (spin-5) % 360;
  } else  if (key=='w') {
    c.x = c.x + cos(degToRad(camRot));
    c.z = c.z + sin(degToRad(camRot));
  } else  if (key=='s') {
    c.x = c.x - cos(degToRad(camRot));
    c.z = c.z - sin(degToRad(camRot));
  } else  if (key==27) {
    exit(0);
  }
	glutPostRedisplay();
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
	glutMainLoop();
}