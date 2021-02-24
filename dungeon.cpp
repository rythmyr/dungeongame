#include <iostream>
#include <ncurses.h>

#include "dungeon.h"

Dungeon::Dungeon() {
}

Dungeon::~Dungeon() {
    if (this->_map) {
        delete[] this->_map;
    }
    if (this->_monsters) {
        delete[] this->_monsters;
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

    this->_playerX = (rand() % (this->_sizeX - 2)) + 1;
    this->_playerY = (rand() % (this->_sizeY - 2)) + 1;
    this->_playerX += 1;
    this->_playerY += 1;

    //TODO this random number is probably not good
    this->_monsterCount = (rand() % (this->_sizeX * this->_sizeY) / 30) + 10;
    this->_monsters = new Monster[this->_monsterCount];

    for (int i = 0; i < this->_monsterCount; i++) {
        this->_monsters[i].x = (rand() % (this->_sizeX - 2)) + 1;
        this->_monsters[i].y = (rand() % (this->_sizeY - 2)) + 1;
        this->_monsters[i].health = rand() % 15 + 15;
    }
}

void Dungeon::Display() {
    // Display map
    for (int x = 0; x < this->_sizeX; x++) {
        for (int y = 0; y < this->_sizeY; y++) {
            mvaddch(y, x, this->GetTile(x, y));
        }
    }

    // Display Player
    mvaddch(this->_playerY, this->_playerX, '@');

    // Display Monsters
    for (int i = 0; i < this->_monsterCount; i++) {
        Monster m = this->_monsters[i];
        if (m.health > 0) {
            mvaddch(m.y, m.x, m.displayChar);
        }
    }

    // move cursor out of the way
    // TODO turn off cursor, if possible
    move(this->_sizeY, this->_sizeX);

    // actually update screen
    refresh();
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
