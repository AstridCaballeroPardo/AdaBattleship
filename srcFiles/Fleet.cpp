#include "../headerFiles/Grid.h"
#include "../headerFiles/Tile.h"
#include "../headerFiles/Fleet.h"
#include "../headerFiles/Ship.h"
#include "../headerFiles/constants.h"
#include "../headerFiles/Utility.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>

//Implementing constructor
Fleet::Fleet():size_(FLEET_SIZE),fleetVector_()
{
  setFleet(size_);
}

//member methods
void Fleet::setSize(int size)
{
  size_ = size;
}
void Fleet::setFleet(int size)
{
  //Populate the FleetVector with n(size) number of default ships (each ship has a unique Id)  
  for (int i = 0; i < size; i++) {
    fleetVector_.push_back(Ship());
  }
}

void Fleet::setGridId(int gridId)
{
  gridId_ = gridId;
}

Ship& Fleet::getShip(std::vector<Ship>& fleetVector_, int shipId)
{
  int index = -1;
  for (int i = 0, count = 0; i < fleetVector_.size(); i++) 
  {
    if (fleetVector_[i].getShipId() == shipId)
    {
      index = i;
      break;
    }
  }
  return fleetVector_[index];
}

void Fleet::reduceFleetSize(){
  size_ --;
}  

void Fleet::resetFleet(std::vector<std::vector<Tile>>& grid)
{
  for (int i = 0, count = 0; i < fleetVector_.size(); i++) 
    {
      if(fleetVector_[i].getShipType() != 0)
      {
         //reset tiles of placed ship
        int shipType = fleetVector_[i].getShipType();
        char orientation = fleetVector_[i].getOrientation();        
        int len = calcShipLength(shipType);

        //get Tiles
        int gridSize= grid.size();
        // int totalTiles = pow(gridSize, 2);
        int tileIndex = fleetVector_[i].getShipIndex();
        int x=(tileIndex / gridSize);
        int y= (tileIndex % gridSize);  
        //new values
        std::shared_ptr<Tile> tmpTile = std::make_shared<Tile>();        
        
        resetTiles(len, grid, orientation, x, y, tmpTile);
      }
      //reset ship
      fleetVector_[i].setShip(0, 0, -1);
    }
    //reset Fleet size
    size_ = FLEET_SIZE;
}