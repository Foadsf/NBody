#include "Body.h"
#include "Physics.h"
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>
#include "CL/cl.h"

std::vector<Body> bodyList;
unsigned int NUMBODIES = 100;

int main() {
  bodyList.resize(NUMBODIES);
  srand((unsigned int)time(NULL));
  graphicsMain();
  return 0;
}
