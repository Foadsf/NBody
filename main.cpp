#include "Body.h"
#include "Physics.h"
#include "Graphics.h"
#include "Octree.h"
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
  //graphicsMain();
  
  
  double center[3] = {5.0, 5.0, 5.0};
  double size = 5.0;
  Body a, b, c, d, e, f; 
  a.setRandom(0);
  OctNode* root;
  root = new OctNode(a, center, size);
  insert(root, a, center, size);
  
  
  b.setRandom(1);
  c.setRandom(2);
  d.setRandom(3);
  e.setRandom(4);
  f.setRandom(5);
  
  
  
  return 0;
}
