#ifndef Octree_H
#define Octree_H

#include "Body.h"
#include <iostream>

struct OctNode {
	double center[3];
  double centerOfMass[3];
  double totalMass;
  double size;
	Body b;

	
	//  Children
	OctNode *ppp;
	OctNode *ppn;
	OctNode *pnp;
	OctNode *pnn;
	OctNode *npp;
	OctNode *npn;
	OctNode *nnp;
	OctNode *nnn;	
	
	OctNode(Body inBody, double inCenter[], double inSize) {
		b = inBody;
    totalMass = 0.0;
		for (int i = 0; i < 3; i++) {
		  centerOfMass[i] = 0.0;
      center[i] = inCenter[i];
    }
		size = inSize;
		
		ppp = NULL;
		ppn = NULL;
		pnp = NULL;
		pnn = NULL;
		npp = NULL;
		npn = NULL;
		nnp = NULL;
		nnn = NULL;
	}
};

void find(unsigned int bodyNum);
void insert(OctNode *&root, Body b, double inCenter[], double size);
#endif
