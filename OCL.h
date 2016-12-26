#ifndef OCL_H
#define OCL_H

#include "Body.h"
#ifdef __APPLE__
#include <OpenCL/opencl.h>
// #include <unistd.h>
#else
#include <CL/cl.h>
#endif
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

void loadFile();
void setupOpencl();
void setupVectors();
void fillVectors();
void updateOpencl();
void readBackData();
void fillBodies();

#endif
