#include "Body.h"
#include "Physics.h"
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>
#include "CL/cl.h"

const unsigned int NUMBODIES = 10;
Body bodyList[NUMBODIES];

int main() {
  srand(time(NULL));
  cl_platform_id platform_id = NULL;
  cl_device_id device_id = NULL;   
  cl_uint ret_num_devices;
  cl_uint ret_num_platforms;
  cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);

  graphicsMain();
  return 0;
}
