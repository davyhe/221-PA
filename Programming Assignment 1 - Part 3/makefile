all: test


test:  Collection-test.o Stress_ball.o Jeans.o Stress_ball_test.o Jeans_test.o
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ Stress_ball.o  Collection-test.o Jeans.o Stress_ball_test.o Jeans_test.o -o test

Collection-test.o: Collection-test.cpp Collection.h 
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -c Collection-test.cpp

Stress_ball.o: Stress_ball.cpp Stress_ball.h
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -c Stress_ball.cpp 

Jeans.o: Jeans.cpp Jeans.h 
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -c Jeans.cpp 

Stress_ball_test.o: Stress_ball_test.cpp Stress_ball_test.h
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -c Stress_ball_test.cpp

Jeans_test.o: Jeans_test.cpp Jeans_test.h
	g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ -c Jeans_test.cpp




clean:
	rm *.o test

run: test
	./test