CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
BUILDDIR := Source

all: FieldRunners.out

FieldRunners.out: main.o rsdl.o FieldRunners.o Building.o Enemy.o functions.o Shooting.o
	$(CC) main.o rsdl.o FieldRunners.o Building.o Enemy.o functions.o Shooting.o $(CCFLAGS) -o FieldRunners.out

main.o: src/rsdl.hpp $(BUILDDIR)/main.cpp $(BUILDDIR)/main.hpp $(BUILDDIR)/FieldRunners.hpp $(BUILDDIR)/Enemy.hpp
	$(CC) -c $(BUILDDIR)/main.cpp -o main.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	$(CC) -c src/rsdl.cpp -o rsdl.o

FieldRunners.o: $(BUILDDIR)/FieldRunners.cpp $(BUILDDIR)/FieldRunners.hpp $(BUILDDIR)/main.hpp $(BUILDDIR)/ImportException.hpp $(BUILDDIR)/Shooting.hpp $(BUILDDIR)/Enemy.hpp $(BUILDDIR)/Building.hpp
	$(CC) -c $(BUILDDIR)/FieldRunners.cpp 

Building.o: $(BUILDDIR)/Building.cpp $(BUILDDIR)/Building.hpp $(BUILDDIR)/main.hpp $(BUILDDIR)/ImportException.hpp $(BUILDDIR)/Shooting.hpp
	$(CC) -c $(BUILDDIR)/Building.cpp

Enemy.o: $(BUILDDIR)/Enemy.cpp $(BUILDDIR)/Enemy.hpp $(BUILDDIR)/main.hpp
	$(CC) -c $(BUILDDIR)/Enemy.cpp

functions.o: $(BUILDDIR)/functions.cpp $(BUILDDIR)/main.hpp $(BUILDDIR)/FieldRunners.hpp $(BUILDDIR)/Enemy.hpp
	$(CC) -c $(BUILDDIR)/functions.cpp

Shooting.o: $(BUILDDIR)/Shooting.cpp $(BUILDDIR)/Enemy.hpp $(BUILDDIR)/Shooting.hpp
	$(CC) -c $(BUILDDIR)/Shooting.cpp


.PHONY: clean
clean:
	rm -r *.o
	rm FieldRunners.out