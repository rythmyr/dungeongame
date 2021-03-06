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

    // try to place rooms 10 times (number is arbitrary)
    for (int i = 0; i < 10; i ++) {
        Room room;
        room.w = rand() % 5 + 3;
        room.h = rand() % 5 + 3;
        room.x = (rand() % (this->_sizeX - room.w - 4)) + 2;
        room.y = (rand() % (this->_sizeY - room.h - 4)) + 2;
        for (int _x = room.x; _x < room.x + room.w; _x++) {
            for (int _y = room.y; _y < room.y + room.h; _y++) {
                this->SetTile(_x, _y, '#');
            }
        }
        this->_rooms.push_back(room);
    }

    //TODO monster spawning, this random count probably isn't great
    //this->_monsterCount = (rand() % (this->_sizeX * this->_sizeY) / 30) + 10;
    //this->_monsters = new Monster[this->_monsterCount];

    //for (int i = 0; i < this->_monsterCount; i++) {
    //    Monster* m = &this->_monsters[i];
    //    m->x = (rand() % (this->_sizeX - 2)) + 1;
    //    m->y = (rand() % (this->_sizeY - 2)) + 1;
    //    m->health = rand() % 15 + 15;
    //}
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
        Monster* m = &this->_monsters[i];
        if (m->health > 0) {
            mvaddch(m->y, m->x, m->displayChar);
        }
    }

    //TODO temporary
    // Display Rooms
    for (unsigned int i = 0; i < this->_rooms.size(); i++) {
        Room& r = this->_rooms[i];
        mvprintw(this->_sizeY + i + 1, 0, "x: %d, y: %d, w: %d, h: %d", r.x, r.y, r.w, r.h);
    }

    Room r1, r2;

    r1.x = 0;
    r1.y = 0;
    r1.w = 6;
    r1.h = 15;

    r2.x = 10;
    r2.y = 10;
    r2.w = 10;
    r2.h = 10;

    //TODO debug info
    mvaddch(this->_sizeY, this->_sizeX + 5, r1.Collides(r2, 5) ? 'c' : 'n');

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
        this->_playerX = newX;
        this->_playerY = newY;
    }
    return 1;
}
