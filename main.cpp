#include <iostream>
#include <curses.h>
#include <getopt.h>

struct Options {
    bool help = false;
};

void printHelp(std::string name) {
    std::cout << "Usage: " <<  std::endl;
    std::cout << "    " << name << std::endl;
}

int getOptions(const int argc, char* const* argv, Options& opts){
    char opt;

    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
            case 'h':
                opts.help = true;

                return 0;

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

    initscr();

    printw("Hello, Curses!");
    refresh();
    getch();

    endwin();

    return 0;
}
