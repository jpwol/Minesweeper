#pragma once
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>

enum TileType : uint8_t{
    Empty,
    Number1,
    Number2,
    Number3,
    Number4,
    Number5,
    Number6,
    Number7,
    Number8,
    Mine,
    TYPE_MASK = 0xF0,
    TYPE_SHIFT = 4U
};
enum Flags : uint8_t{
    CLICKED = 0x01,
    FLAGGED = 0x02,
    VISITED = 0x04,
};

class Board{
    public:
        struct Tile{
            int x, y;
            uint8_t state;
            std::string texKey;
        };
        using GridPosition = std::pair<int, int>;
        struct Hash{
            std::size_t operator()(const GridPosition& gridPos) const {
                return std::hash<int>()(gridPos.first) ^ std::hash<int>()(gridPos.second);
            }
        };
        using SpatialHash = std::unordered_map<GridPosition, Tile*, Hash>;

    private:
        std::vector<Tile> tiles;
        SpatialHash hash;
    public:
        int rows = 16, cols = 30;
        int gBombCount;
        
        Board() : rows(16), cols(30){tiles.reserve(rows*cols);}
        Board(int r, int c) : rows(r), cols(c){tiles.resize(rows*cols);}

        void hashTiles();
        
        Tile* getTile(int x, int y);
        const uint8_t getTileType(int x, int y);
        const bool getTileFlag(int x, int y, Flags flag);
        void setTileType(int x, int y, uint8_t type);
        void setTileFlag(int x, int y, Flags flag);
        std::vector<Tile*> getNearbyTiles(int x, int y);
        std::vector<Tile> accessTiles(){return tiles;}
        void cycleTiles(int x, int y);
        void updateKeys();

        void initBoard(bool showTiles, bool& loseState, int& bombIndex, float desiredDensity);
        void triggerLoseState(bool& loseState);
};