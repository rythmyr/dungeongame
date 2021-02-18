#include <iostream>
#include <curses.h>
#include <getopt.h>
#include <limits.h>

#include "dungeon.h"

struct Options {
    bool help = false;
    long seed = 0;
    bool seedSet = false;
};

void printHelp(std::string name) {
    std::cout << "Usage: " <<  std::endl;
    std::cout << "    " << name << std::endl;
}

int getOptions(const int argc, char* const* argv, Options& opts){
    char opt;
    char* end = NULL;

    while ((opt = getopt(argc, argv, "hs:")) != -1) {
        switch(opt) {
            case 'h':
                opts.help = true;

                return 0;

            case 's':
                opts.seed = strtol(optarg, &end, 0);
                opts.seedSet = true;

                if (((opts.seed == LONG_MAX || opts.seed == LONG_MIN) && (errno == ERANGE))
                        || (*end != 0)) {
                    std::cerr << "invalid seed: please enter a valid integer value" << std::endl;
                    std::cerr << "given: " << optarg << std::endl << std::endl;
                    std::cerr << "max value: " << LONG_MAX << std::endl;
                    std::cerr << "min value: " << LONG_MIN << std::endl;

                    return 1;
                }

                break;

            case '?':
                return 1;
        }
    }

    return 0;
}

int main (int argc, char** argv) {
    Options options;

    if (getOptions(argc, argv, options)) {
        return 0;
    }

    if (options.help) {
        printHelp(argv[0]);

        return 0;
    }

    if (options.seedSet) {
        srand(options.seed);
    } else {
        srand(time(0));
    }

    Dungeon dungeon;
    dungeon.Generate(50, 50);

    initscr();

    bool running = true;

    while(running) {
        dungeon.Display();
        refresh();
        char c = getch();
        switch (c) {
            case 'q':
                running = false;
                break;
            case 'w':
                dungeon.MovePlayer(DIR_UP);
                break;
            case 'a':
                dungeon.MovePlayer(DIR_LEFT);
                break;
            case 's':
                dungeon.MovePlayer(DIR_DOWN);
                break;
            case 'd':
                dungeon.MovePlayer(DIR_RIGHT);
                break;
        }
    }
    endwin();

    return 0;
}
