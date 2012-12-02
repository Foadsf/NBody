#ifndef Graphics_H
#define Graphics_H

#include <omp.h>
#include "OCL.h"
#include "Body.h"
#include "Physics.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


double degToRad(double degrees);
void resetBodies();

void fillBodies();
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

