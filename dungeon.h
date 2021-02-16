#pragma once

class Dungeon {
private:
    char* _map = nullptr;
    int _sizeX = 0;
    int _sizeY = 0;
public:
    Dungeon();
    ~Dungeon();

    void Generate(int x, int y);
};
