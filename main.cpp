#include "Body.h"
#include "Physics.h"
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>
#include "CL/cl.h"

std::vector<Body> bodyList;
unsigned int NUMBODIES = 1000;

int main(int argc, char* argv[]) {
  if (argc > 1) 
		NUMBODIES = atoi(argv[1]);
  bodyList.resize(NUMBODIES);
  srand((unsigned int)time(NULL));
  graphicsMain();
  return 0;
}
