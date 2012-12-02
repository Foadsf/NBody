#include "OCL.h"

FILE* fp; char *sourceStr; size_t sourceSize;
cl_platform_id platformIDs[5];
cl_platform_id platformID;
cl_device_id deviceID = NULL;
cl_uint numDevices, numPlatforms;
cl_int status;
cl_context context;
cl_command_queue commandQueue;
cl_program program;
cl_kernel kernel;
cl_mem posXMem, posYMem, posZMem;
cl_mem velXMem, velYMem, velZMem;
cl_mem massMem, numMem; 
size_t globalSize, localSize;

extern std::vector<Body> bodyList;
double *bodyPosX; 
double *bodyPosY; 
double *bodyPosZ;
double *bodyVelX; 
double *bodyVelY; 
double *bodyVelZ;
double *bodyMass;
unsigned int* bodyNum;
extern unsigned int NUMBODIES;

//  Initialize vectors that will be passed to the kernel
void setupVectors() {
	bodyPosX = new double[NUMBODIES]; bodyPosY = new double[NUMBODIES]; bodyPosZ = new double[NUMBODIES];
	bodyVelX = new double[NUMBODIES]; bodyVelY = new double[NUMBODIES]; bodyVelZ = new double[NUMBODIES];
	bodyMass = new double[NUMBODIES];
	bodyNum = new unsigned int[NUMBODIES];
}

void setupOpencl() {
	globalSize = NUMBODIES;
	localSize = 50;

	status = clGetPlatformIDs(5, platformIDs, &numPlatforms);
	for (unsigned int i = 0; i < numPlatforms; i++) {
		status = clGetDeviceIDs(platformIDs[i], CL_DEVICE_TYPE_GPU, 1, &deviceID, &numDevices);
		if(numDevices != 0) {
			platformID = platformIDs[i];
			break;
		}
	}
	if (numDevices == 0)
		std::cout << "No GPU devices were found\n";
	context = clCreateContext(NULL, 1, &deviceID, NULL, NULL, &status);
	commandQueue = clCreateCommandQueue(context, deviceID, 0, &status);
	program = clCreateProgramWithSource(context, 1, (const char **)&sourceStr, (const size_t *)&sourceSize, &status);
	status = clBuildProgram(program, 1, &deviceID, NULL, NULL, NULL);
	kernel = clCreateKernel(program, "nbody", &status);

	posXMem = clCreateBuffer(context, CL_MEM_READ_WRITE, NUMBODIES*sizeof(double), NULL, &status);
	posYMem = clCreateBuffer(context, CL_MEM_READ_WRITE, NUMBODIES*sizeof(double), NULL, &status);
	posZMem = clCreateBuffer(context, CL_MEM_READ_WRITE, NUMBODIES*sizeof(double), NULL, &status);
	velXMem = clCreateBuffer(context, CL_MEM_READ_WRITE, NUMBODIES*sizeof(double), NULL, &status);
	velYMem = clCreateBuffer(context, CL_MEM_READ_WRITE, NUMBODIES*sizeof(double), NULL, &status);
	velZMem = clCreateBuffer(context, CL_MEM_READ_WRITE, NUMBODIES*sizeof(double), NULL, &status);
	massMem = clCreateBuffer(context, CL_MEM_READ_WRITE, NUMBODIES*sizeof(double), NULL, &status);
	numMem = clCreateBuffer(context, CL_MEM_READ_WRITE, NUMBODIES*sizeof(unsigned int), NULL, &status);

	status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&posXMem);
	status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&posYMem);
	status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&posZMem);
	status = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&velXMem);
	status = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&velYMem);
	status = clSetKernelArg(kernel, 5, sizeof(cl_mem), (void*)&velZMem);
	status = clSetKernelArg(kernel, 6, sizeof(cl_mem), (void*)&massMem);
	status = clSetKernelArg(kernel, 7, sizeof(cl_mem), (void*)&numMem);
	status = clSetKernelArg(kernel, 8, sizeof(unsigned int), &NUMBODIES);
}

void updateOpencl() {
	status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
	//std::cout << "Status in updateOpencl() = " << status << std::endl;
}

void loadFile() {
	fp = fopen("nbody.cl", "r");
	if (!fp) {
		std::cout << "Kernel was not loaded properly\n";
	} else {
		std::cout << "Kernel was loaded\n";
	}
	sourceStr = new char[1048576];
	sourceSize = fread(sourceStr, 1, 1048576, fp);
	fclose(fp);
}

//  Populate the vectors with all of the body data
void fillVectors() {
	for (unsigned int i = 0; i < NUMBODIES; i++) {
		bodyPosX[i] = bodyList[i].getPosX(); 
		bodyPosY[i] = bodyList[i].getPosY(); 
		bodyPosZ[i] = bodyList[i].getPosZ();
		bodyVelX[i] = bodyList[i].getVelX(); 
		bodyVelY[i] = bodyList[i].getVelY(); 
		bodyVelZ[i] = bodyList[i].getVelZ();
		bodyMass[i] = bodyList[i].getMass();
		bodyNum[i] = bodyList[i].getNum();
	}
	status = clEnqueueWriteBuffer(commandQueue, posXMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyPosX, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(commandQueue, posYMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyPosY, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(commandQueue, posZMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyPosZ, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(commandQueue, velXMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyVelX, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(commandQueue, velYMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyVelY, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(commandQueue, velZMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyVelZ, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(commandQueue, massMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyMass, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(commandQueue, numMem, CL_TRUE, 0, NUMBODIES * sizeof(unsigned int), bodyNum, 0, NULL, NULL); 
	//std::cout << "Status in fillvectors() = " << status << std::endl;
}

void readBackData() {
	status = clEnqueueReadBuffer(commandQueue, posXMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyPosX, 0, NULL, NULL);
	status = clEnqueueReadBuffer(commandQueue, posYMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyPosY, 0, NULL, NULL);
	status = clEnqueueReadBuffer(commandQueue, posZMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyPosZ, 0, NULL, NULL);
	status = clEnqueueReadBuffer(commandQueue, velXMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyVelX, 0, NULL, NULL);
	status = clEnqueueReadBuffer(commandQueue, velYMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyVelY, 0, NULL, NULL);
	status = clEnqueueReadBuffer(commandQueue, velZMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyVelZ, 0, NULL, NULL);
	status = clEnqueueReadBuffer(commandQueue, massMem, CL_TRUE, 0, NUMBODIES * sizeof(double), bodyMass, 0, NULL, NULL);
	status = clEnqueueReadBuffer(commandQueue, numMem, CL_TRUE, 0, NUMBODIES * sizeof(unsigned int), bodyNum, 0, NULL, NULL);

	//std::cout << "Status in readBackData() = " << status << std::endl;
	fillBodies();
}

//  Place the update information from the kernel into the canonical list so it can be used by different functions
void fillBodies() {
	for (unsigned int i = 0; i < NUMBODIES; i++) {
		bodyList[i].setPos(bodyPosX[i], bodyPosY[i], bodyPosZ[i]); 
		bodyList[i].setVel(bodyVelX[i], bodyVelY[i], bodyVelZ[i]);
		bodyList[i].setMass(bodyMass[i]);
		bodyList[i].setNum(bodyNum[i]);
	}
}
