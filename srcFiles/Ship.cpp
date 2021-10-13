#include "../headerFiles/Ship.h"
#include "../headerFiles/Tile.h"
#include "../headerFiles/constants.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

//initializing the static variable
int Ship::currentShipId_ = 1;

//Implementing constructor
Ship::Ship():shipId_(currentShipId_++),isSunk(false), shipLen_(0), shipType_(0), orientation_(0) {}

//Grid member methods
void Ship::setShip(int shipType, int orientation){  
  shipType_ = shipType;
  orientation_ = orientation;
  switch(shipType) {
    case 0: 
      shipLen_ = 5;
      break;
    case 1:
      shipLen_ = 4;
      break;
    case 2: 
      shipLen_ = 3;
      break;
    case 3:
      shipLen_ = 3;
      break;
    case 4:
      shipLen_ = 2;
      break;
  }
}

 void Ship::setIsSunk(bool sunk){
   isSunk = sunk;
 }

