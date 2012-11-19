#include "Body.h"
#include "Physics.h"
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>

int main() {
  const unsigned int NUMBODIES = 3;
  srand(time(NULL));

  Body bodyList[NUMBODIES];
  for (int i = 0; i < NUMBODIES; i++) 
    bodyList[i].setRandom(i);

  //  Timesteps
  for (int timeStep = 0; timeStep < 4; timeStep++) {
    //  Reset forces at each time step
    for (int currentBody = 0; currentBody < NUMBODIES; currentBody++) {
      bodyList[currentBody].setForce(0, 0, 0);
    }
    for (int currentBody = 0; currentBody < NUMBODIES; currentBody++) {  
      for (int otherBody = 0; otherBody < NUMBODIES; otherBody++) {
        if (currentBody != otherBody) {
          updateBody(bodyList[currentBody], bodyList[otherBody]);
        }
      }
    }
  }
}