#include "Graphics.h"
#include "Body.h"

int cTheta = 0, cPhi = 90;
float cx, cy, cz;
float aspectRatio = 1.0;
float AR = 1.0;
bool reset = false;
#define UNUSED(x) ((void)(x))

//  Camera
struct cam {
  double x;
  double y;
  double z;
}c;

//  For trig functions
double degToRad(double degrees) {
  return degrees*PI/180.0f;
}

//  Reset all bodies back to random values
void resetBodies() {
  for (unsigned int i = 0; i < NUMBODIES; i++) 
    bodyList[i].setRandom(i);
}

//  Setup camera position, black background, start bodies as random
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

//  Draw each body, offset to be within 5-15 range in each direction
void drawBodies() {
  glColor3f(1.0, 1.0, 0.0);
  for (unsigned int currentBody = 0; currentBody < NUMBODIES; currentBody++) {
    glPushMatrix();
    glTranslatef(5, 5, 5);
    glTranslated(bodyList[currentBody].getPosX(), bodyList[currentBody].getPosY(), bodyList[currentBody].getPosZ());
    glutSolidSphere(0.05, 10, 10);
    glPopMatrix();
  }
}

//  Calculate the new forces, positions, and velocities for each body
void updateBodyPositions() {
  //  Reset forces at each time step
  for (unsigned int currentBody = 0; currentBody < NUMBODIES; currentBody++) {
    bodyList[currentBody].setForce(0, 0, 0);
  }
  //  N^2 Naive approach
  for (unsigned int currentBody = 0; currentBody < NUMBODIES; currentBody++) {  
    for (unsigned int otherBody = 0; otherBody < NUMBODIES; otherBody++) {
      if (currentBody != otherBody) {
        updateBody(bodyList[currentBody], bodyList[otherBody]);
      }
    }
  }
}

//  Box around the starting positions of the bodies, helps in visualizing movement
void drawAxes() {
  glColor3d(0.2, 0.2, 0.2);
  glPushMatrix();
  glTranslatef(10, 10, 10);
  glutWireCube(10);
  glPopMatrix();
}

//  Update bodies and view
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

//  Standard reshape function
void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, float(w)/float(h), 0.001, 1000);
  glMatrixMode(GL_MODELVIEW);
  AR = float(w)/float(h);
}

/*
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
*/

//  Keyboard controls
void keyboard (unsigned char key, int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //  Rotate around
  if (key=='a') {
    cTheta = (cTheta - 3) % 360;
  } else  if (key=='d') {
    cTheta = (cTheta + 3) % 360;
    //  Rotate above/below
  } else  if (key=='q') {
    cPhi += 3;
    if (cPhi >= 177)
      cPhi = 177;
  } else  if (key=='e') {
    cPhi -= 3;
    if (cPhi <= 3)
      cPhi = 3;
    //  Zoom in/out
  } else  if (key=='w') {
    cx -= 0.25;
    cy -= 0.25;
    cz -= 0.25;
  } else  if (key=='s') {
    cx += 0.25;
    cy += 0.25;
    cz += 0.25;
    //  Close the program
  } else  if (key==27) {
    exit(0);
    //  Restart simulation
  } else if (key == 'r') {
    resetBodies();
  }
  c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
  c.y = cy * cos(degToRad(cPhi));
  c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));
  display();
}

void graphicsMain() {
  int argc = 1;
  char title[] = "NBody";
  char* argv[] = {title, NULL};
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  //glutMouseFunc(mouseButton);
  //glutMotionFunc(mouseMove);
  glutIdleFunc(display);
  glutMainLoop();
}
