#include <iostream>
#include <curses.h>

int main (int argc, char** argv) {
    initscr();

    printw("Hello, Curses!");
    refresh();
    getch();

    endwin();

    return 0;
}
