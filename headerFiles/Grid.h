#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Tile.h"

class Grid {
  private:    
    std::vector<std::vector<Tile>> grid;
    
  public:
  //constructor
  Grid();  

  //Grid member methods
  void revealGrid();

  void setGrid(int size);

  //inline implementation to have access to the private attribute 'grid'
  // int ** getGrid() const {return grid;}

  Tile getTile(char row, int column);
  
  void updateGrid(char letter, int number);
};