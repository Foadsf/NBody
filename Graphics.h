#ifndef Graphics_H
#define Graphics_H

#include "Body.h"
#include "Physics.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <CL/cl.h>
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
extern double *bodyPosX; 
extern double *bodyPosY; 
extern double *bodyPosZ;
extern double *bodyVelX; 
extern double *bodyVelY; 
extern double *bodyVelZ;
extern double *bodyMass;
extern unsigned int* bodyNum;

double degToRad(double degrees);
void resetBodies();
void loadFile();
void setupOpencl();
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
