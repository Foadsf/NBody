#include <iostream>
#include <vector>
#include "Body.h"
#include "Physics.h"

int main() {
  Body a, b;

  //a.setAll(0, 0, 0, 1, 1, 1, 100, 0, 0, 0);
  a.setAll(0, 0, 0, 0, 0, 0, 100, 0, 0, 0);
  b.setAll(1, 1, 1, 0, 0, 0, 10000000, 0, 0, 0);


  for(int i = 0; i < 10; i++) {
    //  reset forces
    a.setForce(0, 0, 0);
    b.setForce(0, 0, 0);
    updateBody(a, b);
  }
  
  //std::vector<double> out = normalize(a, b);
  //acceleration(a,b);
  //acceleration(b,a);
}