#  Pate Motter 
#  Final Project
#  N-Body Problem
#  Makefile

CC = g++

#Add your choice of flags
FLAGS = -W -Wall -lGL -lGLU -lglut

all: nbody

clean:  
	    /bin/rm -rf     \
	    nbody		         \
      *.o
        
nbody:	
	g++ -o nbody *.cpp $(FLAGS)
