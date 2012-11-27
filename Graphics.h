#ifndef Graphics_H
#define Graphics_H

#include "Body.h"
#include "Physics.h"
#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

const double PI = 3.14159265;
extern const unsigned int NUMBODIES;
extern Body bodyList[];

double degToRad(double degrees);
void resetBodies();
void drawAxes();
void keyboard();
void graphicsMain();
void reshape(int w, int h);
void init();
void drawBodies();
void updateBodyPositions();
void display();
void graphicsMain();
#endif
