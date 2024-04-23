Ass4: Game.o Map.o Robot.o main.o
	g++ -o Ass4 Game.o Map.o Robot.o main.o

Map.o: Map.cpp Map.h
	g++ -c Map.cpp
Robot.o: Robot.cpp Robot.h Map.h
	g++ -c Robot.cpp
Game.o: Game.cpp Game.h Robot.h Map.h
	g++ -c Game.cpp
main.o: main.cpp Game.h Robot.h Map.h
	g++ -c main.cpp

clean:
	rm -f *.o 

