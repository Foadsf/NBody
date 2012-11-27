Pate Motter
N-Body Problem
README.txt

This program is designed to show the computational differences between a CPU and an OpenCL enabled GPU.
The current program operates on a 100 body problem due to hard-coded limits in the OpenCL source for debugging purposes.

The program was developed on both Windows and an Ubuntu VM up until the OpenCL portion when my VM could not properly handle OpenCL.
I will be installing a full version of Linux to develop on for the rest of the project. I tried to limit the amount of warnings by porting as much 
over to Linux as possible before submitting. 

Both the program and the OpenCL kernel are in 32 bit, but this might be changed to 64 bit for the final program. 

The makefile "should" be correct for linking and using the OpenCL libraries, but there was no way for me to verify this. 

Controls:
	W/S : Zoom in and out of the center 
	A/D : Rotate around the center horizontally
	Q/E : Rotate around the center vertically
	R	: Restart the simulation with randomized values
	M	: Change between CPU and OpenCL modes
	P	: Pause the current state of the program
	ESC	: Exit the program