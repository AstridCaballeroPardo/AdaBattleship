#pragma once

#include <vector>
#include <string>
#include <memory>

#include "constants.h"
#include "VectorResource.h"

class Grid {
  private:
    // int grid[GRID_SIZE][GRID_SIZE];
    // int **grid = nullptr;  
    std::vector<std::vector<int>> grid;
    
  public:
  //constructor
  Grid();  

  //Grid member methods
  void createGrid();

  void revealGrid();

  void setGrid(int size);

  //inline implementation to have access to the private attribute 'grid'
  // int ** getGrid() const {return grid;}
  
  void updateGrid(char letter, int number);
};