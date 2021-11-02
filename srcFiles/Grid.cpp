
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "../headerFiles/Grid.h"
#include "../headerFiles/Tile.h"
#include "../headerFiles/Ship.h"
#include "../headerFiles/Fleet.h"
#include "../headerFiles/constants.h"
#include "../headerFiles/Utility.h"

//initializing the static variable
int Grid::currentGridId_ = 1;

//Implementing constructor
Grid::Grid(int size):gridId_(currentGridId_++),gridFleet(),grid(), size_(size), playerType_()
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
      int tileState = Grid::grid[x][y].getTileState();
      char icon = Grid::grid[x][y].getIcon();

      if(tileState == 0) 
      {
        std::cout << "|" << std::setw(TILE_PADDING) << " " << BLUEBACK << icon << ENDCOLOUR << "  ";
      }
      else if (tileState == 1) 
      {
        std::cout << "|" << std::setw(TILE_PADDING) << " " << YELLOW << icon << ENDCOLOUR << "  ";
      }
      else if (tileState == 2 && icon == '~') 
      {
        std::cout << "|" << std::setw(TILE_PADDING) << " " << LIGHTBLUE << icon << ENDCOLOUR << "  ";
      }
      else if (tileState == 2 && icon == 'X') 
      {
        std::cout << "|" << std::setw(TILE_PADDING) << " " << RED << icon << ENDCOLOUR << "  ";
      }
      
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
  int eT = (int)tileState::emptyTile;  

  //check if fleet already has placed the inputted shiptype
  //call fleet
  std::vector<Ship>& ships = gridFleet.getFleetVector(); //Getting the FleetVector by reference.
  isShipInFleet_ = gridFleet.isShipInFleet(shipType); 

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
            grid[x][y + n].setTileState((int)tileState::shipTile);
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
            grid[x + n][y].setTileState((int)tileState::shipTile);
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


void Grid::setFleetId(int gridId)
{   
  gridFleet.setGridId(gridId);
}

void Grid::setPlayerType(std::string playerType)
{
  playerType_ = playerType;
}

void Grid::resetTile(int x, int y, std::shared_ptr<Tile> tmpTile)
{
  grid[x][y].setTileState(tmpTile->getTileState());
}

void Grid::resetBombedTiles(std::vector<int>& bombedTilesGrid)
{
 std::shared_ptr<Tile> tmpTile = std::make_shared<Tile>();
 for (int i = 0; i < bombedTilesGrid.size(); i++)
 {
   //find tile and reset
   //define len, orientation, x and y
   int x =(bombedTilesGrid[i] / size_);
   int y = (bombedTilesGrid[i] % size_);
   //only reset the bombed tiles that didn't belong to ships. There is another reset function that reset the ships wheter they were bombed or not.
   if (grid[x][y].getIcon() == '~' && grid[x][y].getTileState() == 2)
   {
     resetTile(x, y, tmpTile);
   }
 }
}

void Grid::resetTiles(int len, char orientation, int x, int y, std::shared_ptr<Tile> tmpTile) 
{
  for (int n = 0; n < len; n++) 
        {
          //reset horizontally to the right 
          if (orientation == 'H') 
          {
            //reset tile            
            grid[x][y + n].setX(tmpTile->getX()) ; 
            //to set y, add 1 to 'y' because y has a zero based value (0 to (GRID_SIZE - 1)) but it needs to be one based value (1 to GRID_SIZE)
            grid[x][y + n].setY(tmpTile->getY());
            grid[x][y + n].setTileState(tmpTile->getTileState());
            grid[x][y + n].setIcon(tmpTile->getIcon());
            grid[x][y + n].setShipId(tmpTile->getShipId());
          }  
          //reset vertically to the bottom
          else if(orientation == 'V')
          {
            //reset tile
            grid[x + n][y].setX(tmpTile->getX()) ;  
            //to set y, add 1 to 'y' because y has a zero based value (0 to (GRID_SIZE - 1)) but it needs to be one based value (1 to GRID_SIZE)     
            grid[x + n][y].setY(tmpTile->getY());
            grid[x + n][y].setTileState(tmpTile->getTileState());
            grid[x + n][y].setIcon(tmpTile->getIcon());
            grid[x + n][y].setShipId(tmpTile->getShipId());
          }
        } 
}

void Grid::resetFleet()
{
  udtCoordInput coordInput;
  std::vector<Ship>& fleetV = getFleet().getFleetVector();
  for (int i = 0, count = 0; i < fleetV.size(); i++) 
    {
      if(fleetV[i].getShipType() != 0)
      {
         //reset tiles of placed ship
        int shipType = fleetV[i].getShipType();
        char orientation = fleetV[i].getOrientation(); 
        int len = calcShipLength(shipType);        

        //get Tiles
        int gridSize= grid.size();        
        int tileIndex = fleetV[i].getShipIndex();
        coordInput = indexToXY(tileIndex, gridSize);        
        //new values
        std::shared_ptr<Tile> tmpTile = std::make_shared<Tile>();        
        
        resetTiles(len, orientation, letterToInt(coordInput.row), coordInput.column, tmpTile);
      }
      //reset ship
      fleetV[i].setShip(0, 0, -1);      
    }
    //reset Fleet size
    getFleet().setSize(FLEET_SIZE);
}


