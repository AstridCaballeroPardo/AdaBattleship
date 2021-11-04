#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Tile.h"
#include "Fleet.h"
#include "Ship.h"
#include "constants.h"

class Grid {
  private:    
    int gridId_;
    static int currentGridId_;
    std::vector<std::vector<Tile>> grid;
    Fleet gridFleet;
    int size_;
    std::string playerType_;
    
  public:
    //constructor
    Grid(int size = GRID_SIZE);  

    //Grid member methods
    void renderGrid(bool hide);
    void setGrid(int size);
    void setFleetId(int gridId_);
    void setPlayerType(std::string playerType);

    //inline implementation to have access to the private attribute 'grid'    
    int getGridId()const {return gridId_;} 
    Fleet& getFleet() {return gridFleet;}  
    int getSize()const {return size_;} 
    std::vector<std::vector<Tile>>& getGrid() {return grid;}
    std::string getPlayerType() const {return playerType_;}
    
    bool placeShip(char letter, int number, int shipType, char orientation, int index);
    void resetTile(int x, int y, std::shared_ptr<Tile> tmpTile);
    void resetBombedTiles(std::vector<int>& bombedTilesGrid); 
    void resetTiles(int shipLen, char orientation, int x, int y, std::shared_ptr<Tile> tmpTile);
    void resetFleet(); 
    void setShipTile(char orientation,int shipLen, char letter, int x, int y, std::vector<Ship>& ships, int shipIndx);
};