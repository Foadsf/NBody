.cpp.o:
	g++ -c -Wall -I/usr/local/cuda/include -I/usr/include/ -L/usr/lib $^ -fopenmp
nbody: main.o Graphics.o Physics.o Body.o OCL.o
	g++ -o $@ $^ -I/usr/local/cuda/include -I/usr/include/ -L/usr/lib -lOpenCL -lglut -lGLU -lGL -fopenmp
clean:  
	rm -rf *o nbody *~
