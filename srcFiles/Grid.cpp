#include "../headerFiles/Grid.h"
#include "../headerFiles/Tile.h"
#include "../headerFiles/Ship.h"
#include "../headerFiles/Fleet.h"
#include "../headerFiles/constants.h"
#include "../headerFiles/Utility.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

/**refactoring**/


//initializing the static variable
int Grid::currentGridId_ = 1;

//Implementing constructor
Grid::Grid(int size):gridId_(currentGridId_++),gridFleet(),grid(), size_(size)
{
  setGrid(size_);  
  // renderGrid();   
  setFleetId(gridId_);
}

//Implementing Grid member methods
void Grid::renderGrid()
{
  std::cout << "\n";
  //print headers - column
  std::cout << std::setfill(' ') << std::setw(TILE_WIDTH + 1);
  for (int i = 1; i <= size_; i++)
  {     
    std::cout << "|" << std::setw(TILE_PADDING) << " "  << i << "  ";
  }
  std::cout << "|\n";
  std::cout << std::setw(TILE_WIDTH + 1);
  std::cout << " " << std::setfill('-') << std::setw((size_ * TILE_WIDTH) + size_) << '\n';
  for (int x = 0; x < size_; x++) 
  {
    //print headers - row
    std::cout << std::setfill(' ') << std::setw(TILE_PADDING) << " " << intToLetter(x) << "  ";
      
    //print tiles
    for (int y = 0; y < size_; y++) 
    {        
      std::cout << "|" << std::setw(TILE_PADDING) << " " << Grid::grid[x][y].getIcon() << "  ";
    }    
  std::cout << "|\n";    
  }  
  std::cout << std::setfill(' ') << std::setw(TILE_WIDTH + 1);
  std::cout << " " << std::setfill('-') << std::setw((size_ * TILE_WIDTH) + size_) << "\n";    
}

 void Grid::setGrid(int size)
{
  //Define the size of the 2D vector  
  grid.assign(size, std::vector<Tile>(size));
}


bool Grid::placeShip(char letter, int y, int shipType, char orientation, int index)
{
  int countAvailableTiles = 0;
  int len = 0;
  int x = 0;
  bool isShipInFleet_ = false;
  int eT = (int)TileState::emptyTile;
  // int sT = (int)TileState::shipTile;
  // int bT = (int)TileState::bombedTile;

  //check if fleet already has placed the inputted shiptype
  //call fleet
  std::vector<Ship>& ships = gridFleet.getFleetVector(); //Getting the FleetVector by reference.
  isShipInFleet_ = isShipInFleet(ships, shipType); 

  // place ship
  if (!isShipInFleet_) 
  {  
    len = calcShipLength(shipType);
    
    // x is the scaled value of the letter
    x = letterToInt(letter);
    
    //update grid    
    //find unassigned ship
    for (int i = 0, count = 0; i < gridFleet.getSize() && count < 1; i++) 
    {
      if(ships[i].getShipType() == 0)
      {
        // count is used to make sure only one ship gets updated instead of all the ships of the vector
        count++;
        //update empty ship
        ships[i].setShip(shipType, orientation, index);
        for (int n = 0; n < len; n++) 
        {
          //update horizontally to the right 
          if (orientation == 'H') 
          {
            //update tile
            grid[x][y + n].setX(letter) ; 
            //to set y, add 1 to 'y' because y has a zero based value (0 to (GRID_SIZE - 1)) but it needs to be one based value (1 to GRID_SIZE)
            grid[x][y + n].setY(y + n + 1);
            grid[x][y + n].setTileState((int)TileState::shipTile);
            grid[x][y + n].setIcon('^');
            grid[x][y + n].setShipId(ships[i].getShipId());
          }  
          //update vertically to the bottom
          else if(orientation == 'V')
          {
            //update tile
            grid[x + n][y].setX(letter + n) ;  
            //to set y, add 1 to 'y' because y has a zero based value (0 to (GRID_SIZE - 1)) but it needs to be one based value (1 to GRID_SIZE)     
            grid[x + n][y].setY(y + 1);
            grid[x + n][y].setTileState((int)TileState::shipTile);
            grid[x + n][y].setIcon('^');
            grid[x + n][y].setShipId(ships[i].getShipId());
          }
        }
      }
    }
    return true;    
  } else 
  {
    std::cout << "\033[1;31mShip already placed, try again.\033[0m\n\n";
  }
  return false;
}

 Tile Grid::getTile(char row, int column)
 {   
   Tile& myTile = grid[letterToInt(row)][column];
   return myTile;
 }

 void Grid::setFleetId(int gridId)
 {   
   gridFleet.setGridId(gridId);
 }

