#include <iostream>
#include <ncurses.h>

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
        this->_map[i] = '.';
    }

    for (; x >= 0; x-- ) {
        this->SetTile(x, 0, '#');
        this->SetTile(x, this->_sizeY - 1, '#');
    }
    for (; y >= 0; y-- ) {
        this->SetTile(0, y, '#');
        this->SetTile(this->_sizeX - 1, y, '#');
    }

    this->_playerX = 9;
    this->_playerY = 30;
    this->SetTile(9, 30, '@');
}

void Dungeon::Display() {
    for (int x = 0; x < this->_sizeX; x++) {
        for (int y = 0; y < this->_sizeY; y++) {
            mvaddch(y, x, this->GetTile(x, y));
        }
    }
}

int Dungeon::SetTile(int x, int y, char tile) {
    if (!this->_map) {
        return 1;
    }
    if (x < 0 || x >= this->_sizeX) {
        return 1;
    }
    if (y < 0 || y >= this->_sizeY) {
        return 1;
    }
    this->_map[x*this->_sizeY + y] = tile;
    return 0;
}

char Dungeon::GetTile(int x, int y) {
    if (!this->_map) {
        return 0;
    }
    if (x < 0 || x >= this->_sizeX) {
        return 0;
    }
    if (y < 0 || y >= this->_sizeY) {
        return 0;
    }

    return this->_map[x*this->_sizeY + y];
}

int Dungeon::MovePlayer(DirectionPair direction) {
    int newX = this->_playerX + direction.x;
    int newY = this->_playerY + direction.y;

    if (this->GetTile(newX, newY) == '.') {
        //empty space, move there
        this->SetTile(newX, newY, '@');
        this->SetTile(this->_playerX, this->_playerY, '.');
        this->_playerX = newX;
        this->_playerY = newY;
    }
    return 1;
}
