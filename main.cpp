#include "Body.h"
#include "Physics.h"
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>
#include "CL/cl.h"

const unsigned int NUMBODIES = 10;
Body bodyList[NUMBODIES];

int main() {
  srand((unsigned int)time(NULL));
  

  graphicsMain();
  return 0;
}
