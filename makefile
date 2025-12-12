CC = g++

CFLAGS = -c -g -Wall -std=c++17 -fpermissive

EXENAME = hi.out

OBJS = main.o Engine.o Particle.o Matrices.o

all: $(OBJS)
	$(CC) $(OBJS) -o $(EXENAME) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o: main.cpp Engine.h
	$(CC) $(CFLAGS) main.cpp

Engine.o: Engine.cpp Engine.h Particle.h
	$(CC) $(CFLAGS) Engine.cpp

Particle.o: Particle.cpp Particle.h Matrices.h
	$(CC) $(CFLAGS) Particle.cpp

Matrices.o: Matrices.cpp Matrices.h
	$(CC) $(CFLAGS) Matrices.cpp

clean:
	rm -f *.o $(EXENAME)

run: all
	./$(EXENAME)