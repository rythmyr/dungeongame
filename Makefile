a.out: main.o dungeon.o
	g++ -Wall -Werror -std=c++17 main.o dungeon.o -o a.out -lncurses

main.o: main.cpp dungeon.h
	g++ -Wall -Werror -std=c++17 main.cpp -o main.o -c

dungeon.o: dungeon.cpp dungeon.h
	g++ -Wall -Werror -std=c++17 dungeon.cpp -o dungeon.o -c

clean:
	rm *.o
	rm a.out
