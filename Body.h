#ifndef Body_H
#define Body_H

#include <vector>

double fRand(double fMin, double fMax);

class Body
{
public:
  Body(void);
  ~Body(void);

  //  Everything
  void setAll(double inAll[]);
  void setAll(double pX, double pY, double pZ,
              double vX, double vY, double vZ, double m);
  void setRandom(unsigned int numBody);
  
  //  Position
  void setPos(double inPos[]);
  void setPos(double x, double y, double z);
  void getPos(double position[]);
  double getPosX();
  double getPosY();
  double getPosZ();

  //  Velocity
  void setVel(double inVel[]);
  void setVel(double x, double y, double z);
  void getVel(double velocities[]);
  double getVelX();
  double getVelY();
  double getVelZ();

  //  Mass
  void setMass(double inMass);
  double getMass();

  //  Force
  void setForce(double inForce[]);
  void setForce(double x, double y, double z);
  void getForce(double forces[]);
  double getForceX();
  double getForceY();
  double getForceZ();

  //  Num
  void setNum(unsigned int numBody);
  unsigned int getNum();

private:
  double posX, posY, posZ;
  double velX, velY, velZ;
  double mass;
  double forceX, forceY, forceZ;
  unsigned int num;
};

#endif