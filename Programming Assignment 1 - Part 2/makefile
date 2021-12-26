
all: test

test: main.o Stress_ball.o Collection.o
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ main.o Stress_ball.o Collection.o -o test

main.o: main.cpp
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -c main.cpp

Stress_ball.o: Stress_ball.cpp Stress_ball.h
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -c Stress_ball.cpp

Collection.o: Collection.cpp Collection.h
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -c Collection.cpp


clean:
	rm *.o test

run: test
	./test