#ifndef OCL_H
#define OCL_H

#include "Body.h"
#include <CL/cl.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>


void loadFile();
void setupOpencl();
void setupVectors();
void fillVectors();
void updateOpencl();
void readBackData();
void fillBodies();

#endif OCL_H