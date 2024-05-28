all: ecosystem.bin

ecosystem.bin: main.o Organism.o Plant.o Animal.o Map.o
	g++ -o ecosystem.bin main.o Organism.o Plant.o Animal.o Map.o

Animal.o: Animal.h Animal.cpp Organism.o
	g++ -c Animal.h Animal.cpp
Plant.o: Plant.h Plant.cpp Organism.o
	g++ -c Plant.h Plant.cpp
Organism.o: Organism.h Organism.cpp
	g++ -c Organism.h Organism.cpp
Map.o: Map.h Map.cpp Organism.o Plant.o Animal.o
	g++ -c Map.cpp
main.o: main.cpp Organism.o Plant.o Animal.o Map.o
	g++ -c main.cpp

sample: ecosystem.bin
	./ecosystem.bin ../input/map.txt ../input/species.txt

clean:
	rm -rf *.bin *.o *.gch