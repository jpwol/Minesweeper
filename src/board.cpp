#include "Board.h"

void Board::hashTiles()
{
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            tiles.push_back(Tile{x, y, 0x00});
            Tile* tileptr = &tiles.back();
            GridPosition pos = std::make_pair(x, y);
            hash[pos] = tileptr;
        }
    }
}

Board::Tile* Board::getTile(int x, int y)
{
    GridPosition pos = std::make_pair(x, y);
    return hash[pos];
}

const uint8_t Board::getTileType(int x, int y)
{
    return(getTile(x, y)->state >> TYPE_SHIFT);
}

const bool Board::getTileFlag(int x, int y, Flags flag)
{
    if(flag != CLICKED && flag != FLAGGED && flag != VISITED){
        std::cerr << "Error! Unknown flag!\n";
        return false;
    }
    return(getTile(x, y)->state & flag) != 0;
}

void Board::setTileType(int x, int y, uint8_t type)
{
    getTile(x, y)->state = (getTile(x, y)->state & ~TYPE_MASK) | (type << TYPE_SHIFT);
}

void Board::setTileFlag(int x, int y, Flags flag)
{
    getTile(x, y)->state ^= flag;
}

void Board::updateKeys()
{
    for(auto& tile : tiles){
        switch(tile.state >> TYPE_SHIFT){
            case Empty:
                tile.texKey = "tileShown";
                break;
            case Number1:
                tile.texKey = "number1";
                break;
            case Number2:
                tile.texKey = "number2";
                break;
            case Number3:
                tile.texKey = "number3";
                break;
            case Number4:
                tile.texKey = "number4";
                break;
            case Number5:
                tile.texKey = "number5";
                break;
            case Number6:
                tile.texKey = "number6";
                break;
            case Number7:
                tile.texKey = "number7";
                break;
            case Number8:
                tile.texKey = "number8";
                break;
            case Mine:
                tile.texKey = "mine";
                break;
                default:
                    break;
        }
    } 
}

void Board::initBoard(bool showTiles, bool& loseState, int& bombIndex, float desiredDensity)
{
    loseState = false;

    int totalTiles = rows*cols;
    int bombCount = static_cast<int>(totalTiles * (desiredDensity / 100));
    bombIndex = bombCount;

    std::vector<GridPosition> positions;
    for(int x = 0; x < cols; x++){
        for(int y = 0; y < rows; y++){
            positions.push_back({x, y});
            getTile(x, y)->state = 0x00;
            if(showTiles)
                setTileFlag(x, y, CLICKED);
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);
    for(int i = 0; i < bombCount; i++){
        setTileType(positions[i].first, positions[i].second, Mine);
    }
    
    for(int x = 0; x < cols; x++){
        for(int y = 0; y < rows; y++){
            if(getTileType(x, y) != Mine){
                uint8_t bombSum = 0;
                for(int _x = -1; _x <= 1; _x++){
                    for(int _y = -1; _y <= 1; _y++){
                        if(_x == 0 && _y == 0) continue;
                        int nx = x + _x, ny = y + _y;
                        if(nx >= 0 && nx < cols && ny >= 0 && ny < rows && getTileType(nx, ny) == Mine)
                            bombSum++;
                    }
                }
                if(bombSum > 0)
                    setTileType(x, y, bombSum);
            }
        }
    }
    
    updateKeys();
}

void Board::triggerLoseState(bool &loseState)
{
    loseState = true;
    for(auto tile : tiles){
        if(getTileType(tile.x, tile.y) == Mine && !getTileFlag(tile.x, tile.y, CLICKED) && !getTileFlag(tile.x, tile.y, FLAGGED)){
            setTileFlag(tile.x, tile.y, CLICKED);
        }
    }
}

std::vector<Board::Tile*> Board::getNearbyTiles(int x, int y)
{
    std::vector<Tile*> tileptr;
    for(int _x = -1; _x <= 1; _x++){
        for(int _y = -1; _y <= 1; _y++){
            if(_x == 0 && _y == 0) continue;
            int nx = x + _x, ny = y + _y;
            if(nx >= 0 && nx < cols && ny >= 0 && ny < rows){
                tileptr.push_back(getTile(nx, ny));
            }
        }
    }
    return tileptr;
}

void Board::cycleTiles(int x, int y)
{
    if(getTileType(x, y) != Empty)
        return;
    else if(getTileType(x, y) == Empty && !getTileFlag(x, y, VISITED)){
        for(auto& tile : getNearbyTiles(x, y)){
            if(!getTileFlag(tile->x, tile->y, CLICKED) && !getTileFlag(tile->x, tile->y, FLAGGED)){
                setTileFlag(tile->x, tile->y, CLICKED);
                if(getTileType(tile->x, tile->y) == Empty)
                    cycleTiles(tile->x, tile->y);
            }
        setTileFlag(x, y, VISITED);
        }
    }
}