.cpp.o:
	g++-6 -c -Wall  $^ 
nbody: main.o Graphics.o Physics.o Body.o OCL.o Octree.o
	g++-6 -o $@ $^ -framework OpenCL -framework OpenGL -framework GLUT -fopenmp
clean:
	rm -rf *o nbody *~
