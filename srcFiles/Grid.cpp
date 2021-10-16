#include "../headerFiles/Grid.h"
#include "../headerFiles/Tile.h"
#include "../headerFiles/Ship.h"
#include "../headerFiles/Fleet.h"
#include "../headerFiles/constants.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

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


void Grid::updateGrid(char letter, int y, int shipType, int orientation)
{
  int countEmpty = 0;
  int len;
  int eT = (int)TileState::emptyTile;
  // int sT = (int)TileState::shipTile;
  // int bT = (int)TileState::bombedTile;

  switch(shipType) {
    case 0: 
      len = 5;
      break;
    case 1:
      len = 4;
      break;
    case 2: 
      len = 3;
      break;
    case 3:
      len = 3;
      break;
    case 4:
      len = 2;
      break;
  }
  
  // x is the scaled value of the letter 
  int x = letter - CAPITAL_LETTER ;

  //Check if there is space to place ship
  //loop through n number of tiles in the given orientation
  for (int n = 0; n < len; n++) {
    //check horizontally to the right 
    if (orientation == 2) {      
      //check if tile is empty
      if (grid[x][(y - 1) + n].getTileState() == eT) {
        countEmpty++;
      }    
    }
    //check vertically to the bottom
    else {
      if (grid[x + n][y - 1].getTileState() == eT) {
        countEmpty++;
      }  
    }
  }
  //update grid
  if (countEmpty == len) {
    //call fleet and update its Fleetvector
    std::vector<Ship>& ships = gridFleet.getFleetVector(); //Getting the FleetVector by reference.

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
          else {
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
    //set up ship
    // Ship newShip;
    // newShip.setShip(shipType, orientation);
    //loop through n number of tiles in the given orientation
    // for (int n = 0; n < len; n++) {
    //   //update horizontally to the right 
    //   if (orientation == 2) {
    //     //update tile
    //     grid[x][(y - 1) + n].setX(letter) ;       
    //     grid[x][(y - 1) + n].setY(y + n);
    //     grid[x][(y - 1) + n].setTileState((int)TileState::shipTile);
    //     grid[x][(y - 1) + n].setIcon('^');
    //     grid[x][(y - 1) + n].setShipId(newShip.getShipId());
    //   }  
    //   //update vertically to the bottom
    //   else {
    //     //update tile
    //     grid[x + n][y - 1].setX(letter + n) ;       
    //     grid[x + n][y - 1].setY(y);
    //     grid[x + n][y - 1].setTileState((int)TileState::shipTile);
    //     grid[x + n][y - 1].setIcon('^');
    //     grid[x + n][y - 1].setShipId(newShip.getShipId());
    //   }
    // }
  } else {
    std::cout << "\033[1;31mspace not available for ship, try again.\033[0m\n\n";
  }  
}

 Tile Grid::getTile(char row, int column){
   int y = row - CAPITAL_LETTER ;
   Tile myTile = grid[y][column - 1];
   return myTile;
 }

 void Grid::setFleetId(int gridId){   
   gridFleet.setGridId(gridId);
 }

