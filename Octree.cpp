#include "Octree.h"

void insert(OctNode *&root, Body b, double inCenter[], double inSize) {

	//  determine where the particle is located compared to the current center
	bool x = 0, y = 0, z = 0;
	x = (b.getPosX() >= inCenter[0]) ? true : false;
	y = (b.getPosY() >= inCenter[1]) ? true : false;
	z = (b.getPosZ() >= inCenter[2]) ? true : false;

  //  determine the new recursive center/size 
	double newSize = inSize/2.0;
	double newCenter[3] = {inCenter[0], inCenter[1], inCenter[2]};
	newCenter[0] += (x) ? newSize : -newSize;
	newCenter[1] += (y) ? newSize : -newSize;
	newCenter[2] += (z) ? newSize : -newSize;

	if (root == NULL) {							//NULL
		root = new OctNode(b, inCenter, inSize);
	} else if (x && y && z) {				//ppp
		insert(root->ppp, b, newCenter, newSize);
	} else if (x && y && !z) { 			//ppn
		insert(root->ppn, b, newCenter, newSize);
	} else if (x && !y && z) { 			//pnp
		insert(root->pnp, b, newCenter, newSize);
	} else if (x && !y && !z) { 		//pnn
		insert(root->pnn, b, newCenter, newSize);
	} else if (!x && y && z) { 			//npp
		insert(root->npp, b, newCenter, newSize);
	} else if (!x && y && !z) { 		//npn
		insert(root->npn, b, newCenter, newSize);
	} else if (!x && !y && z) { 		//nnp
		insert(root->nnp, b, newCenter, newSize);
	} else if (!x && !y && !z) { 		//nnn
		insert(root->nnn, b, newCenter, newSize);
	}	

  //  update each node based on the bodies that pass through it
  root->totalMass += b.getMass();
  root->centerOfMass[0] = (b.getMass()*b.getPosX() + root->totalMass*root->centerOfMass[0])  / root->totalMass;
  root->centerOfMass[1] = (b.getMass()*b.getPosY() + root->totalMass*root->centerOfMass[1])  / root->totalMass;
  root->centerOfMass[2] = (b.getMass()*b.getPosZ() + root->totalMass*root->centerOfMass[2])  / root->totalMass;
}
