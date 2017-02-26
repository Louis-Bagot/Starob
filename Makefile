CC=g++
OPT=-g -std=c++11 -static
CFLAGS= -Wall -Wextra -Wreorder
LIBS= -lsfml-graphics -lsfml-window -lsfml-system
OBJ= main.o mmi.o hero.o fundations.o foe.o

# Executable(s)
exe: $(OBJ)
	$(CC) $(OPT) $(CFLAGS) $(OBJ) -o exe $(LIBS)


# Objet(s)
main.o: main.cpp mmi.h hero.h fundations.h
	$(CC) $(OPT) $(CFLAGS) -c main.cpp

mmi.o: mmi.h mmi.cpp fundations.h hero.h foe.h
	$(CC) $(OPT) $(CFLAGS) $(LIBS) -c mmi.cpp

hero.o: hero.h hero.cpp fundations.h
		$(CC) $(OPT) $(CFLAGS) -c hero.cpp

fundations.o: fundations.h fundations.cpp
		$(CC) $(OPT) $(CFLAGS) -c fundations.cpp

foe.o: foe.h foe.cpp fundations.h
		$(CC) $(OPT) $(CFLAGS) -c foe.cpp

# Cleaner
clean:
	rm *.o exe
