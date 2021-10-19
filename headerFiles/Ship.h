#pragma once

#include <string>

#include "constants.h"

class Ship {
  private:
    int shipId_;
    static int currentShipId_;
    int shipLen_; 
    int shipType_;
    int orientation_; // v - for vertical, h - for horizontal
    bool isSunk;

  public:
  //constructor
  Ship();  

  //Grid member methods
  void setShip(int shipType, int orientation);

  void setIsSunk(bool sunk);

  //inline implementation to have access to the private attributes
  int getShipId()const {return shipId_;}
  int getShipLen()const {return shipLen_;}
  int getShipType()const {return shipType_;}
  int getOrientation()const {return orientation_;}
  bool getIsSunk()const {return isSunk;}  
};