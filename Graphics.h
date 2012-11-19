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

float degToRad(double degrees);
void reshape(int w, int h);
void init();
void drawBodies();
void display();
void graphicsMain();