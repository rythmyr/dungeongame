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
        this->_map[i] = '#';
    }

    // try to place rooms 100 times
    // number is arbitrary, higher numbers means more attempts, not necessarily more rooms
    for (int i = 0; i < 100; i ++) {
        bool skip = false;
        Room room;
        room.w = rand() % 5 + 3;
        room.h = rand() % 5 + 3;
        room.x = (rand() % (this->_sizeX - room.w - 4)) + 2;
        room.y = (rand() % (this->_sizeY - room.h - 4)) + 2;

        for (unsigned int j = 0; j < this->_rooms.size(); j++) {
            if (room.Collides(this->_rooms[j], 3)) {
                skip = true;
            }
        }
        if (skip) {continue;}
        for (int _x = room.x; _x < room.x + room.w; _x++) {
            for (int _y = room.y; _y < room.y + room.h; _y++) {
                this->SetTile(_x, _y, '.');
            }
        }
        this->_rooms.push_back(room);
    }

    Room startRoom = this->_rooms[0];

    this->_playerX = startRoom.x + (startRoom.w / 2);
    this->_playerY = startRoom.y + (startRoom.h / 2);

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
