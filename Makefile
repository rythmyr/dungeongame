a.out: main.o
	g++ -Wall -Werror -std=c++17 main.o -o a.out -lncurses

main.o: main.cpp
	g++ -Wall -Werror -std=c++17 main.cpp -o main.o -c

clean:
	rm *.o
	rm a.out
