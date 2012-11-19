#include "Physics.h"
#include <math.h>
#include <iostream>

const double G = 6.6726E-11;
const double EPS = 1.0;

double distance(double distances[]) {
  double dist = 0.0;
  for (int i = 0; i < 3; i++) {
    dist += distances[i]*distances[i];
  }
  return sqrt(dist);// + damp*damp;
}

void updateBody(Body &a, Body &b) {
  double r[3] = {b.getPosX() - a.getPosX(), b.getPosY() - a.getPosY(), b.getPosZ() - a.getPosZ()};
  double acc[3] = {0.0};
  double pos[3] = {0.0};
  double dist = distance(r);

  //  update force
  a.setForce( a.getForceX() + (G * r[0] * a.getMass() * b.getMass() /  powf(dist,3.0)),
    a.getForceY() + (G * r[1] * a.getMass() * b.getMass() / powf(dist,3.0)),
    a.getForceZ() + (G * r[2] * a.getMass() * b.getMass() / powf(dist,3.0)));
  std::cout << "Forces " << a.getForceX() << " " << a.getForceY() << " " << a.getForceZ() << std::endl;
  std::cout << "My total force " << sqrt(a.getForceX()*a.getForceX() + 
    a.getForceY()*a.getForceY() + 
    a.getForceZ()*a.getForceZ()) << std::endl;
  std::cout << "Actual Total force " << G*a.getMass()*b.getMass()/(powf(dist,2.0)) << std::endl;

  //  update velocity
  for (int i = 0; i < 3; i++) {
    acc[i] = G * b.getMass() * r[i] / powf(dist,3.0);
  }
  a.setVel(a.getVelX() + acc[0], a.getVelY() + acc[1], a.getVelZ() + acc[2]);
  std::cout << "New velocity: " << a.getVelX() << " " << a.getVelY() << " " << a.getVelZ() << std::endl;

  //  update position
  a.setPos(a.getPosX() + a.getVelX(), a.getPosY() + a.getVelY(), a.getPosZ() + a.getVelZ()); 
  std::cout << "New position: " << a.getPosX() << " " << a.getPosY() << " " << a.getPosZ() << std::endl << std::endl;
}