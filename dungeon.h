#pragma once

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

class Dungeon {
private:
    char* _map = nullptr;
    int _sizeX = 0;
    int _sizeY = 0;

    int _playerX = 0;
    int _playerY = 0;

    Monster* _monsters = nullptr;
    int _monsterCount = 0;
public:
    Dungeon();
    ~Dungeon();

    char GetTile(int x, int y);

    int SetTile(int x, int y, char tile);

    int MovePlayer(DirectionPair direction);

    void Generate(int x, int y);
    void Display();
};
