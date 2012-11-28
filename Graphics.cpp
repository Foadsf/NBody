#include "Graphics.h"
#include "Body.h"

int cTheta = 0, cPhi = 90;
float cx, cy, cz;
float aspectRatio = 1.0;
float AR = 1.0;
bool reset = false;
bool cpu = true, halt = false;
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

#define UNUSED(x) ((void)(x))

//  Camera
struct cam {
	double x;
	double y;
	double z;
}c;

//  Initialize vectors that will be passed to the kernel
void setupVectors() {
	bodyPosX = new double[NUMBODIES]; bodyPosY = new double[NUMBODIES]; bodyPosZ = new double[NUMBODIES];
	bodyVelX = new double[NUMBODIES]; bodyVelY = new double[NUMBODIES]; bodyVelZ = new double[NUMBODIES];
	bodyMass = new double[NUMBODIES];
	bodyNum = new unsigned int[NUMBODIES];
}

//  For trig functions
double degToRad(double degrees) {
	return degrees*PI/180.0f;
}

//  Reset all bodies back to random values
void resetBodies() {
	for (unsigned int i = 0; i < NUMBODIES; i++) 
		bodyList[i].setRandom(i);
}

//  Setup camera position, black background, start bodies as random
void init() {
	setupVectors();
	loadFile();
	setupOpencl();

	cx = 20.0; //camera location
	cy = 15.0;
	cz = 20.0;

	c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
	c.y = cy * cos(degToRad(cPhi));
	c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST); 		       // Enable depth buffering
	resetBodies();

}

//  Draw each body, offset to be within 5-15 range in each direction
void drawBodies() {
	glColor3f(1.0, 1.0, 0.0);
	for (unsigned int currentBody = 0; currentBody < NUMBODIES; currentBody++) {
		glPushMatrix();
		glTranslatef(5, 5, 5);
		glTranslated(bodyList[currentBody].getPosX(), bodyList[currentBody].getPosY(), bodyList[currentBody].getPosZ());
		glutSolidSphere(0.05, 10, 10);
		glPopMatrix();
	}
}

void setupOpencl() {
	globalSize = NUMBODIES;
	localSize = 10;

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

void fillBodies() {
	for (unsigned int i = 0; i < NUMBODIES; i++) {
		bodyList[i].setPos(bodyPosX[i], bodyPosY[i], bodyPosZ[i]); 
		bodyList[i].setVel(bodyVelX[i], bodyVelY[i], bodyVelZ[i]);
		bodyList[i].setMass(bodyMass[i]);
		bodyList[i].setNum(bodyNum[i]);
	}
}

//  Calculate the new forces, positions, and velocities for each body
void updateBodyPositions() {
	//  Reset forces at each time step
	for (unsigned int currentBody = 0; currentBody < NUMBODIES; currentBody++) {
		bodyList[currentBody].setForce(0, 0, 0);
	}
	//  N^2 Naive approach
	if (halt) {
	} else if (cpu) {
		for (unsigned int currentBody = 0; currentBody < NUMBODIES; currentBody++) {  
			for (unsigned int otherBody = 0; otherBody < NUMBODIES; otherBody++) {
				if (currentBody != otherBody) {
					updateBody(bodyList[currentBody], bodyList[otherBody]);
				}
			}
		}
	} else if (!cpu) {
		fillVectors();
		updateOpencl();
		readBackData();
	}
}

//  Box around the starting positions of the bodies, helps in visualizing movement
void drawAxes() {
	glColor3d(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(10, 10, 10);
	glutWireCube(10);
	glPopMatrix();
}

//  Update bodies and view
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(50, AR, 1, 60);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0+c.x,10.0+c.y, 10.0+c.z, 10.0, 10.0, 10.0, 0.0, 1.0, 0.0);
	drawAxes();
	drawBodies();
	updateBodyPositions();
	glLoadIdentity();
	glFlush();
}

//  Standard reshape function
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, float(w)/float(h), 0.001, 1000);
	glMatrixMode(GL_MODELVIEW);
	AR = float(w)/float(h);
}

//  Keyboard controls
void keyboard (unsigned char key, int x, int y) {
	UNUSED(x);
	UNUSED(y);
	//  Rotate around
	if (key=='a') {
		cTheta = (cTheta - 3) % 360;
	} else  if (key=='d') {
		cTheta = (cTheta + 3) % 360;
		//  Rotate above/below
	} else  if (key=='q') {
		cPhi += 3;
		if (cPhi >= 177)
			cPhi = 177;
	} else  if (key=='e') {
		cPhi -= 3;
		if (cPhi <= 3)
			cPhi = 3;
		//  Zoom in/out
	} else  if (key=='w') {
		cx -= 0.25;
		cy -= 0.25;
		cz -= 0.25;
	} else  if (key=='s') {
		cx += 0.25;
		cy += 0.25;
		cz += 0.25;
		//  Close the program
	} else  if (key==27) {
		exit(0);
		//  Restart simulation
	} else if (key == 'r') {
		resetBodies();
	} else if (key == 'm') {
		cpu = !cpu;
	} else if (key == 'p') {
		halt = !halt;
	}
	c.x = cx * sin(degToRad(cTheta)) * sin(degToRad(cPhi));
	c.y = cy * cos(degToRad(cPhi));
	c.z = cz * cos(degToRad(cTheta)) * sin(degToRad(cPhi));
	display();
}

void graphicsMain() {
	int argc = 1;
	char title[] = "NBody";
	char* argv[] = {title, NULL};
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutMainLoop();
}
