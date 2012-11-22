#include "Body.h"
#include "Physics.h"
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>

const unsigned int NUMBODIES = 3;
Body bodyList[NUMBODIES];

int main() {
  srand(time(NULL));
  graphicsMain();
  return 0;
}