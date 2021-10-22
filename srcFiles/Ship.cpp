#include "../headerFiles/Ship.h"
#include "../headerFiles/Tile.h"
#include "../headerFiles/constants.h"
#include "../headerFiles/Utility.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

//initializing the static variable
int Ship::currentShipId_ = 1;

//Implementing constructor
Ship::Ship():shipId_(currentShipId_++),isSunk(false), shipLen_(0), shipType_(0), orientation_(0) {}

//Grid member methods
void Ship::setShip(int shipType, char orientation, int index){  
  shipType_ = shipType;
  orientation_ = orientation; 
  shipLen_ = calcShipLength(shipType);
  index_ = index;
}

 void Ship::setIsSunk(bool sunk){
   isSunk = sunk;
 }





