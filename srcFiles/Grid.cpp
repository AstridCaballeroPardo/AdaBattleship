#include "../headerFiles/Grid.h"
#include "../headerFiles/constants.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

//Implementing constructor
Grid::Grid():grid()
{
  setGrid(GRID_SIZE);  
  revealGrid();   
}

//Implementing Grid member methods
void Grid::revealGrid()
{
  //print headers - letters
  std::cout << std::setfill(' ') << std::setw(TILE_WIDTH + 1);
  for (int i = 1; i <= GRID_SIZE; i++){     
    std::cout << "|" << std::setw(TILE_PADDING) << " "  << i << "  ";
  }
  std::cout << "|\n";
  std::cout << std::setw(TILE_WIDTH + 1);
  std::cout << " " << std::setfill('-') << std::setw((GRID_SIZE * TILE_WIDTH) + GRID_SIZE) << '\n';
  for (int x = 0; x < GRID_SIZE; x++) {
    //print headers - row number
    std::cout << std::setfill(' ') << std::setw(TILE_PADDING) << " " << (char)(x + CAPITAL_LETTER) << "  ";
      
    for (int y = 0; y < GRID_SIZE; y++) {        
      std::cout << "|" << std::setw(TILE_PADDING) << " " << Grid::grid[x][y].getIcon() << "  ";
    }    
  std::cout << "|\n";    
  }  
  std::cout << std::setfill(' ') << std::setw(TILE_WIDTH + 1);
  std::cout << " " << std::setfill('-') << std::setw((GRID_SIZE * TILE_WIDTH) + GRID_SIZE) << "\n";    
}

 void Grid::setGrid(int size)
{
  //Define the size of the 2D vector  
  grid.assign(size, std::vector<Tile>(size));
}


void Grid::updateGrid(char letter, int x)
{
  int eT = (int)TileState::emptyTile;
  // int sT = (int)TileState::shipTile;
  // int bT = (int)TileState::bombedTile;
  
  // x is the scaled value of the letter 
  int y = letter - CAPITAL_LETTER ;
  //check if tile is empty
  if (grid[y][x - 1].getTileState() == eT) {
    grid[y][x - 1].setX(letter);
    grid[y][x - 1].setY(x);
    grid[y][x - 1].setTileState((int)TileState::shipTile);
    grid[y][x - 1].setIcon('^');
    //TODO set shipId
  }  
  
}

 Tile Grid::getTile(char row, int column){
   int y = row - CAPITAL_LETTER ;
   Tile myTile = grid[y][column - 1];
   return myTile;
 }