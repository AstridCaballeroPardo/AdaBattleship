#include "../headerFiles/Grid.h"
#include "../headerFiles/Tile.h"
#include "../headerFiles/Fleet.h"
#include "../headerFiles/Ship.h"
#include "../headerFiles/constants.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

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

Ship getShip(std::vector<Ship> &fleet, int shipId)
{
  Ship myShip; 
  // = fleet->fleetVector;
  //loop through the fleet searching for an specific ship
  // for ()
  return myShip;
}