#makefile for Traveling Salesman Problem
#CS325
#Sam Best
#March 4 2013

FLAGS   := -O2 -DNDEBUG -ftree-vectorize -Wall
OBJECTS := main.o city.o tree.o algorithms.o

tsp: $(OBJECTS)
	g++ $(FLAGS) $(OBJECTS) -o tsp

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp
	
city.o: city.cpp
	g++ $(FLAGS) -c city.cpp	
	
tree.o: tree.cpp
	g++ $(FLAGS) -c tree.cpp
	
algorithms.o: algorithms.cpp
	g++ $(FLAGS) -c algorithms.cpp

clean:
	rm -rf *o tsp
