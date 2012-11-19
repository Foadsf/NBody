#include "Graphics.h"


float degToRad(double degrees) {
  return degrees*PI/180.0f;
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0, (GLfloat) w/(GLfloat) h, 0.1, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 20, 0, 0, 0, 0, 0, 1, 0);
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void drawBodies() {

}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  drawBodies();
}

void graphicsMain() {
  glutInit(NULL, NULL);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Nbody");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}