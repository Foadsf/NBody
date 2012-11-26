#ifndef Physics_H
#define Physics_H
#include "Body.h"

double distance(Body a, Body b);
void updateBody(Body &a, Body &b);
void print(Body a, double bMass, double dist);
#endif