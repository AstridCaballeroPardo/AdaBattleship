#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "constants.h"
#include "Ship.h"
#include "Grid.h"

class Fleet{
  private:    
    int size_;
    int gridId_;
    std::vector<Ship> fleetVector_;
    

  public:
    //constructor
    Fleet(); 

    //member methods
    void setSize(int size);
    void setGridId(int gridId);
    void setFleet(int size);
   

    //inline implementation to have access to the private attributes
    int getSize() const {return size_;}  
    int getGridId() const {return gridId_;}  
    std::vector<Ship>& getFleetVector() {return fleetVector_;};
    
    Ship& getShip(std::vector<Ship>& fleetVector, int shipId);  
    void reduceFleetSize();   
    void resetFleet(std::vector<std::vector<Tile>>& grid);  
    bool isShipInFleet(int shipType); 
    bool isFleetCompleted();
};