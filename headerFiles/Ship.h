#pragma once

#include <string>

class Ship {
  private:
    int shipId_;
    static int currentShipId_;
    int shipLen_; 
    int shipType_;
    int orientation_; // v - for vertical, h - for horizontal
    bool isSunk;
    int index_;

  public:
    //constructor
    Ship();  

    //Grid member methods
    void setShip(int shipType, char orientation, int index);

    void setIsSunk(bool sunk);

    void reduceShipLen();


    //inline implementation to have access to the private attributes
    int getShipId()const {return shipId_;}
    int getShipLen()const {return shipLen_;}
    int getShipType()const {return shipType_;}
    int getOrientation()const {return orientation_;}
    bool getIsSunk()const {return isSunk;}  
    int getShipIndex()const {return index_;} 
};