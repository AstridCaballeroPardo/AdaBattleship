#pragma once

#include <vector>
#include <string>

class Grid {
  private:
    int **grid = NULL;    

  public:
  //constructor
  Grid();  

  //Grid member methods
  void createGrid();

  void revealGrid();

  void setGrid(int size);

  //inline. I implemented it here to be able to access the private attribute 'grid'
  int ** getGrid() {return grid;}
};