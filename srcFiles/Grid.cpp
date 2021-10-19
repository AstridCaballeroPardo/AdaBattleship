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
Grid::Grid():gridId_(currentGridId_++),gridFleet(),grid()
{
  setGrid(GRID_SIZE);  
  renderGrid();   
  setFleetId(gridId_);
}

//Implementing Grid member methods
void Grid::renderGrid()
{
  std::cout << "\n";
  //print headers - column
  std::cout << std::setfill(' ') << std::setw(TILE_WIDTH + 1);
  for (int i = 1; i <= GRID_SIZE; i++){     
    std::cout << "|" << std::setw(TILE_PADDING) << " "  << i << "  ";
  }
  std::cout << "|\n";
  std::cout << std::setw(TILE_WIDTH + 1);
  std::cout << " " << std::setfill('-') << std::setw((GRID_SIZE * TILE_WIDTH) + GRID_SIZE) << '\n';
  for (int x = 0; x < GRID_SIZE; x++) {
    //print headers - row
    std::cout << std::setfill(' ') << std::setw(TILE_PADDING) << " " << intToLetter(x) << "  ";
      
    //print tiles
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


bool Grid::placeShip(char letter, int y, int shipType, int orientation)
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
  if (!isShipInFleet_) {  
  
    len = calcShipLength(shipType);
    
    // x is the scaled value of the letter
    x = letterToInt(letter);

    //Check if there is space to place ship
    bool areTilesAvailable_ = areTilesAvailable(len, orientation, x, y, eT, grid);
    
    //update grid
    if (areTilesAvailable_) {
      //find unassigned ship
      for (int i = 0, count = 0; i < gridFleet.getSize() && count < 1; i++) {
        if(ships[i].getShipType() == 0){
          // count is used to make sure only one ship gets updated instead of all the ships of the vector
          count++;
          //update empty ship
          ships[i].setShip(shipType, orientation);
          for (int n = 0; n < len; n++) {
            //update horizontally to the right 
            if (orientation == 2) {
              //update tile
              grid[x][(y - 1) + n].setX(letter) ;       
              grid[x][(y - 1) + n].setY(y + n);
              grid[x][(y - 1) + n].setTileState((int)TileState::shipTile);
              grid[x][(y - 1) + n].setIcon('^');
              grid[x][(y - 1) + n].setShipId(ships[i].getShipId());
            }  
            //update vertically to the bottom
            else if(orientation == 1){
              //update tile
              grid[x + n][y - 1].setX(letter + n) ;       
              grid[x + n][y - 1].setY(y);
              grid[x + n][y - 1].setTileState((int)TileState::shipTile);
              grid[x + n][y - 1].setIcon('^');
              grid[x + n][y - 1].setShipId(ships[i].getShipId());
            }
          }
        }
      }
      return true;
    } else {
      std::cout << "\033[1;31mspace not available for ship, try again.\033[0m\n\n";
    } 
  } else {
    std::cout << "\033[1;31mShip already placed, try again.\033[0m\n\n";
  }
  return false;
}

 Tile Grid::getTile(char row, int column){   
   Tile myTile = grid[letterToInt(row)][column - 1];
   return myTile;
 }

 void Grid::setFleetId(int gridId){   
   gridFleet.setGridId(gridId);
 }

