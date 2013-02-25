Pate Motter
N-Body Problem
README.txt

This program is designed to show the computational differences between a CPU and an OpenCL enabled GPU.
The current program operates on a 1000 body problem and maxes out at about 4000 using the brute force method. 
The difference between the three modes is very drastic and easily seen on both of my machines. 

The program was developed on both Windows and Linux Mint to help ensure compatibility.

Both the program and the OpenCL kernel are in 32 bit, but this might be changed to 64 bit for the final program. 

Requires libraries for OpenCL and OpenMP to be installed to work correctly. 

Controls:
	W/S : Zoom in and out of the center 
	A/D : Rotate around the center horizontally
	Q/E : Rotate around the center vertically
	R	: Restart the simulation with randomized values
	M	: Change between CPU / OpenMP / OpenCL modes (default = OpenCL)
	N	: Change the shape of the body distribution from 2D to 3D
	P	: Pause the current state of the program
	ESC	: Exit the program

A video of the program running in OpenCL mode can be seen here: http://www.youtube.com/watch?v=WiJtigzdn8I
I recommend watching it in HD as it can be hard to see the bodies otherwise
