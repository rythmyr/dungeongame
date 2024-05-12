#pragma once

#include <vector>

struct DirectionPair {
    char x, y;
};

inline DirectionPair DIR_UP = { .x = 0, .y = -1 };
inline DirectionPair DIR_DOWN = { .x = 0, .y = 1 };
inline DirectionPair DIR_LEFT = { .x = -1, .y = 0 };
inline DirectionPair DIR_RIGHT = { .x = 1, .y = 0 };

struct Monster {
    int x = 0;
    int y = 0;
    int health = 15;
    char displayChar = 'm';
    Monster(Monster const &m) = delete;
    Monster() {};
};

struct Room {
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    inline bool Collides(Room const &other) {
        // equal means touching, but not overlapping, so return false for collisions in that case
        return other.x + other.w > this->x
            && other.x < this->x + this->w
            && other.y + other.h > this->y
            && other.y < this->y + this->h;
    }

    inline bool Collides(Room const &other, int threshold) {
        Room r;
        r.x = other.x - threshold;
        r.y = other.y - threshold;
        r.w = other.w + (threshold * 2);
        r.h = other.h + (threshold * 2);
        return this->Collides(r);
    }
};

class Dungeon {
private:
    char* _map = nullptr;
    int _sizeX = 0;
    int _sizeY = 0;

    int _playerX = 0;
    int _playerY = 0;

    Monster* _monsters = nullptr;
    int _monsterCount = 0;

    std::vector<Room> _rooms = std::vector<Room>();

    void ConnectAllRooms();
    void ConnectRooms(const Room &r1, const Room &r2);
public:
    Dungeon();
    ~Dungeon();

    char GetTile(int x, int y);

    int SetTile(int x, int y, char tile);

    int MovePlayer(DirectionPair direction);

    void Generate(int x, int y);
    void Display();
};
