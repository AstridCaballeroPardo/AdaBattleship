#include "../headerFiles/Grid.h"
#include "../headerFiles/Tile.h"
#include "../headerFiles/Fleet.h"
#include "../headerFiles/Ship.h"
#include "../headerFiles/constants.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>

//Implementing constructor
Fleet::Fleet():size_(FLEET_SIZE),fleetVector()
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
    fleetVector.push_back(Ship());
  }
}

void Fleet::setGridId(int gridId)
{
  gridId_ = gridId;
}

Ship& Fleet::getShip(std::vector<Ship> &fleet, int shipId)
{
  std::unique_ptr<Ship> myShip1; 
  for (int i = 0, count = 0; i < fleet.size(); i++) 
  {
    if (fleet[i].getShipId() == shipId)
    {
      myShip1 = (std::unique_ptr<Ship>) &fleet[i];
    }
  }
  return *myShip1;
}

void Fleet::reduceFleetSize(){
  size_ --;
}  