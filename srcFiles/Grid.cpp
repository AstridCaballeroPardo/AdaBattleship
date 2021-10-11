#include "../headerFiles/Grid.h"
#include "../headerFiles/constants.h"
#include "../headerFiles/TileState.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

//Implementing constructor
Grid::Grid():grid()
{
  setGrid(GRID_SIZE);
  createGrid();
  // revealGrid();   
}

//Implementing Grid member methods
void Grid::createGrid()
{
  int number = 0;
  for (int x = 0; x < GRID_SIZE; x++) {
    for (int y = 0; y < GRID_SIZE; y++) {
      Grid::grid[x][y] = number;
    }
  }
}

void Grid::revealGrid()
{
  //print headers - letters
  std::cout << std::setfill(' ') << std::setw(TILE_WIDTH + 1);
  for (int i = 1; i <= GRID_SIZE; i++){     
    std::cout << "|" << std::setw(TILE_WIDTH) << i;
  }
  std::cout << "|\n";
  std::cout << std::setw(TILE_WIDTH + 1);
  std::cout << " " << std::setfill('-') << std::setw((GRID_SIZE * TILE_WIDTH) + GRID_SIZE) << '\n';
  for (int x = 0; x < GRID_SIZE; x++) {
    //print row number
    std::cout << std::setfill(' ') << std::setw(TILE_WIDTH) << (char)(x + CAPITAL_LETTER);
      
    for (int y = 0; y < GRID_SIZE; y++) {        
      std::cout << "|" << std::setw(TILE_WIDTH) << Grid::grid[x][y];
    }    
  std::cout << "|\n";    
  }  
  std::cout << std::setfill(' ') << std::setw(TILE_WIDTH + 1);
  std::cout << " " << std::setfill('-') << std::setw((GRID_SIZE * TILE_WIDTH) + GRID_SIZE) << '\n';    
}

 void Grid::setGrid(int size)
{
  //Define the size of the 2D array
  // grid = new int *[size];
  // for (int i = 0; i < size; i++) {
  //   grid[i] = new int [size];
  // }

  //Define the size of the 2D vector
  grid.assign(size, std::vector<int>(size, 0));
}


void Grid::updateGrid(char letter, int x)
{
  int eT = (int)TileState::emptyTile;
  // int sT = (int)TileState::shipTile;
  // int bT = (int)TileState::bombedTile;
  
  // y is the scaled value of the letter 
  int y = letter - CAPITAL_LETTER ;
  //check if tile is empty
  if (grid[y][x - 1] == eT) {
    grid[y][x - 1] = 1;
  }  
  
}