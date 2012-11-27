#pragma OPENCL EXTENSION cl_khr_fp64 : enable
__kernel void nbody(
	__global double *posX, __global double *posY, __global double *posZ,
	__global double *velX, __global double *velY, __global double *velZ,
	__global double *mass, __global unsigned int *num) 
	{
	
	  double G = 6.6726E-11;
	  int a = get_global_id(0);
	  double forceX = 0.0, forceY = 0.0, forceZ = 0.0;
	  for (int b = 0; b < 100; b++) {
		if (a != b) {
			double r[3] = {posX[b] - posX[a], posY[b] - posY[a], posZ[b] - posZ[a]};
			double acc[3] = {0.0};

			//  Distance function
			double dist = 0.0;
			for (int i = 0; i < 3; i++) {
				dist = dist + r[i]*r[i];
			}
			dist = sqrt(dist + 0.1*0.1);

			forceX = forceX + G*r[0]*mass[a]*mass[b]/pow((float)dist,(float)3.0);
			forceY = forceY + G*r[1]*mass[a]*mass[b]/pow((float)dist,(float)3.0);
			forceZ = forceZ + G*r[2]*mass[a]*mass[b]/pow((float)dist,(float)3.0);

			for(int i =0; i < 3; i++) {
				acc[i] = G*mass[b]*r[i]/pow((float)dist,(float)3.0);
			}
			velX[a] = velX[a] + acc[0];
			velY[a] = velY[a] + acc[1];
			velZ[a] = velZ[a] + acc[2];

			posX[a] = posX[a] + velX[a];
			posY[a] = posY[a] + velY[a];
			posZ[a] = posZ[a] + velZ[a];
		}
	}
}