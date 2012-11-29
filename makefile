.cpp.o:
	g++ -c -Wall -I/usr/local/cuda/include -I/usr/include/ -L/usr/lib $^
nbody: main.o Graphics.o Physics.o Body.o    
	g++ -o $@ $^ -I/usr/local/cuda/include -I/usr/include/ -L/usr/lib -lOpenCL -lglut -lGLU -lGL
clean:  
	rm -rf *o nbody *~
