#pragma once

struct DirectionPair {
    char x, y;
};

inline DirectionPair DIR_UP = { .x = 0, .y = -1 };
inline DirectionPair DIR_DOWN = { .x = 0, .y = 1 };
inline DirectionPair DIR_LEFT = { .x = -1, .y = 0 };
inline DirectionPair DIR_RIGHT = { .x = 1, .y = 0 };

class Dungeon {
private:
    char* _map = nullptr;
    int _sizeX = 0;
    int _sizeY = 0;

    int _playerX = 0;
    int _playerY = 0;
public:
    Dungeon();
    ~Dungeon();

    char GetTile(int x, int y);

    int SetTile(int x, int y, char tile);

    int MovePlayer(DirectionPair direction);

    void Generate(int x, int y);
    void Display();
};
