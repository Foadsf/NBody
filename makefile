#  Pate Motter 
#  Final Project
#  N-Body Problem
#  Makefile

CC = g++
#INC = -I/usr/include/

#Add your choice of flags
FLAGS = -W -Wall -lGL -lGLU -lglut -lOpenCL

all: nbody

clean:  
	    rm -rf *o nbody *~
        
nbody: main.cpp Graphics.o Physics.o Body.o	
	g++ $(FLAGS) -o nbody main.cpp Graphics.o Physics.o Body.o
	
Graphics.o: Graphics.cpp
	g++ -c -Wall Graphics.cpp
	
Physics.o: Physics.cpp
	g++ -c -Wall Physics.cpp

Body.o: Body.cpp
	g++ -c -Wall Body.cpp
