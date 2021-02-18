#pragma once

class Dungeon {
private:
    char* _map = nullptr;
    int _sizeX = 0;
    int _sizeY = 0;
public:
    Dungeon();
    ~Dungeon();

    char GetTile(int x, int y);

    int SetTile(int x, int y, char tile);


    void Generate(int x, int y);
    void Display();
};
