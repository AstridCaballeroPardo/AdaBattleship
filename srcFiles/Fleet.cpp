
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>


#include "../headerFiles/Grid.h"
#include "../headerFiles/Tile.h"
#include "../headerFiles/Fleet.h"
#include "../headerFiles/constants.h"
#include "../headerFiles/Utility.h"


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

bool Fleet::isShipInFleet(int shipType)
{
    for (int i = 0; i < fleetVector_.size(); i++) {
      if (fleetVector_[i].getShipType() == shipType) {        
        return true;
      }
    }
    return false;
}

bool Fleet::isFleetCompleted(){
  int count = 0;
  for (int i = 0; i < fleetVector_.size(); i++) {
    if (fleetVector_[i].getShipType() != 0) {
      count++;
    }
  }
  if (count == fleetVector_.size()) {
    return true;
  }
  return false;
}