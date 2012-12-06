#include "Octree.h"

void insert(OctNode *&root, Body b, double inCenter[], double size) {
	//  determine where the particle is located compared to the current center
	bool x, y, z;
	//x = (b.getPosX() >= inCenter[0]) ? true : false;
	//y = (b.getPosY() >= inCenter[1]) ? true : false;
	//z = (b.getPosZ() >= inCenter[2]) ? true : false;
	//double newCenter[3] = {inCenter[0]/= 2.0, inCenter[1]/= 2.0, inCenter[2]/= 2.0};
	//size /= 2.0;
	double newCenter[3] {1,1,1};
	double newSize = 5.24;
	
	insert(root->ppp, b, newCenter, newSize);
	
	if (x && y && z) {							//ppp
		//insert(root, b, inCenter, size);
	} else if (x && y && !z) { 			//ppn
	
	} else if (x && !y && z) { 			//pnp
	
	} else if (x && !y && !z) { 		//pnn
	
	} else if (!x && y && z) { 			//npp
	
	} else if (!x && y && !z) { 		//npn
	
	} else if (!x && !y && z) { 		//nnp
	
	} else if (!x && !y && !z) { 		//nnn
	
	}
		
		std::cout << "body:" << b.getNum() << std::endl;
		std::cout << "size:" << size << std::endl;
		std::cout << "center:" << inCenter[0] << "," << inCenter[1] << "," << inCenter[2] << std::endl;
}
