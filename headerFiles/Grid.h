#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Tile.h"
#include "Fleet.h"
#include "constants.h"

class Grid {
  private:    
    int gridId_;
    static int currentGridId_;
    std::vector<std::vector<Tile>> grid;
    Fleet gridFleet;
    int size_;
    
  public:
    //constructor
    Grid(int size = GRID_SIZE);  

    //Grid member methods
    void renderGrid();

    void setGrid(int size);

    void setFleetId(int gridId_);

    //inline implementation to have access to the private attribute 'grid'
    // int ** getGrid() const {return grid;}
    int getGridId()const {return gridId_;} 
    Fleet& getFleet() {return gridFleet;} 

    // Tile& getTile(char row, int column);   
    int getSize()const {return size_;} 
    std::vector<std::vector<Tile>>& getGrid() {return grid;}
    
    bool placeShip(char letter, int number, int shipType, char orientation, int index);
};