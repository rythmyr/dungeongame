#include <iostream>
#include "dungeon.h"

Dungeon::Dungeon() {
}

Dungeon::~Dungeon() {
    if (this->_map) {
        delete[] this->_map;
    }
}

void Dungeon::Generate(int x, int y) {
    this->_sizeX = x;
    this->_sizeY = y;
    this->_map = new char[x * y];

    for (int i = 0; i < x * y; i++) {
        this->_map[i] = 0;
    }
}
