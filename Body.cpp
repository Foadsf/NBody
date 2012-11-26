#include "Body.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

double fRand(double fMin, double fMax) {
	double f = (double)rand() / RAND_MAX;
	return fMin + f*(fMax - fMin);
}

Body::Body(void) {}
Body::~Body(void) {}
//  Set every value
//  Position, Velocity, Mass
void Body::setAll(double inAll[]) {
  posX = inAll[0]; posY = inAll[1]; posZ = inAll[2];
  velX = inAll[3]; velY = inAll[4]; velZ = inAll[5];
  mass = inAll[6]; num = inAll[7];
}
void Body::setAll(double pX, double pY, double pZ,
                  double vX, double vY, double vZ, double m) {
                    posX = pX; posY = pY; posZ = pZ;
                    velX = vX; velY = vY; velZ = vZ;
                    mass = m;
}

void Body::setRandom(unsigned int numBody) {
  posX = fRand(0.0, 10.0);
  posY = fRand(0.0, 10.0);
  posZ = fRand(0.0, 10.0);
  velX = fRand(-0.000001, 0.000001);
  velY = fRand(-0.000001, 0.000001);
  velZ = fRand(-0.000001, 0.000001);
  mass = fRand(1.0, 1000.0);
  num = numBody;
}

//  Set position values
void Body::setPos(double inPos[]) {
  posX = inPos[0];
  posY = inPos[1];
  posZ = inPos[2];
}
void Body::setPos(double x, double y, double z) {
  posX = x;
  posY = y;
  posZ = z;
}

//  Get position values
void Body::getPos(double position[]) {
  position[0] = posX;
  position[1] = posY;
  position[2] = posZ;
}
double Body::getPosX() {
  return posX;
}
double Body::getPosY() {
  return posY;
}

double Body::getPosZ() {
  return posZ;
}

//  Set velocity values
void Body::setVel(double inVel[]) {
  velX = inVel[0];
  velY = inVel[1];
  velZ = inVel[2];
}
void Body::setVel(double x, double y, double z) {
  velX = x;
  velY = y;
  velZ = z;
}

//  Get velocity values
void Body::getVel(double velocities[]) {
  velocities[0] = posX;
  velocities[1] = posY;
  velocities[2] = posZ;
}
double Body::getVelX() {
  return velX;
}
double Body::getVelY() {
  return velY;
}
double Body::getVelZ() {
  return velZ;
}

//  Set mass value
void Body::setMass(double inMass) {
  mass = inMass;
}

//  Get mass value
double Body::getMass() {
  return mass;
}

//  Set force values
void Body::setForce(double inForce[]) {
    forceX = inForce[0];
    forceY = inForce[1];
    forceZ = inForce[2];
}
void Body::setForce(double x, double y, double z) {
  forceX = x;
  forceY = y;
  forceZ = z;
}

//  Get force values
void Body::getForce(double forces[]) {
  forces[0] = forceX;
  forces[1] = forceY;
  forces[2] = forceZ;
}
double Body::getForceX() {
  return forceX;
}
double Body::getForceY() {
  return forceY;
}
double Body::getForceZ() {
  return forceZ;
}

//  Set num
void Body::setNum(unsigned int numBody) {
  num = numBody;
}

//  Get num
unsigned int Body::getNum() {
  return num;
}